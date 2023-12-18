/*
 * File:   main.c
 * Author: Khanh
 *
 * Created on December 19, 2023, 12:10 AM
 */


#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 4000000
#define DAC_OUT PORTB
void ADC_Init();
uint16_t ADC_Read(uint8_t);


void ADC_Init()
{
  ADCON0 = 0x41;            // Bat ADC, chon ADC kenh 0,  Clock = Fosc/8
  ADCON1 = 0x80;            // cau hinh 8 kenh Analog,
  // ADC Clock = Fosc/8
}
uint16_t ADC_Read(uint8_t ANC)
{
  if(ANC<0 || ANC>7)        // Kiem tra kenh
  { 
      return 0;
  }
  ADCON0 &= 0x11000101;              // Clear The Channel Selection Bits
  ADCON0 |= ANC<<3;                  // Select The Required Channel (ANC)
  
  __delay_us(30); 
  GO_DONE = 1;                      // Bat dau chuyen chuyen ADC -> DAC
  while(ADCON0bits.GO_DONE);        // Cho qua trinh chuyen doi
 
  return ((ADRESH << 8) + ADRESL); // Tra ve gia tri 10 bit
}

void main(void) {
 
  ADC_Init();
  TRISB = 0x00;                         
  DAC_OUT = 0x00;
  uint16_t AN0RES;
  while(1)
  {
    AN0RES = ADC_Read(0)>>2;    // DAC_OUT = (10bit ADC) / 4 = [ 0->255 ]
    DAC_OUT = AN0RES;           // Truyen du lieu den DAC
    __delay_ms(1);             
  }
  return;
}
