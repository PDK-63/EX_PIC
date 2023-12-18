/*
 * File:   main.c
 * Author: Khanh
 *
 * Created on December 18, 2023, 3:14 AM
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
    TRISB0 = 1;               // Khai bao PORTB la Input
    TRISB1 = 0;
    while(1){
        if(RB0 == 0){
            RB1 = 1;
        }
        else{
            RB1 = 0;
        }
    }
    return;
}
