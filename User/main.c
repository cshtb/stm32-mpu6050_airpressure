/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2020-01-7
  * @brief   https://github.com/cshtb/stm32_control.git
  ******************************************************************************

  ******************************************************************************
  */
 
/* Includes ------------------------------------------------------------------*/
#include "./adc/bsp_adc.h"
#include "stm32f4xx.h"
#include "./usart/bsp_debug_usart.h"
#include "./led/bsp_led.h"
#include "./systick/bsp_SysTick.h"
#include "./i2c/i2c.h"
#include "./mpu6050/bsp_mpu_exti.h"
#include "./relay/bsp_relay.h"  
#include "./tim/bsp_advance_tim.h"
#include "./data_analysis/analysis.h"

//设置是否使用LCD进行显示，不需要的话把这个宏注释掉即可
#define USE_LCD_DISPLAY
#define USE_USART_DISPLAY

#ifdef USE_LCD_DISPLAY
 #include "./lcd/bsp_lcd.h"
#endif

#include "stdio.h"
#include "common.h"
    
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "invensense.h"
#include "invensense_adv.h"
#include "eMPL_outputs.h"
#include "mltypes.h"
#include "mpu.h"
#include "log.h"
#include "packet.h"
/* Private typedef -----------------------------------------------------------*/
/* Data read from MPL. */


/**
  * @brief main entry point.
  * @par Parameters None
  * @retval void None
  * @par Required preconditions: None
  */
                                  
int main(void)
{ 

#ifdef COMPASS_ENABLED
    unsigned char new_compass = 0;
    unsigned short compass_fsr;
#endif
	RELAY_GPIO_Config();//继电器接口初始化
	SysTick_Init();	 
	Rheostat_Init();//AD初始化
  LED_GPIO_Config();
	TIMx_Configuration(); // 初始化高级控制定时器定时，1s产生一次中断
	
		
	#ifdef USE_LCD_DISPLAY	
		 /*初始化液晶屏*/
		LCD_Init();
		LCD_LayerInit();
		LTDC_Cmd(ENABLE);
		
		/*把背景层刷黑色*/
		LCD_SetLayer(LCD_BACKGROUND_LAYER);  
		LCD_Clear(LCD_COLOR_BLACK);
		
		/*初始化后默认使用前景层*/
		LCD_SetLayer(LCD_FOREGROUND_LAYER); 
		/*默认设置不透明	，该函数参数为不透明度，范围 0-0xff ，0为全透明，0xff为不透明*/
		LCD_SetTransparency(0xFF);
		LCD_Clear(LCD_COLOR_BLACK);
		
			/*设置字体颜色及字体的背景颜色*/
		LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_BLACK);	

		/*英文字体*/
		LCD_SetFont(&Font16x24); 	
		
		LCD_DisplayStringLine(LINE(1),(uint8_t* )"           This is a MPU6050 demo       ");	
		LCD_DisplayStringLine(LINE(2),(uint8_t* )"                (python version)       ");	


	#endif
	 /*初始化USART1*/
  Debug_USART_Config();

	
	EXTI_MPU_Config();
	
		// Configure I2C
	I2cMaster_Init(); 

	
	//MPU_DEBUG("F4 MPU6050 test");
	mpu6050_init();
	


  while(1)
		{
			Data_mpu6050();//mpu6050数据采集
    }
}




/*********************************************END OF FILE**********************/

