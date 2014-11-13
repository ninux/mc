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
	PTFDD_PTFDD0 = 1;	/* set as output */
	PTFPE_PTFPE0 = 1;	/* enable pull-up */
	PTFD_PTFD0 = 0;		/* set to 0 */
	
	PTFDD_PTFDD2 = 1;	/* set as output */
	PTFPE_PTFPE2 = 1;	/* enable pull-up */
	PTFD_PTFD2 = 1;		/* set to 0 */
}

void init_timer(){
	/* set prescaler to 1:16 */
	TPM1SC_PS2 = 1;
	TPM1SC_PS1 = 0;
	TPM1SC_PS0 = 0;
	
	/* set the time to 1 second with 62500-1 */
	TPM1MODH = 0xF4;
	TPM1MODL = 0x23;
	
	/* clear the overflow flag */
	TPM1SC_TOF = 0;
	
	/* set timer clock source to 1MHz fixed internal clock*/
	TPM1SC_CLKSB = 1;
	TPM1SC_CLKSA = 0;
}


/**
 * main program
 */  
void main(void) 
{
	unsigned char tmp;
	/* initPorts(); */
    EnableInterrupts;
    
    init_LED();
    init_timer();

    while (1)
    {   
    	if (TPM1SC_TOF) {
    		PTFD_PTFD0 = ~PTFD_PTFD0;
    		PTFD_PTFD2 = ~PTFD_PTFD2;
    		TPM1SC_TOF = 0;
    	}
    }
    
  /* please make sure that you never leave main */
}

