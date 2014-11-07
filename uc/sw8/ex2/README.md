# Exercise 1

Trace	| PC	| SP	| H/X	| C			| ASM
--------|-------|-------|-------|-----------------------|---------
BP	| 1B08 	| 02FF	| 	| function{}; 		| BSR -18 
1	| 1AF6	| 02FD	|	| void function2(void)	| AIS #-3
2	| 1AF8	| 02FA	|	| ucl = 1;		| LDA #0x01
3	| 1AFA	| 02FA	|	| ucl = 1;		| TSX
4	| 1AFB	| 02FA	| 02/FB	| ucl = 1;		| STA ,X
5	| 1AFC	| 02FA	|	| il = (int)ucl;	| LDX #0x01
6	| 1AFE	| 02FA	| 02/01	| il = (int)ucl;	| CLRH
7	| 1AFF	| 02FA	| 00/01	| il = (int)ucl;	| STHX 2,SP
8	| 1B02	| 02FA 	| 	| ucl++;		| INCA
9	| 1B03	| 02FA	|	| ucl++;		| TSX
10	| 1B04	| 02FA	| 02/FB	| ucl++;		| STA ,X
11	| 1B05	| 02FA	|	| }			| AIS #3
12	| 1B07	| 02FD	|	| }			| RTS 0x0000
13	| 1B0A	| 02FF	|	| for(;;){		| BRA +0
