//=======================================================================================================
//
//     ██╗██████╗     ███████╗██╗     ███████╗ ██████╗████████╗██████╗  ██████╗ ███╗   ██╗██╗ ██████╗
//     ██║██╔══██╗    ██╔════╝██║     ██╔════╝██╔════╝╚══██╔══╝██╔══██╗██╔═══██╗████╗  ██║██║██╔════╝
//     ██║██████╔╝    █████╗  ██║     █████╗  ██║        ██║   ██████╔╝██║   ██║██╔██╗ ██║██║██║     
//██   ██║██╔══██╗    ██╔══╝  ██║     ██╔══╝  ██║        ██║   ██╔══██╗██║   ██║██║╚██╗██║██║██║     
//╚█████╔╝██║  ██║    ███████╗███████╗███████╗╚██████╗   ██║   ██║  ██║╚██████╔╝██║ ╚████║██║╚██████╗
// ╚════╝ ╚═╝  ╚═╝    ╚══════╝╚══════╝╚══════╝ ╚═════╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚═╝ ╚═════╝
//                                                                                                 
//=======================================================================================================

//=======================================================================================================
//
//   Title: Display LCD 16x2 control, mode 4 bits.
//   Author: Joao Ricardo Chaves.
//   Date: August,2024.
//  
//   Compiler: MPLAB X - XC8.
//   MCU: PIC18F4550.
//   CLK: 20MHz Crystal.
//=======================================================================================================

#ifndef LCD_JR_h
#define LCD_JR_h

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 20000000
#endif

//=======================================================================================================
//--- Libraries ---
#include <xc.h>

//=======================================================================================================
//--- Hardware Mapping ---

#define EN  LATEbits.LE1
#define RS  LATEbits.LE0
#define D4  LATDbits.LD4
#define D5  LATDbits.LD5
#define D6  LATDbits.LD6
#define D7  LATDbits.LD7

//=======================================================================================================
//--- Macros ---

#define __Delay(t)   __delay_ms(t)
#define __DelayUs(t) __delay_us(t)

//=======================================================================================================
//--- Functions Prototypes ---

void disp_Init();                                     // Inicializa o LCD
void disp_Clear();                                    // Limpa o LCD
void disp_Putc(unsigned char chr);                    // Escreve um caracter no LCD
void disp_Puts(char *buffer);                         // Escreve uma string no LCD
void disp_WriteCmd(unsigned char cmd);                // Envia um comando para o LCD
void send_nibble(unsigned char nib, char rsel);       // Envia cada nibble separadamente
void send_number(long int num);                       // Exibe um num inteiro de ate 5 digitos

#endif
//=======================================================================================================
//--- End of Program ---