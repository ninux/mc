/**
 *--------------------------------------------------------------------\n
 *          HSLU T&A Hochschule Luzern Technik+Architektur            \n
 *--------------------------------------------------------------------\n
 *
 * \brief         Musterlösung uCOS-II, Aufgabe 3 - Lauflicht mit Sync.
 * \file
 * \author        Christian Jost, christian.jost@hslu.ch
 * \date          14.11.2010
 *
 * \b Language:   Ansi-C \n\n
 * \b Target:     Medusa-Trainer & Demoboard \n
 *
 * \par Description:
 *
 *
 *
 * $Id: aufgabe3_temp.c 552 2013-12-02 13:40:04Z zajost $
 *--------------------------------------------------------------------
 */
#include <hidef.h>      // for EnableInterrupts macro
#include "platform.h"   // include peripheral declarations
#if AUFGABE == 3

#define PRIO_INIT           0           // max. priority for the init task.
#define PRIO_ADC			1
#define PRIO_BLINK_LN       2
#define PRIO_BLINK_HN       3

#define TASK_STK_SIZE       128         // Stacksize for one Task

OS_STK InitTaskStack[TASK_STK_SIZE];    // allocate memory for the stack of the init task
OS_STK BlinkLNStack[TASK_STK_SIZE];     // allocate memory for the stack of the BlinkD1 task
OS_STK BlinkHNStack[TASK_STK_SIZE];     // allocate memory for the stack of the BlinkD3 task
OS_STK AdcTaskStack[TASK_STK_SIZE];		// allocate memory for the stack of the ADC task

volatile unsigned char ucDelayKitRight = 0xFF;
volatile unsigned char ucDelayKitLeft = 0xFF/2;

OS_EVENT *semLeft;
OS_EVENT *semRight;

void init_LED(void) {
	// set the IO direction
	PTDDD_PTDDD0 = 1;	// set as output
	PTDDD_PTDDD1 = 1;	
	PTDDD_PTDDD2 = 1;	
	PTDDD_PTDDD3 = 1;
	PTDDD_PTDDD4 = 1;
	PTDDD_PTDDD5 = 1;	
	PTDDD_PTDDD6 = 1;	
	PTDDD_PTDDD7 = 1;	
	
	// set the initial value
	PTDD_PTDD0 = 0;
	PTDD_PTDD1 = 0;
	PTDD_PTDD2 = 0;
	PTDD_PTDD3 = 0;
	PTDD_PTDD4 = 0;
	PTDD_PTDD5 = 0;
	PTDD_PTDD6 = 0;
	PTDD_PTDD7 = 0;
}

/**
 * This Task lets Bit1 of Port D blinking.
 *
 * @param pdata optional data (unused).
 */
void BlinkLN(void *pdata)
{
	unsigned char bitpos;
    (void)pdata;                        // prevents compiler warning
    
    for(;;)
    {
        // @todo implement BlinkLN-Task here
    	for (bitpos = 0; bitpos <= 3; bitpos++) {
    		PTDD = ~(~PTDD & 0xF0 | 1 << bitpos);
    		if (bitpos == 3) {
    			OSSemPost(semRight);
    			OSSemPend(semLeft, 0, OS_NO_ERR);
    		}
    		OSTimeDly(ucDelayKitRight);
    	}
    	
    }   
}

/**
 * This task lets Bit3 of Port D blinking.
 *
 *  @param pdata optional data (unused).
 */
void BlinkHN(void *pdata)
{
	unsigned char bitpos;
    (void)pdata;

    for(;;)
    {
        // @todo implement BlinkD3-Task here...
    	for (bitpos = 4; bitpos <= 7; bitpos++) {
    		PTDD = ~(~PTDD & 0x0F | 1 << bitpos);
    		if (bitpos == 7) {
    			OSSemPost(semLeft);
    			OSSemPend(semRight, 0, OS_NO_ERR);
    		}
    	    OSTimeDly(ucDelayKitLeft);
    	}
    }   
} 


