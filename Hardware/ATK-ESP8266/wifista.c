#include "common.h"
#include "stdlib.h"
#include "wifista.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 

//ATK-ESP8266 WIFI STA����
//���ڲ���TCP/UDP����
//����ֵ:0,����
//    ����,�������
void atk_8266_wifista_test(void)
{ 
	atk_8266_send_cmd("AT+RST","OK",20);		//DHCP�������ر�(��APģʽ��Ч) 
	delay_ms(1000);         //��ʱ3S�ȴ������ɹ�
	delay_ms(1000);
	delay_ms(1000);
	atk_8266_send_cmd(CWJAP,"WIFI GOT IP",300);
	atk_8266_send_cmd("AT+CIPMUX=0","OK",20);   //0�������ӣ�1��������
	delay_ms(200);
	atk_8266_send_cmd(CIPSTART,"CONNECT",200);
	atk_8266_send_cmd(CIPSTART,"CONNECT",200);
	atk_8266_send_cmd(CIPSTART,"CONNECT",200);
	delay_ms(500);
	atk_8266_send_cmd("AT+CIPMODE=1","OK",200);      //����ģʽΪ��͸��
} 




























