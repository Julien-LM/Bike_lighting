/*
 * File:   main.c
 * Author: julien LM
 *
 * Created on July 30, 2017, 2:34 PM
 */


#include <xc.h>
#include "header.h"

void main(void) {
    // RA3 is a read only pin
    //TRISA = 0b00001100;
    TRISA = 0x08;
    ANSELA = 0x00;
    
    while(1) {
        
        RA0 = RA3;
        
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
