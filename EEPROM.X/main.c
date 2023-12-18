/*
 * File:   main.c
 * Author: Khanh
 *
 * Created on December 19, 2023, 1:01 AM
 */

#define _XTAL_FREQ 4000000 
#include <xc.h>
#include <stdint.h>

// CAU HINH CHAN
#define Doc RB0             // DOc gia tri trong bo nho EEPROM
#define W_1 RB1             // Write 0x01
#define W_2 RB2             // Write 0x02
#define W_3 RB3             // Write 0x03

void EEPROM_W(uint8_t Dc, uint8_t Dulieu);
int EEPROM_R(uint8_t Dc);

void EEPROM_W(uint8_t Dc, uint8_t Dulieu){
    while(EECON1bits.WR);   
    EEADR = Dc;                     
    EEDATA = Dulieu;
    EECON1bits.EEPGD = 0;
    EECON1bits.WREN = 1;
    INTCONbits.GIE = 0;
    EECON2 = 0x55;
    EECON2 = 0xAA;
    EECON1bits.WR = 1;
    INTCONbits.GIE = 0;
    EECON1bits.WREN = 0;
    EECON1bits.WR = 0;
}

int EEPROM_R(uint8_t Dc){
    uint8_t Dulieu;
    EEADR = Dc;
    EECON1bits.EEPGD = 0;
    EECON1bits.RD = 1;
    Dulieu = EEDATA;
    return Dulieu;
}
void main(void) {
    TRISB = 0x0F;           // nut nhan
    TRISD = 0x00;           // LED
    PORTD = 0x00;
    uint8_t dc;
    
    while(1){
        if(W_1){
            EEPROM_W(dc++, 1);
            __delay_ms(500);
        }
        if(W_2){
            EEPROM_W(dc++, 2);
            __delay_ms(500);
        }
        if(W_3){
            EEPROM_W(dc++, 3);
            __delay_ms(500);
        }
        if(dc == 3){
            dc = 0;
        }
        if(Doc == 0){
            uint8_t i;
            for(uint8_t i = 0; i < 3; i++){
                PORTD = EEPROM_R(i);
                __delay_ms(1000);
            }
        }
    }
    return;
}
