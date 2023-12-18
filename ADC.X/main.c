/*
 * File:   main.c
 * Author: Khanh
 *
 * Created on December 18, 2023, 4:27 PM
 * Chuong trinh hien thi gia tri ADC, qua 10 led don
 */


#define _XTAL_FREQ 4000000
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

void ADC_Init(){
  ADCON0 = 0b01000001; //ADC ON and Fosc/16 is selected
  ADCON1 = 0b11000000;
}

int ADC_Read(char channel){
  ADCON0 &= 0x11000101; 
  ADCON0 |= channel<<3;
  __delay_ms(2);
  GO_nDONE = 1; 
  while(GO_nDONE);
  return ((ADRESH<<8)+ADRESL); 
}

void main(void) {
    TRISA0 = 1;
    TRISD = 0x00;
    TRISC = 0x00;
    ADC_Init();
    unsigned int ADC;
    float dienap;
    while(1){
        ADC = ADC_Read(0);              // Doc gia tri ADC kenh 0
        PORTC = ADC % 256;              // Byte thap
        PORTD = ADC / 256;              // Byte cao
    }
    return;
}