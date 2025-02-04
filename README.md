# Tarefa - Temporizador de Semáforo com Botão - Raspberry Pi Pico W

# Documentação do Código

## **Descrição Geral**

O código controla três LEDs, sendo capaz de:
- Captar o acionamento do botão utilizado e tratar o seu bouncing via software.
- Alternar entre os LEDs acesos, simulando o comportamento de um semáforo.
- Configurar e utilizar o temporizadores integrantes do RP2040.
- Alternar entre estados com a função *callback* implementada no sistema.

## **Bibliotecas Utilizadas**

### **Padrão do C**
- `<stdio.h>`: Manipulação de entrada/saída.

### **Pico SDK**
- `pico/stdlib.h`: Configuração padrão para Raspberry Pi Pico. Pôde apresentar toda a estrutura necessária para que esse código funcionasse corretamente, sem a necessidade de mais bibliotecas de *hardware*

## **Constantes**
- `GREEN_PINO`: Define o pino de saída utilizado pelo LED verde do RGB.
- `BLUE_PINO`: Define o pino de saída utilizado pelo LED azul do RGB.
- `RED_PINO`: Define o pino de saída utilizado pelo LED vermelho do RGB.
- `BTN_A`: Define o pino de entrada utilizado pelo Push Button.
- `DEBOUNCE_LINE`: Define em microsegundos o tempo a ser utilizado no debounce do botão.

## **Funções**

## **1. Callback**
### `bool turn_off_callback(struct repeating_timer *t)`
- **Descrição**: É um callback usado pelo temporizador repetitivo do Raspberry Pi Pico W. Ela é chamada automaticamente em intervalos definidos.
- **Parâmetros**:
  - `t`: É um ponteiro para `struct repeating_timer`, que contém as informações necessárias sobre o temporizador.

### **2. Função Principal (`main`)**
- **Descrição**:
  - Configura e inicializa os periféricos.
  - Configura a interrupção para detectar o acionamento do botão.
  - Entra em um loop infinito que:
    1. Mantém o processador em idle enquanto o timer funciona.

## **Fluxo do programa**

- A apresentação fica estática até que o botão de acionamento seja pressionado
- Quando o botão é pressionado, todos os LEDs acendem.
- O LED vermelho apaga no intervalo de tempo definido no temporizador.
- O LED azul (no lugar do amarelo) apaga em seguida, também no intervalo de tempo definido no temporizador.
- O LED verde apaga em seguida, também no intervalo de tempo definido no temporizador.
- O ciclo se encerra e é reiniciado somente caso o botão seja pressionado novamente.<br>
**OBS:** Caso o botão seja pressionado enquanto os estados são transicionados na sequência de execução, não haverá efeito algum. O botão só se torna válido novamente após todos os estados transicionados.