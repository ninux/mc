/**
 *--------------------------------------------------------------------\n
 *          HSLU T&A Hochschule Luzern Technik+Architektur            \n
 *--------------------------------------------------------------------\n
 *
 * \brief         Musterlösung uCOS-II, Aufgabe 1 - Blink
 * \file
 * \author        Christian Jost, christian.jost@hslu.ch
 * \date          07.11.2010
 *
 * \b Language:   Ansi-C \n\n
 * \b Target:     Medusa-Trainer & Demoboard \n
 *
 * \par Description:
 * Template mit uCOS-II Betriebssystem.
 * Achtung, Clock-Konfiguration muss in den folgenden Dateien
 * angepasst werden:
 * - @ref os_cpu_c.c
 * - @ref os_cfg.h => @ref OS_TICKS_PER_SEC
 *
 * $Id: aufgabe1_temp.c 552 2013-12-02 13:40:04Z zajost $
 *--------------------------------------------------------------------
 */
#include <hidef.h>      // for EnableInterrupts macro
#include "platform.h"   // include peripheral declarations
#if AUFGABE == 1

#define PRIO_INIT           0           // max. priority for the init task.
#define PRIO_BLINK_D1       1
#define PRIO_BLINK_D3       2

#define TASK_STK_SIZE       128         // Stacksize for one Task

OS_STK InitTaskStack[TASK_STK_SIZE];    // allocate memory for the stack of the init task
OS_STK BlinkD1Stack[TASK_STK_SIZE];     // allocate memory for the stack of the BlinkD1 task
OS_STK BlinkD3Stack[TASK_STK_SIZE];     // allocate memory for the stack of the BlinkD3 task


/**
 * This Task lets Bit1 of Port D blinking.
 *
 * @param pdata optional data (unused).
 */
void BlinkD1(void *pdata)
{
    (void)pdata;                        // prevents compiler warning
    
    PTDDD_PTDDD0 = 1;	// set as output
    for(;;)
    {
        // @todo implement BlinkD1-Task here
    	PTDD_PTDD0 = 1;
    	OSTimeDlyHMSM(0,0,1,0);		
    	PTDD_PTDD0 = 0;
    	OSTimeDlyHMSM(0,0,1,0);
    }   
}


/**
 * This task lets Bit3 of Port D blinking.
 *
 *  @param pdata optional data (unused).
 */
void BlinkD3(void *pdata)
{
    (void)pdata;
    
    PTDDD_PTDDD3 = 1;	// set as output
    for(;;)
    {
        // @todo implement BlinkD3-Task here...
    	PTDD_PTDD3 = 1;
    	OSTimeDlyHMSM(0,0,2,0);
    	PTDD_PTDD3 = 0;
    	OSTimeDlyHMSM(0,0,2,0);
    }   
} 


/**
 * Timer etc. initialisieren...
 *
 * @param pdata Optionale Daten für den Task beim Start.
 */
void InitTask(void* pdata)
{
#if OS_TASK_CREATE_EXT_EN > 0
    OS_STK_DATA d1, d3;
    unsigned char res1, res2;
#endif    
    
    (void)pdata;  
    OSTimerInit();                  // start timer (RTI)
    
#if OS_TASK_CREATE_EXT_EN > 0
    res1 = OSTaskCreateExt(BlinkD1, (void*)0, &BlinkD1Stack[TASK_STK_SIZE-1], PRIO_BLINK_D1, PRIO_BLINK_D1,
            &BlinkD1Stack[0], TASK_STK_SIZE, (void *)0, OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
   
    res2 = OSTaskCreateExt(BlinkD3, (void*)0, &BlinkD3Stack[TASK_STK_SIZE-1], PRIO_BLINK_D3, PRIO_BLINK_D3,      
            &BlinkD3Stack[0], TASK_STK_SIZE, (void *)0, OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
   
    OSTimeDly(500);                 // Delay 500 x 20ms = 10sec
     
    res1 = OSTaskStkChk(PRIO_BLINK_D1, &d1);
    res2 = OSTaskStkChk(PRIO_BLINK_D3, &d3);
    
    asm bgnd;                       // Breakpoint
   
#else      
   (void)OSTaskCreate(BlinkD1, (void*)0, &BlinkD1Stack[TASK_STK_SIZE-1], PRIO_BLINK_D1);
   (void)OSTaskCreate(BlinkD3, (void*)0, &BlinkD3Stack[TASK_STK_SIZE-1], PRIO_BLINK_D3);
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
    
    // create the init task
    (void)OSTaskCreate(InitTask, (void*)0, &InitTaskStack[TASK_STK_SIZE-1], PRIO_INIT);  
     
    OSStart();                      // start the operating system  
}
#endif
