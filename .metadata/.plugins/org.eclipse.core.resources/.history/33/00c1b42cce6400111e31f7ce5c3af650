

#include <stdint.h>
#include "color.h"
#include "gpio.h"
#include "stm32f1xx.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


/*
 * SysTick_Handler interrupt handler
 */

int SysTick_TASK = 0;
uint32_t count = 0;
const uint32_t color_table[] = { off, red, green, blue, yellow, cyan, purple, white };

static inline void Gpio_Init(void) {
	RCC->APB2ENR |= (1 << 2);
    // PA11
    GPIOA->CRH &= ~((uint32_t)0xF << ((PA11 - 8) * 4));
    GPIOA->CRH |=  ((uint32_t)GPIO_OUTPUT_2MHZ_PP << ((PA11 - 8) * 4));
    GPIOA->ODR &= ~(1 << PA11);

    // PA12
    GPIOA->CRH &= ~((uint32_t)0xF << ((PA12 - 8) * 4));
    GPIOA->CRH |=  ((uint32_t)GPIO_OUTPUT_2MHZ_PP << ((PA12 - 8) * 4));
    GPIOA->ODR &= ~(1 << PA12);

    // PA15
	RCC->APB2ENR |= (1 << 0);
	AFIO->MAPR |= (2 << 24);
    GPIOA->CRH &= ~((uint32_t)0xF << ((PA15 - 8) * 4));
    GPIOA->CRH |=  ((uint32_t)GPIO_OUTPUT_2MHZ_PP << ((PA15 - 8) * 4));
    GPIOA->ODR &= ~(1 << PA15);

}


static inline void Switch_Color(void) {
    GPIOA->ODR &= ~((1 << 11) | (1 << 12) | (1 << 15));
    GPIOA->ODR |= color_table[count];
    count = (count + 1) % 8;
}

void SysTick_Handler(void)
{
	// Do stuff
	SysTick_TASK = 1;
}

int main(void)
{


	Gpio_Init();

	 /*System Tick Configuration
	 * Initializes the System Timer and its interrupt, and starts the System Tick Timer.
     * Counter is in free running mode to generate periodic interrupts.
	 */
	uint32_t ticks = 1000000; //ticks  Number of ticks between two interrupts, should be less than 0xFFFFFFUL = 16777216  (24bits)
	if ((ticks - 1UL) <= 0xFFFFFFUL)
	{
		 /* set reload register */
		SysTick->LOAD  = (uint32_t)(ticks - 1UL);

		SysTick->VAL   = 0UL;			/* Load the SysTick Counter Value */

		SysTick->CTRL  = (0 << 2) |		/* 0 -> SysTick_Clock = AHB/8 */
						 (1 << 1) |	 	/* Enable SysTick IRQ and SysTick Timer */
						 (1 << 0);
	}

	while(1)
	{
		if(SysTick_TASK)
		{
			SysTick_TASK = 0;
			Switch_Color();
		}
	}
}
