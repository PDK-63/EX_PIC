/*
 * File:   main.c
 * Author: Khanh
 *
 * Created on December 19, 2023, 1:47 AM
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
void LCD_Init();

void rtc_int();
void rtc_start();
void rtc_stop();
void rtc_ack();
void rtc_nak();
void rtc_res();
void rtc_send(unsigned char a);
void rtc_send_byte(unsigned char addr,unsigned char data);
unsigned char rtc_read();
unsigned char rtc_read_byte(unsigned char addr);
void waitmssp();
unsigned char convup(unsigned char bcd);
unsigned char convd(unsigned char bcd);

unsigned char sec,min,hour,day,date,month,year;

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

void LCD_String(unsigned char *s){
    while(*s){
        LCD_Data(*s++);
    }
}

void rtc_int()
{
    TRISC3=TRISC4=1;
    SSPCON=0x28;
    SSPADD= (((11059200/4)/100)-1);
}
void waitmssp()
{
    while(!SSPIF); // SSPIF is zero while TXion is progress    
    SSPIF=0;
}
void rtc_send(unsigned char a)
{
    SSPBUF=a;
    waitmssp();
    while(ACKSTAT);
}   
void rtc_send_byte(unsigned char addr,unsigned char data)
{
    rtc_start();
    rtc_send(0xD0);
    //rtc_send(addr>>8);
    rtc_send(addr);
    rtc_send(data);
    rtc_stop();
}
unsigned char rtc_read()
{
    RCEN=1;
    waitmssp();
    return SSPBUF;
}   
    
unsigned char rtc_read_byte(unsigned char addr)
{
    unsigned char rec;
L:  rtc_res();
    SSPBUF=0xD0;
    waitmssp();
    while(ACKSTAT){goto L;}
    //rtc_send(addr>>8);
    rtc_send(addr);
    rtc_res();
    rtc_send(0xD1);
    rec=rtc_read();
    rtc_nak();
    rtc_stop();
    return rec;
}
    
void rtc_start(void)
{
    SEN=1;
    waitmssp();
}
void rtc_stop()
{
    PEN=1;
    waitmssp();
}
void rtc_res()
{
    RSEN=1;
    waitmssp();
}
void rtc_ack()
{
    ACKDT=0;
    ACKEN=1;
    waitmssp();
}
void rtc_nak()
{
    ACKDT=1;
    ACKEN=1;
    waitmssp();
}
unsigned char convup(unsigned char bcd)
{ 
    return ((bcd>>4)+48);
}
unsigned char convd(unsigned char bcd)
{ 
    return ((bcd&0x0F)+48);
}

void main(void) {
   TRISB = 0x00;
   rtc_int();
  LCD_Init();
   char Temp[16];
  LCD_String("Xin chao");
  while(1){
      sec = rtc_read_byte(0x00);
      min = rtc_read_byte(0x01);
      hour = rtc_read_byte(0x02);
      day = rtc_read_byte(0x03);
      date = rtc_read_byte(0x04);
      month = rtc_read_byte(0x05);
      year = rtc_read_byte(0x06);
      
      LCD_Cmd(0x80);
      LCD_Data(convup(hour));
      LCD_Data(convd(hour));
      LCD_Data(':');
     
      
      LCD_Data(convup(min));
      LCD_Data(convd(min));
      LCD_Data(':');
      
      LCD_Data(convup(sec));
      LCD_Data(convd(sec));
      LCD_Data(':');
      
      LCD_Cmd(0xC0);
      LCD_Data(convup(date));
      LCD_Data(convd(date));
      LCD_Data(':');
      
      LCD_Data(convup(month));
      LCD_Data(convd(month));
      LCD_Data(':');
      
      LCD_Data(convup(year));
      LCD_Data(convd(year));
      LCD_Data(':');
  }
  return;
}
