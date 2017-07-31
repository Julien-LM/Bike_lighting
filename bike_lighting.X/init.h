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
    
    // Internal Oscillator Frequency Select bits
    OSCCONbits.IRCF = 0;    // Set freq to 31kHz
    OSCCONbits.SCS = 2;     // Internal oscillator block

    // XTAL = 31KHz, efficient 7,75 kHz
    PR2 = 0x0B;
    T2CONbits.TMR2ON = 1;   //Timer2 is on
    T2CONbits.T2CKPS = 0;   // Prescaler is 1
    T2CONbits.T2OUTPS = 6;  // 1:7 Postscaler
    
    // Interrupt-on-change
    IOCIE = 1;      // Enables the interrupt-on-change
    IOCAP = 0x08;   // Enable IOCAN3
    IOCAN = 0x00;   // DIsable every pin
    
}
