#include <stdint.h>
#include <stdlib.h>
#include "stm32f1xx.h"

#define CPU_CLK     8000000
#define BaudRate    115200

volatile uint16_t intensidade = 0;
volatile uint8_t subir = 1;
volatile uint8_t i = 0;
const int cores[7] = {1, 2, 4, 3, 6, 5, 7};

char ch = '\0';
uint8_t MAIN_SM = 0;

uint8_t modo_demo = 0;
char rx_buffer[10];
uint8_t rx_idx = 0;

void delay_simulado(volatile uint32_t tempo) {
    while(tempo--);
}

void simular_comando(const char* str) {
    while(*str) {
        ch = *str;
        MAIN_SM = 1;

        if(MAIN_SM) {
            MAIN_SM = 0;
            if (ch == '\n' || ch == '\r') {
                if (rx_idx > 0) {
                    rx_buffer[rx_idx] = '\0';
                    if (rx_buffer[0] == 'd' || rx_buffer[0] == 'D') {
                        modo_demo = !modo_demo;
                        if (!modo_demo) {
                            TIM3->CCR1 = 0; TIM3->CCR2 = 0; TIM3->CCR3 = 0;
                        }
                    }
                    else if (!modo_demo && rx_idx >= 3) {
                        int valor_porcentagem = atoi(&rx_buffer[1]);
                        if (valor_porcentagem > 99) valor_porcentagem = 99;
                        if (valor_porcentagem < 0)  valor_porcentagem = 0;
                        uint16_t ccr_val = (valor_porcentagem * 4095) / 99;
                        switch(rx_buffer[0]) {
                            case 'R': case 'r': TIM3->CCR1 = ccr_val; break;
                            case 'G': case 'g': TIM3->CCR2 = ccr_val; break;
                            case 'B': case 'b': TIM3->CCR3 = ccr_val; break;
                        }
                    }
                    rx_idx = 0;
                }
            }
            else if (rx_idx < sizeof(rx_buffer) - 1) {
                rx_buffer[rx_idx++] = ch;
            }
        }
        str++;
    }
}

void TIM2_IRQHandler() {
    if (TIM2->SR & TIM_SR_UIF) {
        TIM2->SR &= ~TIM_SR_UIF;
        if (!modo_demo) return;

        uint8_t cor = cores[i];
        TIM3->CCR1 = (cor & 1)? intensidade : 0;
        TIM3->CCR2 = (cor & 2)? intensidade : 0;
        TIM3->CCR3 = (cor & 4)? intensidade : 0;

        if (subir){
            intensidade += 15;
            if (intensidade >= 4095) { intensidade = 4095; subir = 0; }
        }
        else {
            if (intensidade >= 15) {
                intensidade -= 15;
            }
            else {
                intensidade = 0; subir = 1; i = (i+1)%7;
            }
        }
    }
}

void USART1_IRQHandler(void) {
    if((USART1->SR & USART_SR_RXNE)) {
        ch = USART1->DR;
        MAIN_SM = 1;
    }
}

int main(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_AFIOEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN | RCC_APB1ENR_TIM3EN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    GPIOA->CRL &= ~0xFF000000;
    GPIOA->CRL |=  0xBB000000;
    GPIOA->CRH &= ~0x00000F00;
    GPIOA->CRH |=  0x00000400;
    GPIOB->CRL &= ~0x0000000F;
    GPIOB->CRL |=  0x0000000B;

    TIM3->ARR = 4095;
    TIM3->PSC = 0;
    TIM3->CCMR1 &= ~((0x7F << 4) | (0x7F << 12));
    TIM3->CCMR1 |= (6 << 4) | (6 << 12) | TIM_CCMR1_OC1PE | TIM_CCMR1_OC2PE;
    TIM3->CCMR2 &= ~(0x7F << 4);
    TIM3->CCMR2 |= (6 << 4) | TIM_CCMR2_OC3PE;
    TIM3->CCER |= TIM_CCER_CC1E | TIM_CCER_CC2E | TIM_CCER_CC3E;
    TIM3->EGR |= TIM_EGR_UG;
    TIM3->CR1 |= TIM_CR1_CEN;

    TIM2->PSC = 799;
    TIM2->ARR = 50;
    TIM2->DIER |= TIM_DIER_UIE;
    NVIC_EnableIRQ(TIM2_IRQn);
    TIM2->CR1 |= TIM_CR1_CEN;

    USART1->CR1 |= USART_CR1_RE;
    USART1->BRR = ((CPU_CLK + (BaudRate/2U))/BaudRate);
    USART1->CR1 |= USART_CR1_RXNEIE;
    NVIC_EnableIRQ(USART1_IRQn);
    USART1->CR1 |= USART_CR1_UE;

    while(1) {
        simular_comando("d\r");
        delay_simulado(4000000);

        simular_comando("d\r");
        delay_simulado(1000000);

        simular_comando("r10\r");
        delay_simulado(2000000);

        simular_comando("g99\r");
        delay_simulado(2000000);

        simular_comando("b50\r");
        delay_simulado(3000000);

        simular_comando("r00\r");
        simular_comando("g00\r");
        simular_comando("b00\r");
        delay_simulado(1000000);
    }
}
