
#include "fota_trigger.h"
#include "memory_map.h"
#include "bl_fota.h"

#include "syslog.h"
#ifdef FOTA_FS_ENABLE
#include "ff.h"
FIL fdst_update;
FIL fdst_image;
FATFS fatfs_update;
#endif
#ifndef FOTA_FS_ENABLE
#include "hal_flash.h"
#ifndef ROM_BASE
#define FOTA_RESERVED_PARTITION_END_ADDRESS    (FOTA_RESERVED_BASE + FOTA_RESERVED_LENGTH - BL_BASE)
#else
#define FOTA_RESERVED_PARTITION_END_ADDRESS    (FOTA_RESERVED_BASE + FOTA_RESERVED_LENGTH - ROM_BASE)
#endif

/* fota magic pattern */
#define FOTA_MODE_MAGIC_PATTERN      0x004F5441 //"OTA"
#define FOTA_TRIGGER_FLAG_ADDRESS    (FOTA_RESERVED_PARTITION_END_ADDRESS - 512)
#define UPDATE_INFO_SIZE    sizeof(bl_fota_update_info_t)
#else
/* fota magic pattern */
#define FOTA_MODE_MAGIC_PATTERN      0x004F5441 //"OTA"
#define FOTA_TRIGGER_FLAG_FILE         "SD:/update"
#endif


log_create_module(fota_trigger, PRINT_LEVEL_DEBUG);

#ifndef FOTA_FS_ENABLE
fota_ret_t fota_mode_entry(void)
{
#ifndef MTK_DUAL_IMAGE_FOTA_ENABLE
    hal_flash_status_t ret;
    uint32_t pattern = FOTA_MODE_MAGIC_PATTERN;
    ret = hal_flash_init();
    if (ret < HAL_FLASH_STATUS_OK)
    {
        LOG_E(fota_trigger, "[FOTA_trigger]Hal flash initialize fail, ret = %d\n", ret);
        return FOTA_TRIGGER_FAIL;
    }

    /* erase the last 4k block in fota reserved partition */
    ret = hal_flash_erase(FOTA_RESERVED_PARTITION_END_ADDRESS - 4096, HAL_FLASH_BLOCK_4K);
    if (ret < HAL_FLASH_STATUS_OK)
    {
        LOG_E(fota_trigger, "[FOTA_trigger]erase 4k block fail, ret = %d\n", ret);
        return FOTA_TRIGGER_FAIL;
    }

    /* write pattern into 512 bytes ahead of the reserved partition end address */
    LOG_I(fota_trigger, "[FOTA_SDK]flag address is 0x%x\n", FOTA_TRIGGER_FLAG_ADDRESS);
    ret = hal_flash_write(FOTA_TRIGGER_FLAG_ADDRESS, (const uint8_t*)&pattern, sizeof(uint32_t));
    if (ret < HAL_FLASH_STATUS_OK)
    {
        LOG_I(fota_trigger, "[FOTA_trigger]Trigger update result is %d\n", ret);
        return FOTA_TRIGGER_FAIL;
    }
    else
    {
        LOG_I(fota_trigger, "[FOTA_trigger]Trigger update result is %d\n", ret);
        return FOTA_TRIGGER_SUCCESS;
    }
#endif /* MTK_DUAL_IMAGE_FOTA_ENABLE*/

}

static fota_status_t fota_read_update_info(void *buffer, int32_t buffer_size)
{
    hal_flash_status_t status = HAL_FLASH_STATUS_OK;
	
    status = hal_flash_read(FOTA_TRIGGER_FLAG_ADDRESS, (uint8_t *)buffer, buffer_size);
    if (status != HAL_FLASH_STATUS_OK) {
        LOG_D(fota_trigger, "[FOTA]hal_flash_read , status = %d \r\n", flash_status);
        return FOTA_ERROR_FAIL;
    }
    LOG_D(fota_trigger, "[FOTA]read update info from %x \r\n", FOTA_TRIGGER_FLAG_ADDRESS);
    return FOTA_ERROR_NONE;
}

