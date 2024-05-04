#include "gd32e23x.h"
#include "systick.h"
#include <stdio.h>
#include "main.h"

#define TX GPIO_PIN_9
#define RX GPIO_PIN_10

void usart_send_data(uint8_t ucch);
void usart_send_String(uint8_t *ucstr);
int fputc(int ch, FILE *f);
int i=0;
int main(void)
{
        systick_config();//用来设置定时时间
        rcu_periph_clock_enable(RCU_GPIOC);//使能GPIOC的时钟
        rcu_periph_clock_enable(RCU_GPIOA);//使能GPIOA的时钟
        rcu_periph_clock_enable(RCU_USART0);//使能串口0的时钟
        gpio_af_set(GPIOA,GPIO_AF_1,TX);//设置端口复用
        gpio_af_set(GPIOA,GPIO_AF_1,RX);//设置端口复用
        gpio_mode_set(GPIOC,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_PIN_13);//设置13号端口输出浮空模式
        gpio_mode_set(GPIOA,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO_PIN_7);//设置7号端口输出浮空模式
        gpio_mode_set(GPIOA,GPIO_MODE_AF,GPIO_PUPD_PULLUP,TX);//设置9号端口复用上拉模式
        gpio_mode_set(GPIOA,GPIO_MODE_AF,GPIO_PUPD_PULLUP,RX);//设置10号端口复用上拉模式
        gpio_output_options_set(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,RX);//设置10号端口推挽输出，50Hz
        gpio_output_options_set(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,TX);//设置9号端口推挽输出、50Hz
        gpio_output_options_set(GPIOC,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_13);//设置13号端口推挽输出、50Hz
        gpio_output_options_set(GPIOA,GPIO_OTYPE_PP,GPIO_OSPEED_50MHZ,GPIO_PIN_7);//设置7号端口推挽输出、50Hz

        usart_deinit(USART0);
        usart_baudrate_set(USART0,115200);
        usart_parity_config(USART0,USART_PM_NONE);
        usart_word_length_set(USART0,USART_WL_8BIT);
        usart_stop_bit_set(USART0,USART_STB_1BIT);
        
        usart_transmit_config(USART0,USART_TRANSMIT_ENABLE);
        usart_receive_config(USART0,USART_RECEIVE_ENABLE);
        usart_enable(USART0);
        usart_send_data('h');
        usart_send_data('e');
        usart_send_data('l');
        usart_send_data('l');
        usart_send_data('o');
        
        while(1)
        {
                gpio_bit_write(GPIOA,GPIO_PIN_7, 0);
                delay_1ms(200);
                gpio_bit_write(GPIOA,GPIO_PIN_7, 1);
		delay_1ms(200);
                gpio_bit_write(GPIOC,GPIO_PIN_13, 0);
                delay_1ms(1000);
                gpio_bit_write(GPIOC,GPIO_PIN_13, 1);
		delay_1ms(1000);
                printf("I love you");
        }
}

void usart_send_data(uint8_t ucch)
{
    usart_data_transmit(USART0, (uint8_t)ucch);  
    while(RESET == usart_flag_get(USART0, USART_FLAG_TBE)); // 等待发送数据缓冲区标志置位
}

void usart_send_String(uint8_t *ucstr)
{   
      while(ucstr && *ucstr)  // 地址为空或者值为空跳出   
      {     
        usart_send_data(*ucstr++);    
      }
}
int fputc(int ch, FILE *f)
{
    usart_data_transmit(USART0, (uint8_t) ch);
    while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
    return ch;
}