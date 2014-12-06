/**
 *--------------------------------------------------------------------\n
 *          HSLU T&A Hochschule Luzern Technik+Architektur            \n
 *--------------------------------------------------------------------\n
 *
 * \brief         A/D converter driver
 * \file
 * \author        Christian Jost, christian.jost@hslu.ch
 * \date          26.11.2012
 *
 * \b Language:   Ansi-C \n\n
 * \b Target:     MC-Car  \n
 *
 * \par Description:
 *
 * $Id: adc_temp.c 547 2013-12-01 18:41:02Z zajost $
 *--------------------------------------------------------------------
 */
#include "platform.h"
#include "adc.h"


#define ADC_RES_8BIT      0
#define ADC_RES_10BIT     2
#define ADC_RES_12BIT     1


/**
 * Performs one A/D conversion for the specified channel
 * with 12 bit resolution. The function blocks until the
 * conversion has been finished. 
 */
uint16 adcGet12BitValue(AdcChannels ch)
{
	// @ToDo implement function code

	ADCCFG_MODE = 0x01;			// select 12-bit mode
	ADCSC1_ADCH = (uint8)ch;	// select the channel
	
	while (!ADCSC1_COCO) {
		// wait till conversion is done
	}
	
	return ADCR;
}

/**
 * Performs one A/D conversion for the specified channel
 * with 10 bit resolution. The function blocks until the
 * conversion has been finished. 
 */
uint16 adcGet10BitValue(AdcChannels ch)
{
	// @ToDo implement function code
	
	ADCCFG_MODE = 0x02;			// select 10-bit mode
	ADCSC1_ADCH = (uint8)ch;	// select the channel
	
	while (!ADCSC1_COCO) {
		// wait thill conversion is done
	}
	
	return ADCR;
}

/**
 * Performs one A/D conversion for the specified channel
 * with 8 bit resolution. The function blocks until the
 * conversion has been finished. 
 */
uint8 adcGet8BitValue(AdcChannels ch)
{
	// @ToDo implement function code
	
	ADCCFG_MODE = 0x00;			// select 8-bit mode
	ADCSC1_ADCH = (uint8)ch;		// select the channel
	
	while (!ADCSC1_COCO) {
		// wait till conversion is done
	}
	
	return ADCRL;
}


/**
 * Configures the A/D converter as follows:
 * - high speed mode with long sample time
 * - set ADCK = 6 MHz (bus clock / 4)
 * - enables the four line sensors
 */
void adcInit(void)
{
  // @ToDo implement function code
	
	ADCSC1_ADCO = 0;		// single conversion mode
	
	ADCSC2_ADTRG = 0;		// trigger conversion by software
	ADCSC2_ACFE = 0;		// disable comparator mode
	
	ADCCFG_ADLPC = 0;		// high-speed configuration
	ADCCFG_ADIV = 0x02;		// divide clock by 4
	ADCCFG_ADLSMP = 1;		// configure to long sample time
	ADCCFG_ADICLK = 0x00;	// select bus clock
	
	// enable the channels
	APCTL1_ADPC4 = 1;
	APCTL1_ADPC5 = 1;
	APCTL1_ADPC6 = 1;
	APCTL1_ADPC7 = 1;
}
