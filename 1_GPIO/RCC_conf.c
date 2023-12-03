#include "stm32f10x.h"
#include <stdint.h>
#include "RCC_conf.h"

void SystemCLK_Init(void){
/*
	||	STEPS TO FOLLOW:
	||	1. enable HSE OSC and wait for it tobe ready:
	||	2. configure HSE divider for PLL entry
	||	3. adjust PLL entry clock source
	||	3. configure PLL multiplication
	||	4. adjust system clock switch
	||	5. configure AHB prescaler
	||
	||	*NOTE: System clock on STM32F103C8T6 is defaultly set at 72MHz, 
	||	so it is not neccesary to use this function just to set system clock to 72MHz
*/
	// enable HSE: quartz crystal 8MHz
	RCC->CR |= (1U<<16);
	// wait for HSE tobe ready
	while(!(RCC->CR & (1U<<17))){}
	// HSE divider for PLL entry: PLLXTPRE = 0 -> HSE is devided by 1 -> 8/1 = 8MHz
	RCC->CFGR &= ~(1U<<17);
	// PLL entry clock source: PLLSRC = 1 -> HSE OSC selected as PLL input clock
	RCC->CFGR |= (1U<<16);
	// PLL multiplication factor: PLLMUL = 0111b -> HSE is multipied by 9 -> 8*9 = 72MHz
	RCC->CFGR |= (7U<<18);
	// System clock switch: SW = 1 -> HSE selected as system clock
	RCC->CFGR |= (1U<<0);
	// AHB prescaler: HPRE = 0 -> HSE is devided by 1 -> 72/1 = 72MHz
	RCC->CFGR &= ~(15U<<4);	
}

void APB1CLK_Init(uint8_t divide){
/*
	||	if APB1 prescaler is divided by 1:
	||	Clock to TIM2,3,4,5,6,7,12,13,14 is APB1
	||	else:
	||	Clock to TIM2,3,4,5,6,7,12,13,14 is 2*APB1
	||
	||	WARNING: APB1 clock must not exceed 36MHz
*/
	// set APB1 prescaler
	switch (divide){
		case 0: // CLK_APB1 = SystemCLK / 1
			RCC->CFGR |= (0U<<8);  
			break;
		case 2: // CLK_APB1 = SystemCLK / 2
			RCC->CFGR |= (4U<<8);  
			break;
		case 4: // CLK_APB1 = SystemCLK / 4
			RCC->CFGR |= (5U<<8);  
			break;
		case 8: // CLK_APB1 = SystemCLK / 8
			RCC->CFGR |= (6U<<8);  
			break;
		case 16: // CLK_APB1 = SystemCLK / 16
			RCC->CFGR |= (7U<<8);  
			break;
	}
}

void APB2CLK_Init(uint8_t divide){
/*
	||	if APB2 prescaler is divided by 1:
	||	Clock to TIM1,8,9,10,11 is APB2
	||	else:
	||	Clock to TIM1,8,9,10,11 is 2*APB2
	||
	||	WARNING: APB2 clock must not exceed 72MHz
*/
	// set APB2 prescaler
	switch (divide){
		case 0: // CLK_APB2 = SystemCLK / 1
			RCC->CFGR |= (0U<<11);  
			break;
		case 2: // CLK_APB2 = SystemCLK / 2
			RCC->CFGR |= (4U<<11);  
			break;
		case 4: // CLK_APB2 = SystemCLK / 4
			RCC->CFGR |= (5U<<11);  
			break;
		case 8: // CLK_APB2 = SystemCLK / 8
			RCC->CFGR |= (6U<<11);  
			break;
		case 16: // CLK_APB2 = SystemCLK / 16
			RCC->CFGR |= (7U<<11);  
			break;
	}
}
