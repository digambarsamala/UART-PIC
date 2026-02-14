// PIC16F877A Master Code
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>


#define _XTAL_FREQ 6000000

void uart_setup();
unsigned char data, rx_data;

void main() {
    uart_setup();      //UART function call
    while (1) 
    {
        data = PORTB;
        switch(data) {
            case 0xE0:     //RB4 switch is pressed        
                TXREG = 'A';      // Transmit character 'A'
            __delay_ms(100); 
            break;
            case 0xD0:         //RB5 switch is pressed 
                TXREG = 'B';    // Transmit character 'B'
            __delay_ms(100);
            break;
            case 0xB0:        //RB6 switch is pressed 
                TXREG = 'C';     // Transmit character 'c'
            __delay_ms(100); 
            break;
            case 0x70:          //RB7 switch is pressed 
                TXREG = 'D';      // Transmit character 'D'
            __delay_ms(100); 
            break;
        }

        if (PIR1 & 0x20) { // Check if data received
            rx_data = RCREG;
            switch(rx_data) {
                case 'a': PORTD = 0x40; // 01000000 -> RD6 high
                break; 
                case 'b': PORTD = 0x02;  // 00000010 -> RD1 high
                break;
                case 'c': PORTD = 0x00;  // both LEDs off
                break;
                case 'd': PORTD = 0x42;  // 01000001 -> both LEDs on
                break;
            
            }
        }
    }
}

void uart_setup() {
    TRISB = 0xF0;  // Switch inputs on upper nibble
    TRISD = 0x00;  // set portd as output
    PORTB = 0x00;  // clear portB

    OPTION_REG &= 0x7F;
    TRISC = 0xC0; // RX and TX
    TXSTA = 0x20;  // Enable transmitter , asynchronous mode
    SPBRG = 0x09;  // Set baud rate
    RCSTA = 0x90; // enable receiver
}
