# Microcontroladores

Este repositório contém o código-fonte e os esquemáticos das práticas desenvolvidas para a disciplina de **Microcontroladores** do curso de Engenharia de Computação **Universidade Federal do Ceará (UFC) - Campus Quixadá**.

As práticas são focadas na arquitetura ARM Cortex-M3, utilizando a placa de desenvolvimento **STM32F103C8T6 (Bluepill)** e programação em **Bare Metal** no ambiente STM32CubeIDE.

---

## 🚀 Práticas Realizadas

### 1. GPIO e Polling: Controle de LEDs com Botões
Nesta primeira prática, exploramos os fundamentos dos registros de GPIO (General Purpose Input/Output). O objetivo foi configurar pinos da Porta A como saídas digitais para controlar LEDs externos e pinos da Porta B como entradas digitais com resistores de *pull-up* internos. A lógica foi implementada via *polling*, onde o processador verifica continuamente o estado dos botões (registrador IDR) para atualizar o estado dos LEDs (registrador ODR).

### 2. Interrupções Externas (EXTI) e Manipulação de LED RGB
A segunda prática introduziu o conceito de interrupções externas (EXTI) e o controlador de interrupções de vetor aninhado (NVIC). Em vez de verificar os botões constantemente, o sistema foi configurado para reagir apenas em eventos de borda de descida (*falling edge*). Utilizamos três botões para alternar o estado (operação XOR/Toggle) de cada cor de um LED RGB, demonstrando como tratar diferentes canais de interrupção (EXTI0, EXTI1 e o canal compartilhado EXTI9_5) e a importância de limpar as *flags* de pendência no registrador PR.

### 3.Temporização por Hardware (SysTick) e Sequenciador de Cores RGB
Na terceira prática, utilizamos o temporizador interno do núcleo ARM, o SysTick, para criar uma base de tempo precisa sem bloquear a CPU com atrasos vazios. O temporizador foi configurado com um divisor de clock por 8 (AHB/8) para gerar interrupções periódicas a cada 1 segundo. A cada disparo do handler, uma variável contadora avança através de uma sequência de 0 a 7, aplicando uma máscara binária diretamente no registrador ODR da Porta A (pinos PA0, PA1 e PA2) para alternar ciclicamente entre as 8 combinações possíveis de cores do LED RGB.

---

## 🛠️ Hardware Utilizado
- **Microcontrolador:** STM32F103C8T6 (Bluepill)
- **Gravador:** ST-Link V2
- **Componentes:** LEDs coloridos, LED RGB (Catodo Comum), Resistores de 220Ω, Push-buttons e Protoboard.

## 💻 Software e Tecnologias
- **Linguagem:** C
- **IDE:** STM32CubeIDE
- **Toolchain:** arm-none-eabi-gcc
- **Estilo de Programação:** Bare Metal (Acesso direto a registradores)