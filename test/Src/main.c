#include "stm32f1xx.h"

// Função de delay simples
void delay(volatile uint32_t tempo) {
    while(tempo--) {
        __NOP();
    }
}

int main(void) {
    // 1. Habilitar o Clock para o Portal GPIOA
    // No registrador RCC_APB2ENR, o bit 2 ativa a Porta A
    RCC->APB2ENR |= (1 << 2);

    // 2. Configurar PA1, PA2 e PA3 como Saída
    // O registrador CRL configura os pinos 0 a 7. Cada pino ocupa 4 bits.
    // PA1 (bits 4-7), PA2 (bits 8-11), PA3 (bits 12-15)
    // 0x2 significa "Output mode, max speed 2 MHz, Push-pull"
    GPIOA->CRL &= ~(0x0000FFF0); // Limpa as configurações atuais destes 3 pinos
    GPIOA->CRL |=  (0x00002220); // Define 0x2 para PA1, PA2 e PA3

    while(1) {
        // Ligar PA1 e desligar os outros
        GPIOA->ODR = (1 << 1);
        delay(500000);

        // Ligar PA2 e desligar os outros
        GPIOA->ODR = (1 << 2);
        delay(500000);

        // Ligar PA3 e desligar os outros
        GPIOA->ODR = (1 << 3);
        delay(500000);
    }
}
