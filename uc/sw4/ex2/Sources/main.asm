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

main:  		; clear the carry flag wit a bit-mask
		TPA			; load the CCR to accu
		AND	#$FE		; apply the bitmask [1111'1110] to clear the carry flag
		TAP			; write the result to CCR

		; set the overflow flag with a bit-mask
		TPA			; load the CCR to accu
		ORA	#$80		; load the bitmask [1000'0000] to set the overflow flag 
		TAP			; write the result to CCR

		; clear the carry flag and set the overflow flag without using a bit-mask
		CLC			; clear carry bit
		; there is no isntruction to set the overflow flag directly
		; onyl a isntruction BSET is available to set a bit in a memory address

EndLoop:        BRA     *               ; Endlos-Loop (=Programmende falls weiter oben Loop vergessen wurde)
                




;--------------------------------------------------------------------
; dummy - Alle nicht benutzten Interruptvektoren werden hierher
;         geleitet damit kein Absturz passiert, wenn ein unerwarteter
;         Interrupt auftritt. (z.B. loss of lock vom ICG)
;--------------------------------------------------------------------
dummy:          BGND
                BRA     dummy
