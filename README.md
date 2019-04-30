# Plot de velocidade de Motor DC em tempo real
## Proposta
Este projeto tem como objetivo plotar, em tempo real, a velocidade de um motor DC através da leitura de um encoder. Os sinais do encoder
serão enviados para duas portas GPIO da Discovery configuradas em modo Alternate Function que serão utilizadas para configurar um TIMER em
modo de leitura de encoder através de biblioteca da própria SPL (Standard Peripherals Library). Serão feitas medições periódicas no valor
do contador do TIMER a fim de, através das devidas conversões matemáticas, obter a velocidade do motor em tempo real.

Além disso, deve haver uma comunicação USB entre a Discovery e um PC de forma que os resultados de medição de velocidade sejam enviados 
continuamente para o PC, onde podem ser plotados através do LabView.

## Periféricos
No projeto serão utilizados:
#### 1 STM32F407 Discovery
#### 1 Motor DC 7.2V
#### 1 Encoder em quadratura de 400 divisões
#### 1 PC - LabView -
#### 1 Roda de Metal

![Diagrama de Blocos](DiagBlocosuC.PNG)
Figura 1: Diagrama de Blocos

## Pinagem
#### Motor0_ENCA -> PB4 -> TIM3_CH1: Encoder Mode
#### Motor0_ENCB -> PB5 -> TIM3_CH2: Encoder Mode
#### 1ms Interrupter -> TIM6: Interrupt Enable
#### USB Serial -> PA11 e PB12: Special Mode

## Fluxograma
O código segue em um Loop Infinito até que seja chamada a interrupção do Timer 6, que acontece a cada 1ms, chamando a função controle que atualiza os vetores encoderCount, calcula o valor atual da velocidade do motor e salva no vetor speed, que também é atualizado no início da interrupção. O valor atual da velocidade é utilizado como parâmetro para uma função que executa comunicação serial via USB de forma que, através de um programa no LabView, pode-se ler continuamente as velocidades medidas e plotá-las em um gráfico.

![Fluxograma](Fluxograma.PNG)
Figura 2: Fluxograma

## Interfaces para usuário
O código está configurado para, ao receber o comando \[A, equivalente a pressionar a tecla de seta para cima no prompt do TeraTerm, exibir a velocidade atual calculada pelo firmware. 

O mesmo comando é utilizado para a interface do LabView, na qual plota-se um gráfico em tempo real da velocidade da roda conectada ao motor0 do robô utilizado na equipe SSL da RoboIME.

## Referências
[Firmware SSL 2016](https://github.com/roboime/roboime-firmware)

[User Manual STM32F407VG](http://www.st.com/content/ccc/resource/technical/document/user_manual/70/fe/4a/3f/e7/e1/4f/7d/DM00039084.pdf/files/DM00039084.pdf/jcr:content/translations/en.DM00039084.pdf)

Aulas de Microcontroladores
# RoboIME-PID
# RoboIME-PID
