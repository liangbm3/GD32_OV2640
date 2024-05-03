#ifndef __SCCB_H
#define __SCCB_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ο�������guanfu_wang���롣
//ALIENTEK STM32F103������ 
//SCCB ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/4/16
//�汾��V1.0		    							    							  
//////////////////////////////////////////////////////////////////////////////////
 
 
#define SCCB_SDA_IN()  {GPIOB->CRH&=0XFF0FFFFF;GPIOB->CRH|=0X00800000;}
#define SCCB_SDA_OUT() {GPIOB->CRH&=0XFF0FFFFF;GPIOB->CRH|=0X00300000;}

//IO��������	 
#define SCCB_SCL    		PDout(3)	 	//SCL
#define SCCB_SDA    		PBout(13) 		//SDA	 

#define SCCB_READ_SDA    	PBin(13)  		//����SDA    
#define SCCB_ID   			0X60  			//OV2640��ID

///////////////////////////////////////////
void SCCB_Init(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void SCCB_No_Ack(void);
u8 SCCB_WR_Byte(u8 dat);
u8 SCCB_RD_Byte(void);
u8 SCCB_WR_Reg(u8 reg,u8 data);
u8 SCCB_RD_Reg(u8 reg);
#endif













