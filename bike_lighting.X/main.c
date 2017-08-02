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
void full(void);
void blink(void);
void chase(void);

short led_state_array[NB_LEDS] = {0, 0, 0, 0, 0};

unsigned char seconds_counteur = 0;
unsigned char blink_counter = 0;
unsigned char chase_counter = 0;
unsigned char chase_position = 0;
unsigned char mode = 2;

void main(void) {
    init();
    while(1) {
        switch(mode) {
            case FULL:
                full();
                break;     
            case 3:
                led_state_array[0] = 0;
                led_state_array[1] = 0;
                led_state_array[2] = 0;
                led_state_array[3] = 1;
                led_state_array[4] = 0;                
                break;            
            case 4:
                led_state_array[0] = 0;
                led_state_array[1] = 0;
                led_state_array[2] = 0;
                led_state_array[3] = 0;
                led_state_array[4] = 1;
                break;
        }
    }
}

void interrupt led_blinking(void) {
    // Interrupt-On-Change interrupt flag
    if(IOCAF3) {
        IOCAF = 0;
        if(RA3) {
            mode++;
            if(mode == 5) {
                mode = 0;
            }
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
        if(mode == BLINK) {
            blink_counter++;
            if(blink_counter == 50) {
                blink_counter = 0;
                blink();
            }
        } else if (mode == CHASE) {
            chase_counter++;
            if(chase_counter == 5) {
                chase_counter = 0;
                chase_position++;
                if(chase_position == NB_LEDS){
                    chase_position = 0;
                }
                chase();
            }
        }
    }
}

void seconds_interrupt(void) {
    NOP();
}

void full(void) {
    led_state_array[0] = 1;
    led_state_array[1] = 1;
    led_state_array[2] = 1;
    led_state_array[3] = 1;
    led_state_array[4] = 1;
}

void blink(void) {
    unsigned char i;
    for(i=0; i<NB_LEDS; i++) {
        led_state_array[i] = !led_state_array[i];
    }
}

void chase(void) {
    unsigned char i;
    for(i=0; i<NB_LEDS; i++) {
        if(chase_position+CHASE_SIZE > i && chase_position <= i) {
            led_state_array[i] = 1;
        } else if(chase_position+CHASE_SIZE-NB_LEDS > i) {
            led_state_array[i] = 1;
        } else {
            led_state_array[i] = 0;
        }
    }
}
