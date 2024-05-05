#include "timer.h"
#include "bsp_usart.h"

u8 ov_frame; 	//ͳ��֡��
//��ʱ��6�жϷ������	 
void TIM6_IRQHandler(void)
{ 		    		  			    
	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{				    
		printf("frame:%dfps\r\n",ov_frame);	//��ӡ֡��
		ov_frame=0;		    				   				     	    	
	}				   
	TIM_ClearITPendingBit(TIM6, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 	    
}
//������ʱ��6�жϳ�ʼ��
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��
//����ʹ�õ��Ƕ�ʱ��3!
void TIM6_Int_Init(u16 arr,u16 psc)
{
	//复位定时器
	timer_deinit(BSP_TIMER);
	
	//配置定时器结构体
	timer_parameter_struct timer_initpara;
	
}















