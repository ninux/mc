/**
 *--------------------------------------------------------------------\n
 *          HSLU T&A Hochschule Luzern Technik+Architektur            \n
 *--------------------------------------------------------------------\n
 *
 * \brief         C Template for the MC Car
 * \file
 * \author        Christian Jost, christian.jost@hslu.ch
 * \date          12.09.2014
 *
 * \b Language:   Ansi-C \n\n
 * \b Target:     MC-Car  \n
 *
 * \par Description:
 *
 * $Id: main.c 904 2014-09-12 10:58:43Z chj-hslu $
 *--------------------------------------------------------------------
 */
#include "platform.h" /* include peripheral declarations */

// #define TOGGLE_TIME 0xF423
#define TOGGLE_TIME 0x

unsigned char _memory @0x00C0;		/* ??? */

void initPorts(void)
{
	PTFDD = 0xff;	/* port F = output */
	PTGDD = 0x00;	/* port G = input */
	PTGPE = 0xff;	/* port G = pull-up enable */
	PTCDD = 0xff; 	/* port C = output */
}

void init_LED(void)
{
	PTFDD_PTFDD1 = 1;	/* set as output */
	PTFPE_PTFPE1 = 1;	/* enable pull-up */
	PTFD_PTFD1 = 0;		/* set to 0 */
	
	PTFDD_PTFDD2 = 1;	/* set as output */
	PTFPE_PTFPE2 = 1;	/* enable pull-up */
	PTFD_PTFD2 = 1;		/* set to 0 */
}

void init_timer1(void){
	TPM1SC_PS2 = 1;		/* set prescaler to 1:16 */
	TPM1SC_PS1 = 0;
	TPM1SC_PS0 = 0;
	
	TPM1MODH = 0xFF;	/* set the time */
	TPM1MODL = 0xFF;
	
	TPM1SC_TOF = 0;		/* clear the overflow flag */
	
	TPM1SC_TOIE = 1;	/* enable the timer interrupt */

	TPM1SC_CLKSB = 1;	/* set timer clock source to 1MHz fixed internal clock*/
	TPM1SC_CLKSA = 0;
}

void init_timer1_ch3(void){
	TPM1C3SC_MS3x = 0x01;	/* output compare */
	TPM1C3SC_ELS3x = 0x01;	/* toggle output */
	TPM1C3V = TOGGLE_TIME;	/* set the value */
	TPM1C3SC_CH3IE = 1;		/* enable the interrupt */
}

interrupt set_timer1_ch3(void)
{
	TPM1C3SC_CH3F = 0;		/* clear the interrupt-flag -> DO THIS AS FIRST OPERATION */
	TPM1C3V += TOGGLE_TIME;	/* update the value */
}

interrupt toggle_clock(void)
{
	TPM1SC_TOF = 0;				/* reset interrupt flag */
	PTFD_PTFD2 = ~PTFD_PTFD2;	/* toggle the clock LED */
}

/**
 * main program
 */  
void main(void) 
{
    init_LED();
    init_timer1();
    init_timer1_ch3();
    EnableInterrupts;

    while (1)
    {   
    	/* let the interrupt service routine do the job */
    }
    
  /* please make sure that you never leave main */
}

