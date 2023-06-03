#include "stm32f10x.h"
#include "GPIO_STM32F10x.h"
#include <math.h>

//GPIO_config
void GPIO_config(){

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB,  ENABLE);
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO,  ENABLE);
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3,ENABLE );
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;             

  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;  

  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
}

//TIM_config
void TIM_config(){
//TIM
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	TIM_TimeBaseInitStruct.TIM_Prescaler=15;         

  TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;       

  TIM_TimeBaseInitStruct.TIM_Period=255;            
 
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
//OC(output compare)
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM2;        /*!< Specifies the TIM mode.
                                   This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes */

  TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;   /*!< Specifies the TIM Output Compare state.
                                   This parameter can be a value of @ref TIM_Output_Compare_state */
  

  TIM_OCInitStruct.TIM_Pulse=0;         /*!< Specifies the pulse value to be loaded into the Capture Compare Register. 
                                   This parameter can be a number between 0x0000 and 0xFFFF */

  TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_Low;    /*!< Specifies the output polarity.
                                   This parameter can be a value of @ref TIM_Output_Compare_Polarity */

	
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);	
	TIM_OC3Init(TIM3,&TIM_OCInitStruct);
	TIM_OC4Init(TIM3,&TIM_OCInitStruct);
	
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	TIM_Cmd(TIM3,ENABLE);
	
}

void delay(int us){

	while(us--){
		int count=9;
		while(count--);
	}
}

void light(float r,float g,float b){

	TIM3->CCR2=r;
	TIM3->CCR3=g;
	TIM3->CCR4=b;
	
}
float ddd=0;
int main(void){
	GPIO_config();
	TIM_config();
	
	float value=0;
	while(1){
		value=sin(ddd)*128+128;
		ddd+=0.001;
		light(value,value,value);
		delay(0xFFFFF);
	}
	
}

void SystemInit(void)
{	
}




/*********************************************END OF FILE**********************/
