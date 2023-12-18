/*
 * File:   main.c
 * Author: Khanh
 *
 * Created on December 18, 2023, 4:10 PM
 */


#include <stdio.h>
#include <stdlib.h>
#define _XTAL_FREQ 4000000
#include <xc.h>
// CONFIG
#pragma config FOSC = XT       
#pragma config WDTE = OFF     
#pragma config PWRTE = OFF   
#pragma config BOREN = OFF     
#pragma config LVP = OFF       
#pragma config CPD = OFF        
#pragma config WRT = OFF      
#pragma config CP = OFF        
const unsigned char Ma_led[8] = {0xff,0x01,0x00,0xf6,0xf6,0x00,0x01,0xff}; 
// lay ma tu duoi len 8 - 4 - 2 - 1
// sang la 0 tat la 1
void main()
{
 unsigned char i;
 unsigned char cnt;
 unsigned char j;
    TRISB = 0X00;
    TRISD = 0X00;
 while(1)
 {
  for(i=0;i<7;i++)
  {
  PORTB = Ma_led[i];
  PORTD = 0x01<<i;
  __delay_ms(1);
  PORTD = 0x00;
  }           
    }
}