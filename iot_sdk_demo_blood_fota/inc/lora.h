#ifndef __LORA_H__
#define __LORA_H__

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct{
	uint16_t length;
	uint8_t type;
	uint8_t data[17];
} spp_message_ex_t;

typedef struct{
	uint16_t start;
	uint16_t addr;
	uint32_t keycode;
	spp_message_ex_t spp_message;
	uint16_t crccode;
} lora_message_t;

typedef enum {
    MSG_ID_LORA_READY_TO_READ = 0,
    MSG_ID_LORA_READY_TO_WRITE,
    MSG_ID_LORA_END
} lora_msg_id_t;


typedef struct {
    lora_msg_id_t msg_id;
    uint8_t* msg_data;
} lora_general_msg_t;

typedef enum{
	SINGLE_READ = 0x01,
	SINGLE_WRITE,
	MULTIPLY_READ,
	MULTIPLY_WRITE,
	CHANNEL_CHANGE
} command_type_t;

typedef enum{
	BT_ID = 0,    //蓝牙ID，唯一
	MEMBER_ID,    //佩戴人ID
	MEMBER_NAME,    //佩戴人姓名
	MEMBER_GENDER,    //佩戴人性别
	MEMBER_AGE,    //佩戴人年龄
	MEMBER_WEIGHT,    //佩戴人体重
	RANGE_NORMAL_PPG,    //正常心率范围
	RANGE_NORMAL_BLOOD_OXYGEN,    //正常血氧范围
	RANGE_NORMAL_EKG,     //正常血压范围
	EKG_PARAMETER,    //血压特征参数
	STANDARD_TIME,    //时间
	RUNNNING_STATUS,    //运行状态
	CALORIES_BURNED,    //当日累计消耗卡路里
	LAST_ERROR_INFO,    //末次故障信息
	LAST_WARNNING_INFO,    //末次告警信息
	LAST_POSITION_TIME,    //末次位置及时间
	LAST_VITAL_SIGNS_INFO,    //末次生命体征信息
	GPS_SWITCH,    //GPS开关控制
	GPS_FREQ,    //GPS采样频率
	GYRO_MODE,    //GYRO工作模式
	VITAL_SIGNS_SWITCH,    //生命体征芯片开关控制
	VITAL_SIGNS_FREQ,    //生命体征芯片采样频率
	VITAL_SIGNS_COUNTER,     //生命体征芯片单次采样原始值数目
	COMMUNICATION_AUTHENTICATION_CODE,    //单播认证码（明文）
	COMMUNICATION_SECRET_KEY,    //通信密钥
	BT_SWTICH,    //蓝牙开关控制
	BT_AUTHENTICATION_CODE,    //蓝牙认证码
	LORA_SWTICH,    //LORA开关控制
	LORA_MODE,    //LORA工作模式
	LORA_WORK_FREQ,    //LORA工作频率
	LORA_FREQ_PARAMETER,    //LORA扩频参数
	LORA_ADDR,    //LORA短地址
	LORA_OVERTIME,    //LORA单播超时
	WIFI_SWTICH,    //WIFI开关控制
	WIFI_NET_ID,    //WIFI网络ID
	WIFI_NET_PASSWORD,    //WIFI网络口令
	MAGNETOMETER_SWITCH,    //磁力计开关控制
	CHEAT_PROOF_SWITCH,    //防作弊开关控制
	CLASS_ID,     //科目代码
	TIME_WARM_UP,    //热身时间
	TIME_TRAIN_START,    //训练开始时间
	TIME_TRAIN_END,    //训练完成时间
	TIME_RESTORE,    //体征恢复时间
	LEVEL_ACHIEVEMENT,    //成绩等级
	CLASS_ACHIEVEMENT,    //课目成绩
	DISTANCE_TOTAL,    //课目累计位移米数
	CLASS_CALORIES_BURNED_TOTAL,    //课目累计消耗卡路里
	HISTORY_ERROR_COUNTER,    //历史故障数组缓存元素个数
	HISTORY_NON_RETURN_ERROR_COUNTER,     //历史故障数组缓存未回传元素个数
	HISTORY_CLASS_COUNTER,    //历史组训课目数组元素个数
	HISTORY_NON_RETURN_CLASS_COUNTER,     //历史组训课目数组未回传元素个数
	HISTORY_WARNNING_COUNTER,    //历史告警数组元素个数
	HISTORY_NON_RETURN_WARNNING_COUNTER,    //历史告警数组未回传元素个数
	HISTORY_TRAJECTORY_COUNTRER,    //历史轨迹点数组元素个数
	HISTORY_NON_RETURN_TRAJECTORY_COUNTRER,     //历史轨迹点数组未回传元素个数
	HISTORY_VITAL_SIGNS_COUNTRER,    //历史生命体征数组元素个数
	HISTORY_NON_RETURN_VITAL_SIGNS_COUNTRER,    //历史生命体征数组未回传元素个数
	HISTORY_PPG_COUNTRER,    //历史生命体征原始PPG数组元素个数
	HISTORY_NON_RETURN_PPG_COUNTRER    //历史生命体征原始PPG数组未回传元素个数
}device_param_t;


void lora_uart_init();
void lora_creat_task();

#ifdef __cplusplus
}
#endif

#endif/* __LORA_H__ */