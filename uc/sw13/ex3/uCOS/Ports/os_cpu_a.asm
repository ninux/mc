;********************************************************************************************************
;                                               uC/OS-II
;                                         The Real-Time Kernel
;
;                                          68HC08 Specific code
;
; File : OS_CPU_A.ASM
; By   : Kerby Suhre
;********************************************************************************************************

    xdef   OSStartHighRdy
    xdef   OSCtxSw
    xdef   OSIntCtxSw

    xref   OSIntExit
    xref   OSIntNesting  
    xref   OSPrioCur    
    xref   OSPrioHighRdy
    xref   OSRunning   
    xref   OSTaskSwHook 
    xref   OSTCBCur     
    xref   OSTCBHighRdy 
    xref   OSTimeTick

MY_ROM: SECTION


;********************************************************************************************************
;                               START HIGHEST PRIORITY TASK READY-TO-RUN
;
; Description : This function is called by OSStart() to start the highest priority task that was created
;               by your application before calling OSStart().
;
; Arguments   : none
;
; Note(s)     : 1) The stack frame is assumed to look as follows:
;  
;   
;                  OSTCBHighRdy->OSTCBStkPtr +  0  -->  H
;                                            +  1       CCR
;                                            +  2       A
;                                            +  3       X
;                                            +  4       PC(H)
;                                            +  5       PC(L)
;
; 
;
;               2) OSStartHighRdy() MUST:
;                      a) Call OSTaskSwHook() then,
;                      b) Set OSRunning to TRUE,
;                      c) Switch to the highest priority task.
;********************************************************************************************************

OSStartHighRdy:
	jsr 	OSTaskSwHook 	   				; Invoke user defined context switch hook           
    
	lda	#$01		                  	; Indicate that we are multitasking
	sta	OSRunning
		
	ldhx	OSTCBHighRdy						; OSTCBHighRdy points to TCB of highest priority task ready to run
	ldhx	0,x									; Load the addres of the SP into the X-Reg. SP is the first entry in TCB
	txs											; Set the SP
	
	pulh							  				; Restore Index Reg. H (High)
	
	rti											; Run task
    
    
    

;********************************************************************************************************
;                                    INTERRUPT LEVEL CONTEXT SWITCH
;
; Description : This function is called by OSIntExit() to perform a context switch to a task that has
;               been made ready-to-run by an ISR.
;
; Arguments   : none
;
; Note(s)     : 
;               1) Stack frame upon entry:
;
;                                ---   SP +  0 ->  
;                                |         +  1 -> PC(H)   \    Return address from call to OSIntCtxSw()
;      Stack pointer adjustment  |         +  2 -> PC(L)   /
;            (+4)                |         +  3 -> PC(H)   \    Return address from call to OSIntExit()
;                                -->       +  4 -> PC(L)   /
;                                          +  1       H    \
;                                          +  2       CCR   |   Stack frame from interrupt stacking.
;                                          +  3       A     |
;                                          +  4       X     |
;                                          +  5       PC(H) |
;                                          +  6       PC(L)/
;********************************************************************************************************

OSIntCtxSw:
	ais	   #4									; Ignore return address to OSIntCtxSw() and 
	bra	   OSIntCtxSwRtn              ; return address from call to OSIntExit()     
	
	
	
	
    
    
;********************************************************************************************************
;                                       TASK LEVEL CONTEXT SWITCH
;
; Description : This function is called when a task makes a higher priority task ready-to-run.
;
; Arguments   : none
;
; Note(s)     : 1) Upon entry, 
;                  OSTCBCur     points to the OS_TCB of the task to suspend
;                  OSTCBHighRdy points to the OS_TCB of the task to resume
;
;               2) The stack frame of the task to suspend looks as follows:
;
;                  SP +  0  -->  H
;                     +  1       CCR
;                     +  2       A
;                     +  3       X
;                     +  4       PC(H)
;                     +  5       PC(L)
;
;               3) The stack frame of the task to resume looks as follows:
; 
;                  OSTCBHighRdy->OSTCBStkPtr +  0  -->  H
;                                            +  1       CCR
;                                            +  2       A
;                                            +  3       X
;                                            +  4       PC(H)
;                                            +  5       PC(L)
;********************************************************************************************************

OSCtxSw:
	pshh							  				; Save Index Reg. H (High) on the stack
OSIntCtxSwRtn:
	tsx											; Copy SP to X-Reg
	pshx											; Save SP-Low-Byte on the stack
	pshh											; Save SP-High-Byte on the stack
	
	ldhx	OSTCBCur								; Load the addres of the SP into the X-Reg. SP is the first entry in TCB
	
	pula											; Load SP-High-Byte from Stack into A
	sta	0,x									; Store SP-High-Byte on the TCP
	pula											; Load SP-Low-Byte from Stack into A
	sta	1,x									; Store SP-Low-Byte on the TCP

	jsr	OSTaskSwHook						; Invoke user defined context switch hook    
	
	ldhx	OSTCBHighRdy               	; OSTCBCur  = OSTCBHighRdy
	sthx	OSTCBCur
	
	lda	OSPrioHighRdy              	; OSPrioCur = OSPrioHighRdy
	sta	OSPrioCur
	
	ldhx	0,x									; Load the addres of the SP into the X-Reg. SP is the first entry in TCB
	txs											; Set the SP
	
	pulh							  				; Restore Index Reg. H (High)
	
	rti											; Run task	
	