/**
 * This task reads alternately the value of ATDCH 6 and 7 and
 * stores the 8 bit value in the variables ucDelayKitLeft and 
 * ucDelayKitRight.
 *
 * @param pdata optional data (unused).
 */
void AdcTask(void *pdata)
{
    (void)pdata;
    for(;;)
    {   
        OSTimeDly(5);
        if(ATD1SC_ATDCH == 7)
        {                                        // if +1 is neglected KitLeft
            ucDelayKitRight = (ATD1RH / 4) + 1;  // is blocked when poti7 is in
            ATD1SC_ATDCH=6;                      // left most position, because
        }                                        // KitLeft has lower prio
        else
        {
            ucDelayKitLeft = (ATD1RH / 4) + 1;
            ATD1SC_ATDCH=7;
        }
    }       
}


/**
 * Timer etc. initialisieren...
 *
 * @param pdata Optionale Daten für den Task beim Start.
 */
void adcInit(void)
{    
  ATD1C_ATDPU=1;                  // ATD power on
  ATD1C_PRS = 2;                  // set the prescaler. Valid for a busclock of 3-12 MHz.
  ATD1C_RES8=1;                   // 8BitData
  ATD1PE_ATDPE7=1;                // Pin enabled Channel 7
  ATD1PE_ATDPE6=1;                // Pin enabled Channel 6
  ATD1SC_ATDCO=0;                 // continuous conversion
  ATD1SC_ATDCH=7;                 // Select Input Channel 7
}

/**
 * Timer etc. initialisieren...
 *
 * @param pdata Optionale Daten für den Task beim Start.
 */
void InitTask(void* pdata)
{
#if OS_TASK_CREATE_EXT_EN > 0
    OS_STK_DATA LN, HN;
    unsigned char res1, res2;
#endif    
    
    (void)pdata;  
    OSTimerInit();                  // start timer (RTI)
    
#if OS_TASK_CREATE_EXT_EN > 0
    res1 = OSTaskCreateExt(BlinkLN, (void*)0, &BlinkLNStack[TASK_STK_SIZE-1], PRIO_BLINK_LN, PRIO_BLINK_LN,
            &BlinkD1Stack[0], TASK_STK_SIZE, (void *)0, OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
   
    res2 = OSTaskCreateExt(BlinkHN, (void*)0, &BlinkHNStack[TASK_STK_SIZE-1], PRIO_BLINK_HN, PRIO_BLINK_HN,      
            &BlinkHNStack[0], TASK_STK_SIZE, (void *)0, OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
   
    OSTimeDly(500);                 // Delay 500 x 20ms = 10sec
     
    res1 = OSTaskStkChk(PRIO_BLINK_LN, &LN);
    res2 = OSTaskStkChk(PRIO_BLINK_HN, &HN);
    
    asm bgnd;                       // Breakpoint
   
#else  
   semLeft = OSSemCreate(0);
   semRight = OSSemCreate(0);
   (void)OSTaskCreate(AdcTask, (void*)0, &AdcTaskStack[TASK_STK_SIZE-1], PRIO_ADC);
   (void)OSTaskCreate(BlinkLN, (void*)0, &BlinkLNStack[TASK_STK_SIZE-1], PRIO_BLINK_LN);
   (void)OSTaskCreate(BlinkHN, (void*)0, &BlinkHNStack[TASK_STK_SIZE-1], PRIO_BLINK_HN);
#endif

    (void)OSTaskDel(OS_PRIO_SELF);  // destroy the init task.
}

/**
 * main program
 * 
 * This function has the following tasks:
 * - init system clock
 * - init operating system
 * - create the first (init-) task
 * - start the os
 */
void main(void) 
{
    OSInit();                       // initialize the operating system
    
    init_LED();
    adcInit();
    
    // create the init task
    (void)OSTaskCreate(InitTask, (void*)0, &InitTaskStack[TASK_STK_SIZE-1], PRIO_INIT);  
     
    OSStart();                      // start the operating system  
}

#endif
