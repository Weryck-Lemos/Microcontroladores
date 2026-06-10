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

### 4. Temporização por Hardware (SysTick) e Sequenciador Complexo RGB
Na terceira prática, exploramos o temporizador interno do núcleo ARM, o SysTick, para criar uma base de tempo precisa por hardware, evitando o uso de loops de atraso que bloqueiam a CPU. Configurando o temporizador com um divisor de clock por 8 (AHB/8) e uma recarga de 1.000.000 de ciclos, geramos interrupções periódicas exatas a cada 1 segundo. Para atender ao desafio de piscar duas vezes cada cor antes de avançar, implementamos uma máquina de estados com 4 etapas dentro do fluxo assíncrono. Além disso, para garantir a ordem exata exigida pelo enunciado (Vermelho, Verde, Azul, Amarelo, Ciano, Roxo, Branco), os valores binários correspondentes aos pinos PA0, PA1 e PA2 foram mapeados em um vetor indexado, desviando da contagem binária pura para estabelecer a sequência correta de mistura de cores no LED RGB.

### 5. Modulação por Largura de Pulso (PWM) e Temporização Assíncrona via Interrupção
Nesta prática, implementamos o controle dinâmico de um LED RGB para alternar suavemente entre sete combinações de cores (Vermelho, Verde, Azul, Amarelo, Ciano, Roxo e Branco) utilizando uma arquitetura baseada em dois timers independentes por hardware, eliminando completamente o uso de funções de atraso (*delays* bloqueantes). O Timer 3 (TIM3) foi configurado com resolução de 12 bits (ARR = 4095) e divisão de clock nula (PSC = 0) para gerar sinais PWM de alta frequência nos pinos PA6, PA7 e PB0, modulando o ciclo de trabalho (*duty cycle*) de cada canal de cor sem oscilação visual. Simultaneamente, o Timer 2 (TIM2) foi configurado para atuar de forma assíncrona como base de tempo do sistema, gerando interrupções periódicas de estouro (*Update Interrupt*) a cada 5 ms enviadas ao NVIC. A lógica de esmaecimento (*fade-in* e *fade-out*) e a máquina de estados que rotaciona os índices de cores foram encapsuladas inteiramente dentro do manipulador de interrupção (`TIM2_IRQHandler`), atualizando os registradores de captura e comparação (`CCR1`, `CCR2` e `CCR3`) em segundo plano e mantendo o laço principal (`while(1)`) com consumo mínimo de CPU.

### 6. ADC Multiplexado com DMA e Controle de Potência via PWM
Nesta prática, avançamos para o processamento de sinais analógicos e controle de potência utilizando quatro periféricos de hardware integrados. O objetivo foi controlar de forma independente a intensidade do brilho das três cores de um LED RGB utilizando três potenciômetros. Configuramos o conversor A/D (ADC1) no modo SCAN (varredura) para ler sequencialmente os canais analógicos PA0, PA1 e PA2 de forma contínua. Para evitar o gargalo da CPU e a sobreposição de dados no registrador de saída do ADC, configuramos o canal 1 do DMA1 em modo circular para transferir automaticamente os dados de 12 bits diretamente para um vetor na memória RAM através do barramento de alta velocidade (AHB). Por fim, configuramos três canais do Timer 3 (TIM3) operando em modo PWM 1 nos pinos PA6, PA7 e PB0, sincronizando o teto da contagem (ARR) com a resolução do ADC (0 a 4095) para modular o ciclo de trabalho e misturar as cores em tempo real sem ônus para o processador.

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