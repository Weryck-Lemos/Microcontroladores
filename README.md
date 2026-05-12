# Microcontroladores

Este repositório contém o código-fonte e os esquemáticos das práticas desenvolvidas para a disciplina de **Microcontroladores** do curso de Engenharia de Computação **Universidade Federal do Ceará (UFC) - Campus Quixadá**.

As práticas são focadas na arquitetura ARM Cortex-M3, utilizando a placa de desenvolvimento **STM32F103C8T6 (Bluepill)** e programação em **Bare Metal** no ambiente STM32CubeIDE.

---

## 🚀 Práticas Realizadas

### 1. GPIO e Polling: Controle de LEDs com Botões
Nesta primeira prática, exploramos os fundamentos dos registros de GPIO (General Purpose Input/Output). O objetivo foi configurar pinos da Porta A como saídas digitais para controlar LEDs externos e pinos da Porta B como entradas digitais com resistores de *pull-up* internos. A lógica foi implementada via *polling*, onde o processador verifica continuamente o estado dos botões (registrador IDR) para atualizar o estado dos LEDs (registrador ODR).

### 2. Interrupções Externas (EXTI) e Manipulação de LED RGB
A segunda prática introduziu o conceito de interrupções externas (EXTI) e o controlador de interrupções de vetor aninhado (NVIC). Em vez de verificar os botões constantemente, o sistema foi configurado para reagir apenas em eventos de borda de descida (*falling edge*). Utilizamos três botões para alternar o estado (operação XOR/Toggle) de cada cor de um LED RGB, demonstrando como tratar diferentes canais de interrupção (EXTI0, EXTI1 e o canal compartilhado EXTI9_5) e a importância de limpar as *flags* de pendência no registrador PR.

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