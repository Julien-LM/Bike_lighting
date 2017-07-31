/* 
 * File:   init.h
 * Author: ju
 *
 * Created on July 31, 2017, 6:53 PM
 */

#ifndef INIT_H
#define	INIT_H
#endif	/* INIT_H */

#include <xc.h>
#include "header.h"

void init(void){
        
    // I/O configuration
    TRISA = 0x08;    // RA3 is a read only pin
    ANSELA = 0x00;
    
    // General Interruption configuration
    GIE = 1;        // Enables all active interrupts
    PEIE = 1;       // Enables all active peripheral interrupts 
    
    // timer2 Interruption configuration
    TMR2IE = 1;     // Enables the Timer2 to PR2 match interrupt
    
    // XTAL = 500KHz
    //PR2 = 0xFA;
    //T2CON = 0x24;
    
    // Internal Oscillator Frequency Select bits
    OSCCON = 0x02; // Set freq to 31kHz

    // XTAL = 31KHz
    PR2 = 0x0B;
    T2CON = 0x34;
    
}
