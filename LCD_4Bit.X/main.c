/*
 * File:   main.c
 * Author: Khanh
 *
 * Created on December 18, 2023, 3:15 PM
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

void LCD_String(char *str, char num){
    unsigned char i;
    for(i = 0; i < num; i++){
        LCD_Data(str[i]);
    }
}
void main(void) {
    TRISB = 0x00;
    LCD_Init();
    while(1){
        LCD_Cmd(0x80);
        LCD_String("Xin chao", 8);
        LCD_Cmd(0xC0);
        LCD_String("1234587", 7);
    }
    return;
}
