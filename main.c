
#include "mcc_generated_files/system.h"

int k = 0;
long int keyPressRAW = 0;
int keyPress = 0;

void initADC(int amask)
{
    AD1PCFG = amask;
    AD1CON1 = 0x00E0;
    AD1CON2 = 0x0000;
    AD1CON3 = 0x1F01;
    AD1CSSL = 0;
    AD1CON1bits.ADON = 1;
}

int readADC(int ch)
{
    AD1CHS = ch;
    AD1CON1bits.SAMP = 1;
    while(!AD1CON1bits.DONE);
    AD1CON1bits.DONE = 0;
    return ADC1BUF0;
}

void _ISR _T1Interrupt (void)
{
    
    keyPressRAW = readADC(4);
    keyPress = keyPressRAW >> 2;
    keyPress = ~keyPress;
         
    for(k=0;k<100;k++);
   
    _T1IF = 0;  // Clear timer1 flag
}

int main(void)
{
    SYSTEM_Initialize();

    TRISFbits.TRISF2 = 0;
    _RF2 = 1;
    
    TRISDbits.TRISD6 = 1;
    T1CON = 0x8030;  //  1:256, turn on
    PR1 = 62500 - 1;  // timer1 counts up to 1 s
    
    _T1IF = 0;   // clear timer 1 interrupt flag
    _T1IE = 1;  // do this after in case the enable was not cleared. 
    
    initADC(0xFFEF);
    
    while(1)
    {
        Nop();
    }

    return 1;
}
