/* 
 * File:   led.h
 * Author: Julien LM
 *
 * Created on July 30, 2017, 10:16 PM
 */
#ifndef LED_H
#define	LED_H
#endif	/* LED_H */

#include "header.h"

void led_blinking_managing(short led_array[]) {
    led_array[0] ? LED0 = !LED0 : LED0 = 0;
    led_array[1] ? LED1 = !LED1 : LED1 = 0;
    led_array[2] ? LED2 = !LED2 : LED2 = 0;
    led_array[3] ? LED3 = !LED3 : LED3 = 0;
    led_array[4] ? LED4 = !LED4 : LED4 = 0;
}

