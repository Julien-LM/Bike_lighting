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

short led_state_array[NB_LEDS] = {0, 0, 0, 0, 0};

short seconds_counteur = 0;
short mode = 0;

void main(void) {
    init();
    while(1) {
        switch(mode) {
            case 0:
                led_state_array[0] = 1;
                led_state_array[1] = 0;
                led_state_array[2] = 0;
                led_state_array[3] = 0;
                break;
            case 1:
                led_state_array[0] = 0;
                led_state_array[1] = 1;
                led_state_array[2] = 0;
                led_state_array[3] = 0;                
                break;            
            case 2:
                led_state_array[0] = 0;
                led_state_array[1] = 0;
                led_state_array[2] = 1;
                led_state_array[3] = 0;                
                break;
            case 3:
                led_state_array[0] = 0;
                led_state_array[1] = 0;
                led_state_array[2] = 0;
                led_state_array[3] = 1;                
                break;            
            case 4:
                led_state_array[4] = 1;
                break;
        }
    }
}

void interrupt led_blinking(void) {
    // Interrupt-On-Change interrupt flag
    if(IOCIF) {
        IOCAF = 0;
        mode++;
        if(mode == 5) {
            mode = 0;
        }
    }
    
    // Timer2 interrupt flag
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
    led_state_array[4] = !led_state_array[4];
    /*for(i=0; i<NB_LEDS; i++) {
        led_state_array[i] = !led_state_array[i];
    }*/
}

