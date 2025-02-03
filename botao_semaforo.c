#include <stdio.h>
#include "pico/stdlib.h"
// Definicao dos pinos dos LEDs, botao e tempo de controle de debounce
#define GREEN_PINO 11
#define BLUE_PINO 12
#define RED_PINO 13
#define BTN_A 5
#define DEBOUNCE_LINE 300000

volatile bool led_ligado = false;  // Indica se os LEDs estao ligados
volatile int contador = 0;          // Contador de controle dos estado de numeros atual
volatile int btn_a_acionado = 0;    // Variavel de controle do 'botao a' pressioando

bool turn_off_callback(struct repeating_timer *t){

    static int estado = 0;

    if(estado == 0){
        gpio_put(RED_PINO, false);
    } else if(estado == 1){
        gpio_put(BLUE_PINO, false);
    } else if(estado == 2){
        gpio_put(GREEN_PINO, false);
        led_ligado = false;            // Libera o botao para uma nova ativacao
        estado = -1;                   // Reseta para a proxima ativacao
        return false;                  // Para o temporizador quando o ultimo LED apaga
    }

    estado++;
    return true;

}

void button_callback(uint gpio, uint32_t events){
    // Obtencao do tempo real em microsegundos numa variavel uint
    uint32_t marco = time_us_32();

    if(gpio == BTN_A && (marco -  btn_a_acionado) > DEBOUNCE_LINE){
        if(!led_ligado){

            btn_a_acionado = marco;

            led_ligado = true;
            // Acende todos os LEDs
            gpio_put(RED_PINO, true);
            gpio_put(BLUE_PINO, true);
            gpio_put(GREEN_PINO, true);
            // Iniciacao do temporizador que apagara os LEDs nos intervalos
            static struct repeating_timer off_timer;
            add_repeating_timer_ms(-3000, turn_off_callback, NULL, &off_timer);

            printf("O botao foi acionado.");

        }
    }

}

int main()
{
    stdio_init_all();

    gpio_init(GREEN_PINO);
    gpio_init(BLUE_PINO);
    gpio_init(RED_PINO);

    gpio_set_dir(GREEN_PINO, GPIO_OUT);
    gpio_set_dir(BLUE_PINO, GPIO_OUT);
    gpio_set_dir(RED_PINO, GPIO_OUT);

    gpio_init(BTN_A);
    gpio_set_dir(BTN_A, GPIO_IN);
    gpio_pull_up(BTN_A);

    // Configura a interrupcao para detectar o acionamento do botao
    gpio_set_irq_enabled_with_callback(BTN_A, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    while (true) {
        tight_loop_contents();  // Mantem o processador em idle enquanto o timer funciona    
    }

}
