/**
 *--------------------------------------------------------------------\n
 *          HSLU T&A Hochschule Luzern Technik+Architektur            \n
 *--------------------------------------------------------------------\n
 *
 * \brief         Timer Output Compare (Playing Ring Tones)
 * \file
 * \author        Christian Jost, christian.jost@hslu.ch
 * \date          10.11.2012
 *
 * \b Language:   Ansi-C \n\n
 * \b Target:     MC-Car  \n
 *
 * \par Description:
 *
 * $Id: main_template.c 520 2013-11-11 09:55:21Z zajost $
 *--------------------------------------------------------------------
 */
#include "platform.h"   // include peripheral declarations
#include "ifrRx.h"
#include "motor.h"

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

/*
 * main program
 * */
void main(void)
{
        initPorts();            // Port init
        initTimer();            // Timer init
        ifrRxFrontInit();       // Infrared init
        motorInit();            // Motor init
        EnableInterrupts;       // Interrupts enable

        for(;;) {
                int8 speed = 0;
                switch (ifrRxFrontGetKey()) {
                        case 'S':	// stop
                                motorSetPWMLeft(0);
                                motorSetPWMRight(0);
                                break;

                        // @ToDo complete cases of the switch statement
                        case 'W':	// forward
                        		if ((motorGetPWMLeft() != 0) && (motorGetPWMRight() != 0)) {
                        			motorSetPWMLeft(80);
                        			motorSetPWMRight(80);
                        		} else {
                        			motorIncrementPWMLeft(5);
                        			motorIncrementPWMRight(5);
                        		}
                                break;
                        case 'T':	// backward
                        		if ((motorGetPWMLeft() != 60) && (motorGetPWMRight() != 60)) {
                        			motorSetPWMLeft(-80);
                        			motorSetPWMRight(-80);
                        		} else {
                        			motorIncrementPWMLeft(-5);
                        			motorIncrementPWMRight(-5);
                        		}
                                break;
                        case '+':	// left
                                motorIncrementPWMLeft(-1);
                                motorIncrementPWMRight(1);
                                break;
                        case '-':	// right
                                motorIncrementPWMLeft(1);
                                motorIncrementPWMRight(-1);
                                break;
                        default:
                                break;
                }
        }
}
