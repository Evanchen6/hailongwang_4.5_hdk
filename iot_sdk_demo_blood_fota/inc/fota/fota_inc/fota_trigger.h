#ifndef __FOTA_TRIGGER_H__
#define __FOTA_TRIGGER_H__

#include "fota.h"
#include "stdint.h"
#include "stdbool.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    uint32_t m_magic_ver;
    uint32_t m_fota_triggered;
} fota_entry_info_t;

typedef enum {
    FOTA_ERROR_NONE = 0,
    FOTA_ERROR_FAIL
} fota_status_t;

fota_ret_t fota_mode_entry(void);
bool fota_is_updating(void);
bool fota_is_triggered(void);

#ifdef __clpusplus
}
#endif

#endif /* __FOTA_TRIGGER_H__ */