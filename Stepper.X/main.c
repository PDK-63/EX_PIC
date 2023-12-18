/*
 * File:   main.c
 * Author: Khanh
 *
 * Created on December 19, 2023, 3:53 AM
 */

#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 4000000
void main(void)
{
  // Create Bit-Shifting Variable
  unsigned char i=0;
  
  TRISC = 0x00;

  PORTC = 0x00;
 
  TRISD0 = 1;
  TRISD1 = 1;
 
  while(1)
  {
  
    while(RD0 == 0)
    {
      PORTC = (1<<i);
      i++;
      __delay_ms(100);
      if (i==4)
          i=0;
    }

    while(RD1 == 0)
    {
      PORTC = (8>>i);
      i++;
      __delay_ms(100);
      if (i==4)
          i=0;
    }
  }
  return;
}