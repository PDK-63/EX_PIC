/*
 * File:   main.c
 * Author: Khanh
 *
 * Created on December 18, 2023, 3:36 PM
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

#define C1 PORTCbits.RC0
#define C2 PORTCbits.RC1
#define C3 PORTCbits.RC2
#define C4 PORTCbits.RC3
#define H1 PORTCbits.RC4
#define H2 PORTCbits.RC5
#define H3 PORTCbits.RC6
#define H4 PORTCbits.RC7

void LCD_Cmd(char data);
void LCD_Data(char data);
void LCD_Init();
void LCD_String(char *str, char num);

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

void Keypad(){
    C1 = 1, C2 = C3 = C4 = 0;
    if(H1 == 1){
        LCD_Data('7');
        while(H1 == 1);
    }
    if(H2 == 1){
        LCD_Data('8');
        while(H2 == 1);
    }
    if(H3 == 1){
        LCD_Data('9');
        while(H3 == 1);
    }
    if(H4 == 1){
        LCD_Data('A');
        while(H4 == 1);
    }
    C2 =1, C1 = C3 = C4 = 0;
    if(H1 == 1){
        LCD_Data('4');
        while(H1 == 1);
    }
    if(H2 == 1){
        LCD_Data('5');
        while(H2 == 1);
    }
    if(H3 == 1){
        LCD_Data('6');
        while(H3 == 1);
    }
    if(H4 == 1){
        LCD_Data('B');
        while(H4 == 1);
    }
    
    C3 = 1, C1 = C2 = C4 = 0;
    if(H1 == 1){
        LCD_Data('1');
        while(H1 == 1);
    }
    if(H2 == 1){
        LCD_Data('2');
        while(H2 == 1);
    }
    if(H3 == 1){
        LCD_Data('3');
        while(H3 == 1);
    }
    if(H4 == 1){
        LCD_Data('C');
        while(H4 == 1);
    }
    
    C4 = 1, C1 = C2 = C3 = 0;
    if(H1 == 1){
        LCD_Data('*');
        while(H1 == 1);
    }
    if(H2 == 1){
        LCD_Data('0');
        while(H2 == 1);
    }
    if(H3 == 1){
        LCD_Data('=');
        while(H3 == 1);
    }
    if(H4 == 1){
        LCD_Data('D');
        while(H4 == 1);
    }
}
void main(void) {
    TRISB = 0x00;
    TRISC = 0xF0;
    LCD_Init();
    LCD_Cmd(0x80);
    LCD_String("KEYPAD: ", 7);
    LCD_Cmd(0xC0);
    
    while(1){
        Keypad();
    }
    return;
}

