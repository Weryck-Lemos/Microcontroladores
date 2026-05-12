#include "stm32f1xx.h"


void EXTI0_IRQHandler(void);  // PB0
void EXTI1_IRQHandler(void);  // PB1
void EXTI9_5_IRQHandler(void); //PB5 ate PB9

int main(void) {
    //habilitar clock
    RCC->APB2ENR |= (1 << 2) | (1 << 3) | (1 << 0);

    //PA0, PA1, PA2 output
    GPIOA->CRL &= ~(0xFFF);
    GPIOA->CRL |=  (0x222);

    //PB0, PB1, PB5 input pull-up
    GPIOB->CRL &= ~( (0xF << 0) | (0xF << 4) | (0xF << 20) );
    GPIOB->CRL |=  ( (0x8 << 0) | (0x8 << 4) | (0x8 << 20) );
    GPIOB->ODR |=  (1 << 0) | (1 << 1) | (1 << 5); // ativa Pull-up

    //configurar AFIO para mapear os pinos como EXTI
    // AFIO->EXTICR[0] pinos 0 a 3. AFIO->EXTICR[1] pinos 4 a 7.
    AFIO->EXTICR[0] |= (0x1 << 0);  // mapeia PB0 para EXTI0
    AFIO->EXTICR[0] |= (0x1 << 4);  //mapeia PB1 para EXTI1
    AFIO->EXTICR[1] |= (0x1 << 4);  // mapeia PB5 para EXTI5

    //EXTI
    EXTI->FTSR |= (1 << 0) | (1 << 1) | (1 << 5); // trigger descida 0V
    EXTI->IMR  |= (1 << 0) | (1 << 1) | (1 << 5); // mascara de interrupcao

    //habilitar NVIC
    NVIC_EnableIRQ(EXTI0_IRQn);
    NVIC_EnableIRQ(EXTI1_IRQn);
    NVIC_EnableIRQ(EXTI9_5_IRQn); // PB5 compartilha esse canal com PB6-PB9

    while(1) {

        __WFI();
    }
}

void EXTI0_IRQHandler(void) {
    if (EXTI->PR & (1 << 0)) {    // verifica interrupção veio do pino 0
        GPIOA->ODR ^= (1 << 0);   // inverte o LED PA0
        EXTI->PR |= (1 << 0);     // limpa a flag de interrupção
    }
}

void EXTI1_IRQHandler(void) {
    if (EXTI->PR & (1 << 1)) {
        GPIOA->ODR ^= (1 << 1);
        EXTI->PR |= (1 << 1);
    }
}

void EXTI9_5_IRQHandler(void) {
    if (EXTI->PR & (1 << 5)) {
        GPIOA->ODR ^= (1 << 2);
        EXTI->PR |= (1 << 5);
    }
}
