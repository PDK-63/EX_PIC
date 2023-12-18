/*
 * File:   main.c
 * Author: Khanh
 *
 * Created on December 18, 2023, 10:59 AM
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

#define a RB0
#define b RB1
#define c RB2
#define d RB3
#define e RB4
#define f RB5
#define g RB6
#define dp RB7

// Khai bao ma LED
char ma_led[] = {0xC0, 0xF9, 0xA4, 0xB0,0x99,0x92,
                0x82,0xF8,0x80,0x98};

void hienthi(char dulieu){
    a = dulieu & 0x01;
    b = (dulieu >> 1) & 0x01;
    c = (dulieu >> 2) & 0x01;
    d = (dulieu >> 3) & 0x01;
    e = (dulieu >> 4) & 0x01;
    f = (dulieu >> 5) & 0x01;
    g = (dulieu >> 6) & 0x01;
    dp = (dulieu >> 7) & 0x01;
}

void main(void) {
    TRISB = 0;              // Cau hinh PORTB OUTPUT
    TRISC = 0;
    PORTB = 1;
    PORTC = 1;
    unsigned int i;
    while(1){
        for(i = 0; i < 1000; i++){
            RC0 = 1;
            hienthi(ma_led[i / 1000]);
            __delay_ms(10);
            RC0 = 0;

            RC1 = 1;
            hienthi(ma_led[(i % 1000) / 100]);
            __delay_ms(10);
            RC1 = 0;

            RC2 = 1;
            hienthi(ma_led[(i % 1000 %100) / 10]);
            __delay_ms(10);
            RC2 = 0;

            RC3 = 1;
            hienthi(ma_led[i % 1000 % 100 % 10]);
            __delay_ms(10);
            RC3 = 0;
        }
    }
    return;
}
