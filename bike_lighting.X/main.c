/*
 * File:   main.c
 * Author: julien LM
 *
 * Created on July 30, 2017, 2:34 PM
 */


#include <xc.h>
#include "header.h"
#include "led.h"
#include "init.h"


void seconds_interrupt(void);
void led_blinking_managing(short led_array[]);

short seconds_counteur = 0;
short led_state_array[NB_LEDS] = {0, 1, 0, 1, 0};

void main(void) {
    init();
    while(1);
}

void interrupt led_blinking(void) {
    if(TMR2IF == 1) {
        TMR2IF = 0;
        
        led_blinking_managing(led_state_array);
        
        seconds_counteur++;
        if(seconds_counteur == 100) {
            seconds_counteur = 0;
            seconds_interrupt();
        }
    }
}

void seconds_interrupt(void) {
    int i;
    for(i=0; i<NB_LEDS; i++) {
        led_state_array[i] = !led_state_array[i];
    }
}

