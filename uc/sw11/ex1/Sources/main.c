/**
 *--------------------------------------------------------------------\n
 *          HSLU T&A Hochschule Luzern Technik+Architektur            \n
 *--------------------------------------------------------------------\n
 *
 * \brief         I2C Quadratur Signal Encoder
 * \file
 * \author        Christian Jost, christian.jost@hslu.ch
 * \date          10.11.2012
 *
 * \b Language:   Ansi-C \n\n
 * \b Target:     MC-Car  \n
 *
 * \par Description:
 *
 * $Id: main.c 523 2013-11-13 12:36:08Z zajost $
 *--------------------------------------------------------------------
 */
#include "platform.h" 	/* include peripheral declarations */
#include "i2c.h"
#include "ifrRx.h"
#include "motor.h"
#include "quad.h"


tQuadTicks ticks;      // for debugging purposes 
tQuadErrors errors;
tQuadSpeed speed;
tError e;

/**
 * Switch on Rear LEDs on Port D2
 */
void initPorts(void)
{
    PTDDD = 0x04;
    PTDD = 0x04;
}


/**
 * TPM1: Counter running with frequency 1 MHz
 * - No TOF interrupt
 * - Modulo = default
 * - Prescale = 1
 */
void initTimer(void)
{
  TPM1SC = 0x10;
}


/**
 * main program
 */  
void main(void) 
{
  uint8 i;
  initPorts();            // Port init
  initTimer();            // Timer init
  ifrRxFrontInit();       // Infrared init
  motorInit();            // Motor init
  
  i2cInit();
  
  EnableInterrupts;       // Interrupts enable 
        
  e = quadSetMode(qmEncoder);
  
  i=25;
  TPM1C3SC = 0x10;            // software compare only
  TPM1C3V = TPM1CNT + 20000;  // 20ms
  for(;;) 
  {
    if (TPM1C3SC_CH3F)
    {
      TPM1C3SC_CH3F = 0;
      TPM1C3V += 20000;      
      i--;
      if (i==0)
      {
        e = quadGetSpeed(&speed);
        //e = quadGetTicks(&ticks);
        //e = quadGetErrors(&errors);
        i = 25;
      }
    }
    switch (ifrRxFrontGetKey())
    {     
      case 'S' : motorSetPWMLeft(0); motorSetPWMRight(0); (void) quadResetTicks(); break;
      case 'W' : motorIncrementPWMLeft(10); motorIncrementPWMRight(10); break;
      case 'T' : motorIncrementPWMLeft(-10); motorIncrementPWMRight(-10); break; 
      case '+' : motorIncrementPWMLeft(1); motorIncrementPWMRight(1); break;
      case '-' : motorIncrementPWMLeft(-1); motorIncrementPWMRight(-1); break;
    }
  }
}
