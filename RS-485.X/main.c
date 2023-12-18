/*
 * File:   main.c
 * Author: Khanh
 *
 * Created on December 19, 2023, 4:12 AM
 */


  
#include <xc.h>
#define _XTAL_FREQ 4000000
#define Baud_rate 9600

#pragma config FOSC = HS     
#pragma config WDTE = OFF       
#pragma config PWRTE = OFF       
#pragma config BOREN = ON       
#pragma config LVP = OFF        
#pragma config CPD = OFF      
#pragma config WRT = OFF       
#pragma config CP = OFF       
void Initialize_UART(void)
{
    TRISC6 = 0; 
    TRISC7 = 1; 
    SPBRG = ((_XTAL_FREQ/16)/Baud_rate) - 1;
    BRGH  = 1; 
    SYNC  = 0;    
    SPEN  = 1;    
    TXEN  = 1;    
    CREN  = 1;   
    TX9   = 0;   
    RX9   = 0;   
}

void UART_send_char(char bt)  
{
    while(!TXIF); 
    TXREG = bt; 
}

char UART_get_char()   
{
    if(OERR) 
    {
        CREN = 0; 
        CREN = 1; 
    }
    while(!RCIF); 
    return RCREG;
}

void UART_send_string(char* st_pt)
{
    while(*st_pt) 

        UART_send_char(*st_pt++); 
}

void main(void)
{
    int get_value;
    TRISB = 0x00; 
    Initialize_UART();                    
    UART_send_string("LewLew");    
    while(1) 
    {
      get_value = UART_get_char(); 
        if (get_value == '1') 
        {
            RB3=1; 
            UART_send_string("RED LED -> ON"); 
            UART_send_char(10);
        }
        if (get_value == '0') 
        {
           RB3=0; 
           UART_send_string("RED -> OFF");     
           UART_send_char(10);
        }
    }
}