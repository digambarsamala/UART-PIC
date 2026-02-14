// PIC16F877A Slave Code
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
// Function declarationS
void uart_setup();
void lcd_init();
void lcd_command(unsigned char i);
void lcd_data(unsigned char i);

//variable declaration
unsigned char rx_data;
unsigned char i, x;

//array declaration
unsigned char rx[8] = {"Rx DATA:"};
unsigned char tx[8] = {"Tx DATA:"};

void main() {
    uart_setup();  //uart function call
    lcd_init();    //lcd fuction call

    lcd_command(0x80);     // Set cursor to first row, first column
    for (x = 0; x < 8; x++)      // Display "Rx DATA:" on LCD
    {
        lcd_data(rx[x]);       // Send each character to LCD
    }

    lcd_command(0xC0);   // Set cursor to second row, first column
    for (x = 0; x < 8; x++)     // Display "Tx DATA:" to LCD
    {
        lcd_data(tx[x]);        // Send each character to LCD
    }

    while (1) {
         // Check if data received
        if (PIR1 & 0x20) {
            rx_data = RCREG;     // Read received character from UART
            lcd_command(0x88);     // Move cursor to 9th position on 1st line
            lcd_data(rx_data); // show received data (A-D)

            lcd_command(0xC8);       // Move cursor to 9th position on 2nd line
            switch (rx_data) {
                case 'A': TXREG = 'a';   // Transmit 'a' back
                __delay_ms(100);
                lcd_data('a');      // Display 'a' on LCD
                break;
                case 'B': TXREG = 'b';
                __delay_ms(100);
                lcd_data('b'); 
                break;
                case 'C': TXREG = 'c'; 
                __delay_ms(100);
                lcd_data('c'); 
                break;
                case 'D': TXREG = 'd'; 
                __delay_ms(100);
                lcd_data('d'); 
                break;
            }
        }
    }
}
//initializing the LCD
void uart_setup() {
    TRISB = 0x00;   // Set PORTB as output
    TRISD = 0x00;   // Set PORTD as output
    TRISC = 0xC0;   //set RC6 (TX) and RC7 (RX) as inputs for UART

    TXSTA = 0x20;   // TX enable, async mode
    SPBRG = 0x09;   // Set baud rate
    RCSTA = 0x90;  // enable receiver
}

void lcd_init() {

    lcd_command(0x30);   //initializing the LCD
    __delay_ms(100);
    lcd_command(0x30);    //initializing the LCD
    __delay_ms(100);
    lcd_command(0x30);    //initializing the LCD
    __delay_ms(100);
    lcd_command(0x38);  //displaying characters on LCD In two lines
    __delay_ms(100);
    lcd_command(0x0C);     //Display on cursor off
    __delay_ms(100);
    lcd_command(0x01);     //clear the display
    __delay_ms(100);
}

void lcd_command(unsigned char i) {
    PORTB &= ~0x08;  // RS = 0
    PORTD = i;
    PORTB |= 0x02;   // EN = 1
    PORTB &= ~0x02;  // EN = 0
    __delay_ms(10);
}

void lcd_data(unsigned char i) {
    PORTB |= 0x08;   // RS = 1
    PORTD = i;
    PORTB |= 0x02;   // EN = 1
    PORTB &= ~0x02;  // EN = 0
    __delay_ms(10);
}
