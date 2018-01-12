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
	BT_ID = 0,    //����ID��Ψһ
	MEMBER_ID,    //�����ID
	MEMBER_NAME,    //���������
	MEMBER_GENDER,    //������Ա�
	MEMBER_AGE,    //���������
	MEMBER_WEIGHT,    //���������
	RANGE_NORMAL_PPG,    //�������ʷ�Χ
	RANGE_NORMAL_BLOOD_OXYGEN,    //����Ѫ����Χ
	RANGE_NORMAL_EKG,     //����Ѫѹ��Χ
	EKG_PARAMETER,    //Ѫѹ��������
	STANDARD_TIME,    //ʱ��
	RUNNNING_STATUS,    //����״̬
	CALORIES_BURNED,    //�����ۼ����Ŀ�·��
	LAST_ERROR_INFO,    //ĩ�ι�����Ϣ
	LAST_WARNNING_INFO,    //ĩ�θ澯��Ϣ
	LAST_POSITION_TIME,    //ĩ��λ�ü�ʱ��
	LAST_VITAL_SIGNS_INFO,    //ĩ������������Ϣ
	GPS_SWITCH,    //GPS���ؿ���
	GPS_FREQ,    //GPS����Ƶ��
	GYRO_MODE,    //GYRO����ģʽ
	VITAL_SIGNS_SWITCH,    //��������оƬ���ؿ���
	VITAL_SIGNS_FREQ,    //��������оƬ����Ƶ��
	VITAL_SIGNS_COUNTER,     //��������оƬ���β���ԭʼֵ��Ŀ
	COMMUNICATION_AUTHENTICATION_CODE,    //������֤�루���ģ�
	COMMUNICATION_SECRET_KEY,    //ͨ����Կ
	BT_SWTICH,    //�������ؿ���
	BT_AUTHENTICATION_CODE,    //������֤��
	LORA_SWTICH,    //LORA���ؿ���
	LORA_MODE,    //LORA����ģʽ
	LORA_WORK_FREQ,    //LORA����Ƶ��
	LORA_FREQ_PARAMETER,    //LORA��Ƶ����
	LORA_ADDR,    //LORA�̵�ַ
	LORA_OVERTIME,    //LORA������ʱ
	WIFI_SWTICH,    //WIFI���ؿ���
	WIFI_NET_ID,    //WIFI����ID
	WIFI_NET_PASSWORD,    //WIFI�������
	MAGNETOMETER_SWITCH,    //�����ƿ��ؿ���
	CHEAT_PROOF_SWITCH,    //�����׿��ؿ���
	CLASS_ID,     //��Ŀ����
	TIME_WARM_UP,    //����ʱ��
	TIME_TRAIN_START,    //ѵ����ʼʱ��
	TIME_TRAIN_END,    //ѵ�����ʱ��
	TIME_RESTORE,    //�����ָ�ʱ��
	LEVEL_ACHIEVEMENT,    //�ɼ��ȼ�
	CLASS_ACHIEVEMENT,    //��Ŀ�ɼ�
	DISTANCE_TOTAL,    //��Ŀ�ۼ�λ������
	CLASS_CALORIES_BURNED_TOTAL,    //��Ŀ�ۼ����Ŀ�·��
	HISTORY_ERROR_COUNTER,    //��ʷ�������黺��Ԫ�ظ���
	HISTORY_NON_RETURN_ERROR_COUNTER,     //��ʷ�������黺��δ�ش�Ԫ�ظ���
	HISTORY_CLASS_COUNTER,    //��ʷ��ѵ��Ŀ����Ԫ�ظ���
	HISTORY_NON_RETURN_CLASS_COUNTER,     //��ʷ��ѵ��Ŀ����δ�ش�Ԫ�ظ���
	HISTORY_WARNNING_COUNTER,    //��ʷ�澯����Ԫ�ظ���
	HISTORY_NON_RETURN_WARNNING_COUNTER,    //��ʷ�澯����δ�ش�Ԫ�ظ���
	HISTORY_TRAJECTORY_COUNTRER,    //��ʷ�켣������Ԫ�ظ���
	HISTORY_NON_RETURN_TRAJECTORY_COUNTRER,     //��ʷ�켣������δ�ش�Ԫ�ظ���
	HISTORY_VITAL_SIGNS_COUNTRER,    //��ʷ������������Ԫ�ظ���
	HISTORY_NON_RETURN_VITAL_SIGNS_COUNTRER,    //��ʷ������������δ�ش�Ԫ�ظ���
	HISTORY_PPG_COUNTRER,    //��ʷ��������ԭʼPPG����Ԫ�ظ���
	HISTORY_NON_RETURN_PPG_COUNTRER    //��ʷ��������ԭʼPPG����δ�ش�Ԫ�ظ���
}device_param_t;


void lora_uart_init();
void lora_creat_task();

#ifdef __cplusplus
}
#endif

#endif/* __LORA_H__ */