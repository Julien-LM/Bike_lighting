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

#include <stdlib.h>


void seconds_interrupt(void);
void led_blinking_managing(short led_array[]);
void full_on(void);
void full_off(void);
void blink(void);
void chase(void);
void space(void);
void fast(unsigned char periode);

short led_state_array[NB_LEDS] = {0, 0, 0, 0, 0};

unsigned char seconds_counteur = 0;
unsigned char main_counter = 0;
unsigned char secondary_counter = 0;
unsigned char chase_direction = 0;

unsigned char mode = CHASE_MISA;

void main(void) {
    init();
    
    while(1) {
        if(mode == FULL) {
            full_on();
        }
    }
}

void interrupt led_blinking(void) {
    // Interrupt-On-Change interrupt flag
    if(IOCAF3) {
        IOCAF = 0;
        if(RA3) {
            mode++;
            if(mode == 6) {
                mode = 0;
            }
            main_counter = 0;
            secondary_counter = 0;
        }
    }
    
    // Timer2 interrupt flag
    // 100 Hz interrupt
    if(TMR2IF == 1) {
        TMR2IF = 0;
        
        led_blinking_managing(led_state_array);
        
        seconds_counteur++;
        if(seconds_counteur == 100) {
            seconds_counteur = 0;
            seconds_interrupt();
        }
        if(mode == BLINK) {
            // BLINK mode
            main_counter++;
            if(main_counter == 50) {
                main_counter = 0;
                blink();
            }
        } else if (mode == CHASE) {
            // CHASE mode
            main_counter++;
            if(main_counter == 5) {
                main_counter = 0;
                if(CHASE_MODE == "to_top") {
                    secondary_counter++;
                    if(secondary_counter == NB_LEDS){
                        secondary_counter = 0;
                    }
                } else if(CHASE_MODE == "to_bot") {
                    if(secondary_counter == 0){
                        secondary_counter = NB_LEDS;
                    }
                    secondary_counter--;
                }
                chase();
            }
        } else if (mode == SPACE) {
            // SPACE mode
            main_counter++;
            if(main_counter == 2) {
                main_counter = 0;
                space();
            }
        } else if (mode == FAST) {
            // FAST mode
            main_counter++;
            if(main_counter == 8) {
                main_counter = 0;
                secondary_counter++;
                fast(secondary_counter);
                if(secondary_counter == 9) {
                    secondary_counter = 0;
                }
            }
        } else if (mode == CHASE_MISA) {
            // CHASE mode both size
            main_counter++;
            if(main_counter == 5) {
                main_counter = 0;
                if(chase_direction) {
                    secondary_counter++;
                    if(secondary_counter == NB_LEDS){
                        chase_direction = 0;
                        secondary_counter = NB_LEDS-2;
                    }
                } else {
                    if(secondary_counter == 0){
                        chase_direction = 1;
                        secondary_counter = 2;
                    }
                    secondary_counter--;
                }
                chase();
            }
        }
    }
}

void seconds_interrupt(void) {
    NOP();
}

void full_on(void) {
    led_state_array[0] = 1;
    led_state_array[1] = 1;
    led_state_array[2] = 1;
    led_state_array[3] = 1;
    led_state_array[4] = 1;
}

void full_off(void) {
    led_state_array[0] = 0;
    led_state_array[1] = 0;
    led_state_array[2] = 0;
    led_state_array[3] = 0;
    led_state_array[4] = 0;
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
        if(secondary_counter+CHASE_SIZE > i && secondary_counter <= i) {
            led_state_array[i] = 1;
        } else if(secondary_counter+CHASE_SIZE-NB_LEDS > i) {
            led_state_array[i] = 1;
        } else {
            led_state_array[i] = 0;
        }
    }
}

void space(void) {
    led_state_array[0] = rand()%2;
    led_state_array[1] = rand()%2;
    led_state_array[2] = rand()%2;
    led_state_array[3] = rand()%2;
    led_state_array[4] = rand()%2;   
}

void fast(unsigned char periode) {
    unsigned char i;
    if(periode < 6) {
        full_off();  
    } else {
        for(i=0; i<NB_LEDS; i++) {
            led_state_array[i] = !led_state_array[i];
        }    
    }

}
