/*
 * File:   main.c
 * Author: Khanh
 *
 * Created on December 19, 2023, 12:24 AM
 * Chuong trinh hien thi gia tri cam bien LM35 len LCD
 */


#define _XTAL_FREQ 4000000
#include <xc.h>
#include <stdio.h>
// CONFIG
#pragma config FOSC = HS        // Che do dao dong HS(High speed))
#pragma config WDTE = ON       // Khong dung Watchdog Timer
#pragma config PWRTE = ON       // Su dung Power-up timer
#pragma config BOREN = OFF      // Khong su dung chuc nang Bown-out reset
#pragma config LVP = OFF        // Khong su dung che do cap nguon chi tu tu mach nap
#pragma config CPD = OFF       
#pragma config WRT = OFF       
#pragma config CP = OFF   

#define RS PORTBbits.RB0
#define RW PORTBbits.RB1
#define EN PORTBbits.RB2

void LCD_Cmd(char data);
void LCD_Data(char data);

void LCD_Cmd(char data){
    PORTB = (data & 0xF0);
    EN = 1;
    RW = 0;
    RS = 0;
    __delay_ms(5);
    EN = 0;
    PORTB = ((data << 4) & 0xF0);
    EN = 1;
    RW = 0;
    RS = 0;
     __delay_ms(5);
    EN = 0;
}

void LCD_Data(char data){
    PORTB = (data & 0xF0);
    EN = 1;
    RW = 0;
    RS = 1;
    __delay_ms(5);
    EN = 0;
    PORTB = ((data << 4) & 0xF0);
    EN = 1;
    RW = 0;
    RS = 1;
    __delay_ms(5);
    EN = 0;
}

void LCD_Init(){
    LCD_Cmd(0x02);
    LCD_Cmd(0x28);
    LCD_Cmd(0x0C);
    LCD_Cmd(0x06);
    LCD_Cmd(0x01);
}

void LCD_String(char *str){
    unsigned char i;
    for(i=0;str[i]!='\0';i++){
        LCD_Data(str[i]);
    }
}

void ADC_Init(){
    ADCON0 = 0x41;              // Bat ADC, chon ADC kenh 0, ADC Clock = Fosc/ 8
    ADCON1 = 0x80;              // Cau hinh 8 chan che do Analog 
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

void main(){
    TRISB = 0x00;
    LCD_Init();         // Goi lai ham LC
    ADC_Init();         // Goi lai ham ADC
    float Nhietdo, Vol;
    int ADC = 0;
    char* Temp[16];
    while(1){
        ADC = ADC_Read(0);          // Doc gia tri ADC kenh 0
        Vol = ADC * 0.00488;
        Nhietdo = Vol / 0.01;
        LCD_Cmd(0x80);
        LCD_String("Nhiet do");
        sprintf(Temp, " %.2f", Nhietdo);
        LCD_Cmd(0xC0);
        LCD_String(Temp);
    }
    return;
}