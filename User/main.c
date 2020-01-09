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

//�����Ƿ�ʹ��LCD������ʾ������Ҫ�Ļ��������ע�͵�����
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
	RELAY_GPIO_Config();//�̵����ӿڳ�ʼ��
	SysTick_Init();	 
	Rheostat_Init();//AD��ʼ��
  LED_GPIO_Config();
	TIMx_Configuration(); // ��ʼ���߼����ƶ�ʱ����ʱ��1s����һ���ж�
	
		
	#ifdef USE_LCD_DISPLAY	
		 /*��ʼ��Һ����*/
		LCD_Init();
		LCD_LayerInit();
		LTDC_Cmd(ENABLE);
		
		/*�ѱ�����ˢ��ɫ*/
		LCD_SetLayer(LCD_BACKGROUND_LAYER);  
		LCD_Clear(LCD_COLOR_BLACK);
		
		/*��ʼ����Ĭ��ʹ��ǰ����*/
		LCD_SetLayer(LCD_FOREGROUND_LAYER); 
		/*Ĭ�����ò�͸��	���ú�������Ϊ��͸���ȣ���Χ 0-0xff ��0Ϊȫ͸����0xffΪ��͸��*/
		LCD_SetTransparency(0xFF);
		LCD_Clear(LCD_COLOR_BLACK);
		
			/*����������ɫ������ı�����ɫ*/
		LCD_SetColors(LCD_COLOR_RED,LCD_COLOR_BLACK);	

		/*Ӣ������*/
		LCD_SetFont(&Font16x24); 	
		
		LCD_DisplayStringLine(LINE(1),(uint8_t* )"           This is a MPU6050 demo       ");	
		LCD_DisplayStringLine(LINE(2),(uint8_t* )"                (python version)       ");	


	#endif
	 /*��ʼ��USART1*/
  Debug_USART_Config();

	
	EXTI_MPU_Config();
	
		// Configure I2C
	I2cMaster_Init(); 

	
	//MPU_DEBUG("F4 MPU6050 test");
	mpu6050_init();
	


  while(1)
		{
			Data_mpu6050();//mpu6050���ݲɼ�
    }
}




/*********************************************END OF FILE**********************/

