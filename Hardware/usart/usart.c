#include "systick.h"
#include "usart.h"		    

//接收缓冲区
uint8_t g_recv_buff[USART_RECEIVE_LENGTH];

//接收数据长度
uint16_t g_recv_length = 0;

//接收完成标志位
uint8_t  g_recv_complete_flag = 0;
/* -------------------------------------------------------------------------- */
//函数名称：uart_init
//函数功能：串口初始化
//传入参数：无
//返回值：无
//作者：lbm
//时间：2042.5.4
/* -------------------------------------------------------------------------- */
void usart_init(void)
{
	//开启时钟
	rcu_periph_clock_enable(RCU_USART0);//开启串口时钟
	rcu_periph_clock_enable(RCU_TX);
	rcu_periph_clock_enable(RCU_RX);

	//配置端口复用
	gpio_af_set(PORT_RX,GPIO_AF_1,GPIO_RX);
	gpio_af_set(PORT_TX,GPIO_AF_1,GPIO_TX);	 

	//配置GPIO模式
	gpio_mode_set(PORT_RX,GPIO_MODE_AF,GPIO_PUPD_PULLUP,GPIO_RX);//复用上拉模式
	gpio_mode_set(PORT_TX,GPIO_MODE_AF,GPIO_PUPD_PULLUP,GPIO_TX);//复用上拉模式

	//配置GPIO输出
	gpio_output_options_set(PORT_RX,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_RX);//推挽输出
	gpio_output_options_set(PORT_TX,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_TX);//推挽输出

	//配置串口
	usart_deinit(USART0);//复位串口
	usart_baudrate_set(USART0,BUAD_RATE);//设置波特率
	usart_parity_config(USART0,USART_PM_NONE);//没有校验位
	usart_word_length_set(USART0,USART_WL_8BIT);//8位数据位
	usart_stop_bit_set(USART0,USART_STB_1BIT);//1位停止位
	
	//使能串口
	usart_enable(USART0);//使能串口
	usart_receive_config(USART0,USART_RECEIVE_ENABLE);//使能接收
	usart_transmit_config(USART0,USART_TRANSMIT_ENABLE);//使能发送

	//串口中断配置
	usart_interrupt_enable(USART0,USART_INT_RBNE);//读数据缓存区非空中断和过载错误中断
	usart_interrupt_enable(USART0,USART_INT_IDLE);//DLE线检测中断
	nvic_irq_enable(USART0_IRQn,2);


	
	
	
}


/* -------------------------------------------------------------------------- */
/* -------------------------------------------------------------------------- */
void USART0_IRQHandler(void)
{    
    if(usart_interrupt_flag_get(USART0,USART_INT_FLAG_RBNE) != RESET) // 接收缓冲区不为空    
    {        
         g_recv_buff[g_recv_length++] = usart_data_receive(USART0);  // 把接收到的数据放到缓冲区中    
    }        
    if(usart_interrupt_flag_get(USART0,USART_INT_FLAG_IDLE) == SET) // 检测到帧中断    
    {        
        usart_data_receive(USART0); // 必须要读，读出来的值不能要        
        g_recv_buff[g_recv_length] = '\0';        
        g_recv_complete_flag = SET;// 接收完成        
    }
}


/* -------------------------------------------------------------------------- */
//函数名称：usart_send_data
//函数功能：发送一个字节
//传入参数：ucch，需要传入的字节
//返回值：无
//参考：嘉立创文档
//时间：2024.5.4
/* -------------------------------------------------------------------------- */
void usart_send_data(uint8_t ucch)
{
    usart_data_transmit(USART0, (uint8_t)ucch);  
    while(RESET == usart_flag_get(USART0, USART_FLAG_TBE)); // 等待发送数据缓冲区标志置位
}


/* -------------------------------------------------------------------------- */
//函数名称：usart_send_String
//函数功能：发送字符串
//传入参数：*ucstr，需要发送字符串的首地址
//返回值：无
//参考：嘉立创文档
//时间：2024.5.4
/* -------------------------------------------------------------------------- */
void usart_send_String(uint8_t *ucstr)
{   
      while(ucstr && *ucstr)  // 地址为空或者值为空跳出   
      {     
        usart_send_data(*ucstr++);    
      }
}


/* -------------------------------------------------------------------------- */
//重写fputc函数，能够将C语言中的printf函数打印到串口
/* -------------------------------------------------------------------------- */
int fputc(int ch, FILE *f)
{
    usart_data_transmit(USART0, (uint8_t) ch);
    while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
    return ch;
}
