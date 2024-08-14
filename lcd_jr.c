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
//=======================================================================================================

//=======================================================================================================
//--- Bibliotecas ---
#include "lcd_jr.h"

//=======================================================================================================
//--- Functions ---

//=======================================================================================================
//--- disp_Init ---
void disp_Init()
{
  __Delay(48);                  // Delay recomendado pelo fabricante de 40ms para mais 
  send_nibble(0x30,0);          // Envia os 4 primeiros nibbles 0011 0000
  __Delay(5);                   // Delay de 5 milisegundos 
  send_nibble(0x30,0);          // Envia novamente os 4 primeiros nibbles
  __DelayUs(150);               // Delay de 150us
  send_nibble(0x30,0);          // Envia novamente os 4 primeiros nibbles
  send_nibble(0x20,0);          // Envia o nibble 0010 
  disp_WriteCmd(0x28);          // 5x8 pontos por caractere, duas linhas
  disp_WriteCmd(0x0F);          // liga display, cursor e blink
  disp_WriteCmd(0x06);          // modo de incremento de endereco para a direita
  disp_Clear();                 // limpa o lcd

}//end disp_Init    

//=======================================================================================================
//--- disp_Clear ---
void disp_Clear()
{
  disp_WriteCmd(0x02);          // Retorna o cursor
  disp_WriteCmd(0x01);          // Limpa o display
}//end disp_Clear 

//=======================================================================================================
//--- disp_Putc ---
void disp_Putc(unsigned char chr)
{
  send_nibble(chr,1);           // Envia o char completo, enviando primeiro os 4 bits mais significativos
  chr <<= 4;                    // realiza o deslocamento e envia os 4 bits restantes.
  send_nibble(chr,1);           // Como e um envio de dados o Register select eh 1, caso fosse um comando
}// end disp_Putc               // utilizar 0.      

//=======================================================================================================
//--- disp_Puts ---
void disp_Puts(char *buffer)
{
  register int i=0;             // Variavel local para iteracoes
  while(buffer[i]!='\0')
  {
    disp_Putc(buffer[i]);       // Envia cada caractere para o lcd
    i++;
  }//end while

}// end disp_Puts

//=======================================================================================================
//--- disp_WriteCmd ---
void disp_WriteCmd(unsigned char cmd)
{
  send_nibble(cmd,0);           // Envia o byte completo, enviando primeiro os 4 bits mais significativos
  cmd <<= 4;                    // realiza o deslocamento e envia os 4 bits restantes.
  send_nibble(cmd,0);
}//end disp_WriteCmd 

//=======================================================================================================
//--- send_nibble ---
void send_nibble(unsigned char nib, char rsel)
{
  D4 = (nib>>4) & 0x01;
  D5 = (nib>>5) & 0x01;
  D6 = (nib>>6) & 0x01;
  D7 = (nib>>7) & 0x01;
  RS = rsel;

  // Envia pulso para Enable do display

  EN = 1;
  __DelayUs(1200);
  EN = 0;
  __DelayUs(1200);

}//end send_nibble   

//=======================================================================================================
//--- Send_number ---
void send_number(long int num)
{
  char dem,mil,cen,dez,uni;
  short no_zero = 0;

  dem = (char) (num/10000);
  mil = (char) ((num%10000)/1000);
  cen = (char) ((num%1000)/100);
  dez = (char) ((num%100)/10);
  uni = (char) (num%10);

  if(!dem && !no_zero)
    disp_Putc(' ');
  else
  {
    disp_Putc(0x30+dem);
    no_zero = 1;
  }// end else

  if(!mil && !no_zero)
    disp_Putc(' ');
  else
  {
    disp_Putc(0x30+mil);
    no_zero = 1;
  }// end else

  if(!cen && !no_zero)
    disp_Putc(' ');
  else
  {
    disp_Putc(0x30+cen);
    no_zero = 1;
  }// end else

  if(!dez && !no_zero)
    disp_Putc(' ');
  else
  {
    disp_Putc(0x30+dez);
    no_zero = 1;
  }// end else

  disp_Putc(0x30+uni);

}//end send_number   

//=======================================================================================================
//--- End of Program ---