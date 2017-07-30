/*
 * File:   main.c
 * Author: julien LM
 *
 * Created on July 30, 2017, 2:34 PM
 */


#include <xc.h>
#include "header.h"
#include "led.h"


void seconds_interrupt(void);
void led_blinking_managing(short led_array[]);

short seconds_counteur = 0;
short led_state_array[NB_LEDS] = {0, 1, 0, 1, 0};

void main(void) {
    
    // I/O configuration
    TRISA = 0x08;    // RA3 is a read only pin
    ANSELA = 0x00;
    
    // General Interruption configuration
    GIE = 1;        // Enables all active interrupts
    PEIE = 1;       // Enables all active peripheral interrupts 
    
    // timer2 Interruption configuration
    TMR2IE = 1;     // Enables the Timer2 to PR2 match interrupt
    PR2 = 0xFA;
    T2CON = 0x24;
    
    while(1) {
        
        //RA0 = RA3;
        
        /*RA0 = 1;
        RA1 = 1;
        RA2 = 1;
        RA5 = 1;
        RA4 = 1;
        __delay_ms(1000);
        RA0 = 0;
        RA1 = 0;
        RA2 = 0;
        RA5 = 0;
        RA4 = 0;
        __delay_ms(1000);*/
    }
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

