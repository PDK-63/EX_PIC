/*
 * File:   main.c
 * Author: Khanh
 *
 * Created on December 18, 2023, 10:32 AM
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

// Khai bao ma LED
char ma_led[] = {0xC0, 0xF9, 0xA4, 0xB0,0x99,0x92,
                0x82,0xF8,0x80,0x98};

void main(void) {
    TRISD = 0;
    unsigned int i;
    while(1){
        for(i = 0; i < 10; i++){
            PORTD = ma_led[i];
            __delay_ms(100);
        }
    }
    return;
}
