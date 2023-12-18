/*
 * File:   main.c
 * Author: Khanh
 *
 * Created on December 19, 2023, 3:28 AM
 */


#include <xc.h>
#include <stdint.h>

#define _XTAL_FREQ 4000000
//--[ Pin Definitions ]--
#define Rev RB0   
#define LV0 RB1   // 0% Speed Button
#define LV1 RB2   // 50% Speed Button
#define LV2 RB3   // 75% Speed Button
#define LV3 RB4   // 100% Speed Button

void PWM1_Set_Duty(uint16_t);
 
void main(void)
{
 
  TRISB = 0x1F;
 
  TRISD0 = 0;
  TRISD1 = 0;

  RD0 = 0;
  RD1 = 1;
 
  CCP1M3 = 1;
  CCP1M2 = 1;
  TRISC2 = 0; 
 
  PR2 = 124;

  T2CKPS0 = 1;
  T2CKPS1 = 0;
 
  TMR2ON = 1;

  while(1)
  {
    if(Rev == 0) 
    {
      RD0 = ~RD0;
      RD1 = ~RD1;
      __delay_ms(500); 
    }
    if(LV0 == 0) // 0% DC
    {
      PWM1_Set_Duty(0);
      __delay_ms(100);
    }
    if(LV1 == 0) // 50% DC
    {
      PWM1_Set_Duty(250);
      __delay_ms(100); 
    }
    if(LV2 == 0) // 75% DC
    {
      PWM1_Set_Duty(375);
      __delay_ms(100); 
    }
    if (LV3 == 0) // 100% DC
    {
      PWM1_Set_Duty(500);
      __delay_ms(100); 
    }
    __delay_ms(10);  
  }
  return;
}
 
void PWM1_Set_Duty(uint16_t DC)
{
  
  if(DC<1024)
  {
    CCP1Y = DC & 1;
    CCP1X = DC & 2;
    CCPR1L = DC >> 2;
  }
}