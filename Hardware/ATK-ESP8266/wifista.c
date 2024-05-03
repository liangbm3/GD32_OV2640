#include "common.h"
#include "stdlib.h"
#include "wifista.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////// 

//ATK-ESP8266 WIFI STA测试
//用于测试TCP/UDP连接
//返回值:0,正常
//    其他,错误代码
void atk_8266_wifista_test(void)
{ 
	atk_8266_send_cmd("AT+RST","OK",20);		//DHCP服务器关闭(仅AP模式有效) 
	delay_ms(1000);         //延时3S等待重启成功
	delay_ms(1000);
	delay_ms(1000);
	atk_8266_send_cmd(CWJAP,"WIFI GOT IP",300);
	atk_8266_send_cmd("AT+CIPMUX=0","OK",20);   //0：单连接，1：多连接
	delay_ms(200);
	atk_8266_send_cmd(CIPSTART,"CONNECT",200);
	atk_8266_send_cmd(CIPSTART,"CONNECT",200);
	atk_8266_send_cmd(CIPSTART,"CONNECT",200);
	delay_ms(500);
	atk_8266_send_cmd("AT+CIPMODE=1","OK",200);      //传输模式为：透传
} 




























