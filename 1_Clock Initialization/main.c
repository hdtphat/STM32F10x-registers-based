#include "stm32f10x.h"
#include "RCC_conf.h"
#include <stdint.h>

void TIM4_Init(void);
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);

int main(void){
	// init system clock to 72MHZ (default: 72MHz, dont need to use this);
	SystemCLK_Init();
	// Set APB1 prescaler to 1/8 => Fapb1 = 72/8 => clock before TIM4 = 72/8x2 = 18MHz
	APB1CLK_Init(8);
	
	// enable clock to portA andAFIO
	RCC->APB2ENR |= (1U<<0) | (1U<<2);
	// set PA1 as output and turn off PA1
	GPIOA->CRL &= ~(0x0FU<<4);
	GPIOA->CRL |= (2U<<4);
	GPIOA->ODR = 0;
	// Init timer 4 for delay_ms() and delay_us()
	TIM4_Init();

	while(1){
		// turn on PA1
		GPIOA->ODR |= 1<<1;
		delay_ms(500);	
		// turn off PA1
		GPIOA->ODR &= ~(1U<<1);
		delay_ms(500);
	}
}

void TIM4_Init(void){
	// enable clock to TIM4
	RCC->APB1ENR |= 1<<2;
	// set TIM4 prescaler to 1/18 => TIM4 clock = 18/18 = 1MHz => 1 count cost 1us => 1000 count = 1000us = 1ms
	TIM4->PSC = 18-1;
	// config max counting value
	TIM4->ARR = 0xFFFF;
	// reset counter
	TIM4->CNT = 0;
	// enable counter 
	TIM4->CR1 |= (1<<0);	
}

void delay_us(uint32_t us){
	// reset counter
	TIM4->CNT = 0;
	// wait for counter to reach the setpoint
	while(TIM4->CNT <us){}
}

void delay_ms(uint32_t ms){
	for(uint32_t i=0; i<ms; i++){
		// delay 1000us = 1ms
		delay_us(1000); 
	}
}
