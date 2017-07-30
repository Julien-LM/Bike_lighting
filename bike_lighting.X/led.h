/* 
 * File:   led.h
 * Author: Julien LM
 *
 * Created on July 30, 2017, 10:16 PM
 */
#include "header.h"

void led_blinking_managing(short led_array[]) {
    /*int i;
    
    for(i=0; i<NB_LEDS; i++) {
        if(led_array[i]) {
            
        } else {
            
        }
    }*/
    
    
    

    if(led_array[0]) {
        LED0 = !LED0;
    } else {
        LED0 = 0;
    }
    if(led_array[1]) {
        LED1 = !LED1;
    } else {
        LED1 = 0;
    }    
    if(led_array[2]) {
        LED2 = !LED2;
    } else {
        LED2 = 0;
    }    
    if(led_array[3]) {
        LED3 = !LED3;
    } else {
        LED3 = 0;
    }    
    if(led_array[4]) {
        LED4 = !LED4;
    } else {
        LED4 = 0;
    }
}

