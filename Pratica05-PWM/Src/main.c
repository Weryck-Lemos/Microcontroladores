#include "stm32f1xx.h"

volatile uint16_t intensidade = 0;
volatile uint8_t subir = 1;
volatile uint8_t i = 0;
const int cores[7] = {1,2, 4, 3, 6, 5, 7};

void TIM2_IRQHandler() {
    if (TIM2->SR & TIM_SR_UIF) {
        TIM2->SR &= ~TIM_SR_UIF;

        uint8_t cor = cores[i];

        TIM3->CCR1 = (cor & 1)? intensidade : 0;
        TIM3->CCR2 = (cor & 2)? intensidade : 0;
        TIM3->CCR3 = (cor & 4)? intensidade : 0;

        if (subir){
            intensidade += 15;
            if (intensidade >= 4095) {
                intensidade = 4095;
                subir = 0;
            }
        }
        else{
            if (intensidade >= 15) {
                intensidade -= 15;
            }
            else {
                intensidade = 0;
                subir = 1;
                i = (i+1)%7;
            }
        }
    }
}

void GPIO_Init(){
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;

    GPIOA->CRL &= ~0xFF000000;
    GPIOA->CRL |=  0xBB000000;
    GPIOB->CRL &= ~0x0000000F;
    GPIOB->CRL |=  0x0000000B;
}

void TIM3_PWM_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

    TIM3->ARR = 4095;
    TIM3->PSC = 0;

    TIM3->CCMR1 &= ~((0x7F << 4) | (0x7F << 12));
    TIM3->CCMR1 |= (6 << 4) | (6 << 12) | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2PE;

    TIM3->CCMR2 &= ~(0x7F << 4);
    TIM3->CCMR2 |= (6 << 4) | TIM_CCMR2_OC3PE;

    TIM3->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E;
    TIM3->EGR |= TIM_EGR_UG;
    TIM3->CR1 |= TIM_CR1_CEN;
}

void TIM2_BaseTempo_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
    TIM2->PSC = 799;
    TIM2->ARR = 50;
    TIM2->DIER |= TIM_DIER_UIE;
    NVIC_EnableIRQ(TIM2_IRQn);
    TIM2->CR1 |= TIM_CR1_CEN;
}

int main(void) {
    GPIO_Init();
    TIM3_PWM_Init();
    TIM2_BaseTempo_Init();

    while(1) {
    }
}
