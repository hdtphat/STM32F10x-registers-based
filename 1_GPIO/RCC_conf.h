#ifndef RCC_H
#define RCC_H

void SystemCLK_Init(void);
void APB1CLK_Init(uint8_t divide);
void APB2CLK_Init(uint8_t divide);

#endif