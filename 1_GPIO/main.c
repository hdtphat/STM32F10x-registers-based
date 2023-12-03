#include "stm32f10x.h"                  // Device header
#include "RCC_conf.h"
#include <stdint.h>

void GPIO_Init(void);

int main(void){
	// set system clock at 72MHz and APB2 at 36MHz
	SystemCLK_Init();
	APB2CLK_Init(2);
	// set up GPIO pin
	GPIO_Init();
	
	while(1){
		// if PB2 is low, then turn on PA1
		if(!(GPIOB->IDR & (1U<<3))){
			GPIOA->ODR |= (1U<<1);
		// else turn off PA1
		} else {
			GPIOA->ODR &= ~(1U<<1);
		}
	}
}

void GPIO_Init(void){
	// enable clock to GPIOA and GPIOB
	RCC->APB2ENR |= (1U<<2) | (1U<<3);
	// set PA1 as output
	GPIOA->CRL &= ~(0x0FU<<4); // clear bit4~7
	GPIOA->CRL |= (2U<<4); // MODE 0b10: Output mode, max speed 2 MHz
	GPIOA->CRL |= (0U<<6); // CNF 0b00: General purpose output push-pull
	// set PB2 as input
	GPIOB->CRL &= ~(0x0FU<<8); // clear bit8~11
	GPIOB->CRL |= (0U<<8); // MODE 0b00: Input mode (reset state)
	GPIOB->CRL |= (1U<<10); // CNF 0b01: Floating input (reset state)
	// turn off PA1
	GPIOA->ODR &= ~(1U<<1);
}
