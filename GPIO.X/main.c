/*
 * File:   main.c
 * Author: Khanh
 *
 * Created on December 17, 2023, 10:06 PM
 * Chuong trinh dieu khien LED nhap nhay tren PORTB
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
    TRISB = 0x00;               // Khai bao PORTB la Input
    PORTB = 0x00;               // Toan bo PORTB tat
    while(1){
        PORTB = ~PORTB;         // Phep dao trang thai, 1->0, 0 -> 1
        __delay_ms(500);        
    }
    return;
}
