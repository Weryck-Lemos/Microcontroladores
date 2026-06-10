#include "stm32f1xx.h"

int adc_buffer[3] = {0, 0, 0};

void GPIO_Init(){
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;

    // A0, A1 e A2 entrada analogica
    GPIOA->CRL &= ~0xFFF;

    //A6 e PA7 saida push pull
    GPIOA->CRL &= ~0xFF000000;
    GPIOA->CRL |=  0xBB000000;

    //PB0 saida push pull
    GPIOB->CRL &= ~0xF;
    GPIOB->CRL |=  0xB;
}

void DMA_Init(){
    RCC->AHBENR |= RCC_AHBENR_DMA1EN; //clock DMA1

    DMA1_Channel1->CPAR = (uint32_t)&(ADC1->DR);  //origem dos dados
    DMA1_Channel1->CMAR = (uint32_t)adc_buffer;  //destino
    DMA1_Channel1->CNDTR = 3;                   //componente
    DMA1_Channel1->CCR = (1 << 10) | (1 << 8) | (1 << 7) | (1 << 5); //MSIZE, PSIZE, MINC, CIRC
    DMA1_Channel1->CCR |= DMA_CCR_EN;
}

void ADC_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    ADC1->SQR1 = (2 << 20);
    ADC1->SQR3 = (0 << 0) | (1 << 5) | (2 << 10);

    ADC1->CR1 |= ADC_CR1_SCAN;
    ADC1->CR2 |= ADC_CR2_DMA; 
    ADC1->CR2 |= ADC_CR2_ADON;
}

void TIM3_PWM_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
    TIM3->ARR = 4095;
    TIM3->PSC = 0;
    TIM3->CCMR1 |= (6 << 4) | (6 << 12);
    TIM3->CCMR1 |= TIM_CCMR1_OC1PE | TIM_CCMR1_OC2PE;
    TIM3->CCMR2 |= (6 << 4);
    TIM3->CCMR2 |= TIM_CCMR2_OC3PE;

    TIM3->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E;

    TIM3->CR1 |= TIM_CR1_CEN;
}


int main(void) {
    GPIO_Init();
    DMA_Init();
    ADC_Init();
    TIM3_PWM_Init();

    ADC1->CR2 |= ADC_CR2_ADON; //ADC ligado
    ADC1->CR2 |= ADC_CR2_CONT; // conversao continua
    ADC1->CR2 |= ADC_CR2_SWSTART;  //primeira conversao

    while(1) {
        TIM3->CCR1 = adc_buffer[0]; // vermelho(A6)
        TIM3->CCR2 = adc_buffer[1]; // verde (A7)
        TIM3->CCR3 = adc_buffer[2]; // azul (B0)
    }
}
