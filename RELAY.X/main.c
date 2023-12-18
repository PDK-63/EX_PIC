/*
 * File:   main.c
 * Author: Khanh
 *
 * Created on December 18, 2023, 2:44 PM
 */


#define _XTAL_FREQ 20000000
#include <xc.h>
// CONFIG
#pragma config FOSC = HS        // Che do dao dong HS(High speed))
#pragma config WDTE = ON       // Khong dung Watchdog Timer
#pragma config PWRTE = ON       // Su dung Power-up timer
#pragma config BOREN = OFF      // Khong su dung chuc nang Bown-out reset
#pragma config LVP = OFF        // Khong su dung che do cap nguon chi tu tu mach nap
#pragma config CPD = OFF       
#pragma config WRT = OFF       
#pragma config CP = OFF  

void main(void) {
    TRISCbits.TRISC0 = 1;               // nut nhan
    TRISBbits.TRISB1 = 0;               // Relay
    PORTBbits.RB1 = 0;
    while(1){
        if(PORTCbits.RC0 == 0){
            PORTBbits.RB1 = 1;
        }
        else{
             PORTBbits.RB1 = 0;
        }
    }
    return;
}
