
  
#include "./relay/bsp_relay.h"   


void RELAY_GPIO_Config(void)
{		

		GPIO_InitTypeDef GPIO_InitStructure;//定义初始化结构体


		RCC_AHB1PeriphClockCmd ( RELAY1_GPIO_CLK|
	                           RELAY2_GPIO_CLK|
	                           RELAY3_GPIO_CLK|
	                           RELAY4_GPIO_CLK, ENABLE); 
															   
		GPIO_InitStructure.GPIO_Pin = RELAY1_GPIO_PIN;	//设置输出的引脚号
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		//设置为输出模式
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;  //设置为推免模式
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;  //设置为下拉模式	
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;//设置输出速率

		GPIO_Init(RELAY1_GPIO_PORT, &GPIO_InitStructure);//串口初始化	    
														   
		GPIO_InitStructure.GPIO_Pin = RELAY2_GPIO_PIN;	//配置另外的引脚号
    GPIO_Init(RELAY2_GPIO_PORT, &GPIO_InitStructure);	
    
		GPIO_InitStructure.GPIO_Pin = RELAY3_GPIO_PIN;	
    GPIO_Init(RELAY3_GPIO_PORT, &GPIO_InitStructure);	
		
		GPIO_InitStructure.GPIO_Pin = RELAY4_GPIO_PIN;	
    GPIO_Init(RELAY4_GPIO_PORT, &GPIO_InitStructure);	
		
		GPIO_ResetBits(RELAY1_GPIO_PORT, RELAY1_GPIO_PIN);//引脚复位，输出低电平
		GPIO_ResetBits(RELAY2_GPIO_PORT, RELAY2_GPIO_PIN);
		GPIO_ResetBits(RELAY3_GPIO_PORT, RELAY3_GPIO_PIN);
		GPIO_ResetBits(RELAY4_GPIO_PORT, RELAY4_GPIO_PIN);
}
/*********************************************END OF FILE**********************/
