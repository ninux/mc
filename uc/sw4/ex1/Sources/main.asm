;--------------------------------------------------------------------
;          HSLU T&A Hochschule Luzern Technik+Architektur            
;--------------------------------------------------------------------
;
; \brief         Template for HCS08 Assembler
; \file
; \author        J.Wassner/C.Jost/L.Kressebuch
; \date          10.10.2012
;
; \b Language:   Assembler \n\n
; \b Target:     MC-CAR \n
;
; \par Description:
;
; $Id: main.asm 910 2014-09-22 07:41:25Z chj-hslu $
;--------------------------------------------------------------------
                include 'derivative.inc'
                

; Global definierte Symbole sind von aussen sichtbar.
;--------------------------------------------------------------------
                GLOBAL      _Startup    ; Start Hauptprogramm
                GLOBAL      main
                GLOBAL      dummy       ; Dummy Interrupt Service Routine

; EQUATIONS
;--------------------------------------------------------------------
StackSize:      EQU     $60             ; Equation for the stack size
pi:             EQU     31416           ; Example for a constant value

; STACK, VARIABLEN (Datenspeicher) und KONSTANTEN (Festwertspeicher) 
;--------------------------------------------------------------------
DATEN_STACK:    SECTION
TofStack:       DS      StackSize-1     ; definiton of "Top of Stack"
BofStack:       DS      1               ; definition of "Bottom of Stack"

DATEN:          SECTION
Variable1:      DS      1               ; Example of a 1 Byte Variable
Array1:         DS      $20             ; Example of an Array of $20 Bytes

KONSTANTEN:     SECTION
Maske1:         DC.B    %00000001
Parameter1:     DC.B    $3A             ; DC mit Punkt-> Coloring geht nicht!
Parameter2:     DC.W    57100
Reserve_Par:    DS      16              ; nur leerer Bereich reservieren!
STRING1:        DC.B    10,"Hello",$0D

; Programmstart (Initialisierungen)
;--------------------------------------------------------------------
PROGRAMM:       SECTION                 ; Code Segment
_Startup:                               ; Resetvektor zeigt hierhin
Stackinit:      LDHX    #(BofStack+1)
                TXS                     ; TXS dekrementiert, deshalb oben +1     
                LDA     #$00
                STA     SOPT1           ; Disable Watchdog

; Start des Benutzer-Codes
;--------------------------------------------------------------------   

main:  		LDA	#$FF
		STA	$00C0
		STA	$00C1

		BSET	0, PTFDD	; set F0 as output
		BSET	1, PTFDD	; set F1 as output
		BSET	2, PTFDD	; set F2 as output
		BSET	7, PTEDD	; set E7 as output
		
		BSET	0, PTFD		; clear output
		BSET	1, PTFD		; clear output
		BSET	2, PTFD		; clear output
		BSET	7, PTED		; clear output

		LDHX 	#$00C0		; read operand 1			        
		LDA	1, X		; read operand 2
		
		BRA	Armop		; jump to arithmetic operation


CheckC:		BRCLR	0, $00C1, CheckZ
CarrySet:	BCLR	0, PTFD

CheckZ:		BRCLR	1, $00C1, CheckV
ZSet:		BCLR	1, PTFD

CheckV:		BRCLR	7, $00C1, CheckN
VSet:		BCLR	7, PTED	

CheckN:		BRCLR	2, $00C1, EndLoop
		BCLR	2, PTFD
	
		BRA	EndLoop

Armop:		;ADD	1, X
		SUB	1, X

		TPA			; copy CCR to A
		STA	$00C1		; copy CCR to CCR_Result

		STA	$00C0		; save the result
		LDHX	$00C0		; write the result to X register
		BRA	CheckC

LightsOn:	BCLR	0, PTFD
		BCLR	1, PTFD
		BCLR	2, PTFD
		BCLR	7, PTED


EndLoop:        BRA     *               ; Endlos-Loop (=Programmende falls weiter oben Loop vergessen wurde)
                




;--------------------------------------------------------------------
; dummy - Alle nicht benutzten Interruptvektoren werden hierher
;         geleitet damit kein Absturz passiert, wenn ein unerwarteter
;         Interrupt auftritt. (z.B. loss of lock vom ICG)
;--------------------------------------------------------------------
dummy:          BGND
                BRA     dummy