#else
fota_ret_t fota_mode_entry(void)
{
  FRESULT res;
  FIL fdst;
  UINT length_written = 0U;
  uint32_t pattern = FOTA_MODE_MAGIC_PATTERN;
  fota_ret_t result = FOTA_TRIGGER_SUCCESS;
  res = f_open(&fdst, _T(FOTA_TRIGGER_FLAG_FILE), FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
  if (FR_OK != res) {
      LOG_E(fota_trigger, "[FOTA] Failed to create fota trigger file, error = \n\r", (uint32_t)(res));
      result = FOTA_TRIGGER_FAIL;
  }
  res = f_write(&fdst, (const uint8_t*)&pattern, sizeof(uint32_t)-1, &length_written);
  if (FR_OK != res) {
      LOG_E(fota_trigger, "[FOTA] Failed to trigger flag to file, error = %d\n\r", (uint32_t)res);
      result = FOTA_TRIGGER_FAIL;
  }

  res = f_close(&fdst);
  if (FR_OK != res) {
      LOG_E(fota_trigger, "[FOTA] Failed to close fota trigger file!\n\r");
      result = FOTA_TRIGGER_FAIL;
  }

  return result;
}

static bl_fota_status_t fota_read_update_info(void *buffer, int32_t buffer_size)
{
    FRESULT res; /* fs status infor*/
    UINT length_read = 0;
    FSIZE_t file_length = 0;

    res = f_open(&fdst_update, _T("0:/update"), FA_OPEN_EXISTING | FA_READ);

    if (FR_OK != res) {
        LOG_E(fota_trigger, "[FOTA]Failed to open update file:%d\n\r", res);
        res = f_close(&fdst_update);
        return BL_FOTA_ERROR_LOADING_MARKER;
    }

    file_length = f_size(&fdst_update);
    LOG_D(fota_trigger, "[FOTA]bl_fota_read_update_info file length (%d)\n\r", file_length);

    res = f_read(&fdst_update, buffer, buffer_size, &length_read);
    if (FR_OK != res) {
        LOG_E(fota_trigger, "[FOTA]Failed to read the file:%d\n\r",res);
        res = f_close(&fdst_update);
        return BL_FOTA_ERROR_LOADING_MARKER;
    }
    LOG_D(fota_trigger, "[FOTA]length_read (%d)\n\r", length_read);

    res = f_close(&fdst_update);
    return BL_FOTA_ERROR_NONE;
}
#endif

bool fota_is_updating(void)
{
#ifndef FOTA_FS_ENABLE
    fota_status_t status = FOTA_ERROR_NONE;
    uint8_t update_info[UPDATE_INFO_SIZE];
    status = fota_read_update_info(update_info, UPDATE_INFO_SIZE);
	if (status != FOTA_ERROR_NONE) {
        LOG_E(fota_trigger, "[FOTA] Failed to read update info!\n\r");
        return false;
    }
	for (int i = 0; i < UPDATE_INFO_SIZE; i++) {
        if (update_info[i] != 0xFF) {
            LOG_E(fota_trigger, "\r\n[FOTA]fota is updating\n\r");
            return true;
      }
  }
	
    LOG_E(fota_trigger, "\r\n[FOTA]fota not updating\n\r");

    return false;
#else
    return isFotaExecuted();
#endif

}

bool fota_is_triggered(void)
{
    /* Check the FOTA update trigger information based on the tail of the FOTA buffer*/
    fota_status_t status = FOTA_ERROR_NONE;
    fota_entry_info_t ei;

#if BL_FOTA_TRIGGERED_ALWAYS_ON
    LOG_D(fota_trigger,  "fota always triggered\n\r");
    return true;
#endif

#ifdef FOTA_FS_ENABLE
    FRESULT res; /* fs status infor*/
    LOG_D(fota_trigger, "\r\nbegins to mount fs!\n\r");
    /* Mount the partition before it is accessed, and need only do it once. */
    res = f_mount(&fatfs_update, _T("0:"), 1);
    if (FR_OK != res) {
        LOG_E(fota_trigger, "\r\n[FOTA]Failed to mount the partition:%d\n\r",res);
        return false;
    }
    LOG_D(fota_trigger, "\r\n[FOTA]end to mount fs\n\r");
#endif

    status = fota_read_update_info(&ei, sizeof(fota_entry_info_t));
    if (status != FOTA_ERROR_NONE) {
		LOG_E(fota_trigger, "[FOTA] Failed to read update info!\n\r");
        return false;
    }
	  LOG_E(fota_trigger, "[FOTA] Get magic pattern:0X%X\n\r", ei.m_magic_ver);
    if ( (ei.m_magic_ver&0x00FFFFFF) != FOTA_MODE_MAGIC_PATTERN ) {
        LOG_E(fota_trigger, "[FOTA] Get error magic pattern:0X%X\n\r", ei.m_magic_ver);
        return false;
    }
	LOG_D(fota_trigger, "\r\n[FOTA] fota triggered\n\r");

#ifndef FOTA_FA_ENABLE
    hal_flash_status_t ret;
    /* erase the last 4k block in fota reserved partition */
	LOG_E(fota_trigger, "[FOTA_trigger] erase trigger flag\r\n");
    ret = hal_flash_erase(FOTA_RESERVED_PARTITION_END_ADDRESS - 4096, HAL_FLASH_BLOCK_4K);
    if (ret < HAL_FLASH_STATUS_OK)
    {
        LOG_E(fota_trigger, "[FOTA_SDK]erase 4k block fail, ret = %d\n", ret);
    }
#endif

    return true;
}
