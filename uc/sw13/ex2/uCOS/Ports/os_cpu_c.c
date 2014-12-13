/*
*********************************************************************************************************
*                                               uC/OS-II
*                                         The Real-Time Kernel
*
*                                         6808 Specific code
*
* File : OS_CPU_C.C
* By   : Kerby Suhre
*********************************************************************************************************
*/
#define  OS_CPU_GLOBALS
//#include "includes.h"
#include "platform.h"




/**
 * Initialisierung des Timers für den TimerTick des OS
 * 
 * Konfiguration:
 * - Quarz: 9.8304 Mhz
 * - Prescaler: 32768
 * => RTI erfolgt alle 3.3ms
 */
void OSTimerInit(void)
{
    SRTISC_RTICLKS = 1;     // Clocksource = external clock
    SRTISC_RTIS = 7;        // Interrupt generated all 3.33ms --> OSTick all 20ms
    SRTISC_RTIE = 1;        // RT-Interrupt enable
}


/**
 * Die folgende ISR wird alle 3.3ms aufgerufen und dazu gebraucht,
 * den Timertick für das OS zu erzeugen.
 * 
 * 3.3ms ist die längste einstellbare Zeit bei einem ext. Quarz von
 * 9.8304 MHz.
 * Bei jedem sechsten Aufruf wird das OS darüber informiert
 * => 6 x 3.3ms = 20ms. Somit erhält das OS alle 20ms die Kontrolle
 * und kann - falls notwendig - einen Taskswitch veranlassen.
 * 
 * Diese Zeit (20ms) müssen dem OS in der Datei os_cfg.h mitgeteilt
 * werden (@ref OS_TICKS_PER_SEC), indem man die Anzahl Ticks/sec 
 * angibt. In diesem Fall sind es 50 Ticks da 50 x 20ms = 1sec ergeben.
 */
interrupt void OSTickISR(void)
{
    static INT8U count = 0;
    
    SRTISC_RTIACK = 1;              // RTI Interrupt quittieren
        
    if (count < 5) // 5
    {
        count++;
    }
    else
    {
        count = 0;
        
        OSIntEnter();           
        OSTimeTick();               // OS informieren (20ms Tick)
        OSIntExit();
    
    /*
        OSIntEnter();
        if(OSIntNesting==1)
        {
            //Speichern des momentanen Stack Pointers
            asm
            {
                tsx
                pshx
                pshh
                ldhx    OSTCBCur
                pula
                sta 0,x
                pula
                sta 1,x
            }
        }
        OSTimeTick();                       // OS benachrichtigen
        OSIntExit();
        */
    }
}


/*
*********************************************************************************************************
*                                        INITIALIZE A TASK'S STACK
*
* Description: This function is called by either OSTaskCreate() or OSTaskCreateExt() to initialize the
*              stack frame of the task being created.  This function is highly processor specific.
*
* Arguments  : task          is a pointer to the task code
*
*              pdata         is a pointer to a user supplied data area that will be passed to the task
*                            when the task first executes.
*
*              ptos          is a pointer to the top of stack.  It is assumed that 'ptos' points to
*                            a 'free' entry on the task stack.  If OS_STK_GROWTH is set to 1 then 
*                            'ptos' will contain the HIGHEST valid address of the stack.  Similarly, if
*                            OS_STK_GROWTH is set to 0, the 'ptos' will contains the LOWEST valid address
*                            of the stack.
*
*              opt           specifies options that can be used to alter the behavior of OSTaskStkInit().
*                            (see uCOS_II.H for OS_TASK_OPT_???).
*
* Returns    : Always returns the location of the new top-of-stack' once the processor registers have
*              been placed on the stack in the proper order.
*********************************************************************************************************
*/
OS_STK *OSTaskStkInit (void (*task)(void *pd), void *pdata, OS_STK *ptos, INT16U opt)
{
    INT16U   *stk;
    (void)pdata;
    (void)opt;
//    opt    = opt;                             // 'opt' is not used, prevent warning        
    stk    = (INT16U *)ptos;           // Load stack pointer                        
    *--stk = (INT16U)(task);                // Program counter                              
    *--stk = (INT16U)(0x00);            // X and A registers                                    
    *--stk = (INT16U)(0x00);            // CCR and H registers, (H not saved during interrupt)
    return ((void *)stk);
}


/*$PAGE*/
#if OS_CPU_HOOKS_EN
/*
*********************************************************************************************************
*                                          TASK CREATION HOOK
*
* Description: This function is called when a task is created.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being created.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
void OSTaskCreateHook (OS_TCB *ptcb)
{
    (void)ptcb;
//    ptcb = ptcb;                       /* Prevent compiler warning                                     */
}


/*
*********************************************************************************************************
*                                           TASK DELETION HOOK
*
* Description: This function is called when a task is deleted.
*
* Arguments  : ptcb   is a pointer to the task control block of the task being deleted.
*
* Note(s)    : 1) Interrupts are disabled during this call.
*********************************************************************************************************
*/
void OSTaskDelHook (OS_TCB *ptcb)
{
    (void)ptcb;
//    ptcb = ptcb;                       /* Prevent compiler warning                                     */
}

/*
*********************************************************************************************************
*                                           TASK SWITCH HOOK
*
* Description: This function is called when a task switch is performed.  This allows you to perform other
*              operations during a context switch.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts are disabled during this call.
*              2) It is assumed that the global pointer 'OSTCBHighRdy' points to the TCB of the task that
*                 will be 'switched in' (i.e. the highest priority task) and, 'OSTCBCur' points to the 
*                 task being switched out (i.e. the preempted task).
*********************************************************************************************************
*/
void OSTaskSwHook (void)
{
}

/*
*********************************************************************************************************
*                                           STATISTIC TASK HOOK
*
* Description: This function is called every second by uC/OS-II's statistics task.  This allows your 
*              application to add functionality to the statistics task.
*
* Arguments  : none
*********************************************************************************************************
*/
void OSTaskStatHook (void)
{
}

/*
*********************************************************************************************************
*                                               TICK HOOK
*
* Description: This function is called every tick.
*
* Arguments  : none
*
* Note(s)    : 1) Interrupts may or may not be ENABLED during this call.
*********************************************************************************************************
*/
void OSTimeTickHook (void)
{
}


#if OS_VERSION > 203
void OSInitHookBegin (void)
{
}


void OSInitHookEnd (void)
{
}


void OSTCBInitHook (OS_TCB *ptcb)
{
    (void)ptcb;
}
#endif


#if OS_VERSION >= 205
void OSTaskIdleHook (void)
{
}
#endif

#endif



/*
*********************************************************************************************************
*                                           START HARDWARE
* Description: This function is called to start the hardware timer tick and enable interrupts.
*
* Arguments  : none
*********************************************************************************************************
*/
void OSStartHardware(void)
{
    /* Start the tick timer and enable interrupts */
    OSTimerInit();
}


