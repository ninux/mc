# Exercise 1

Trace	| PC	| SP	| HX	| C		| ASM
--------|-------|-------|-------|---------------|---------
BP	| 1AF8	| 2FF	|	| function();	| BSR -2
1	| 1AF6	| 2FD	|	| { NOP;	| NOP
2	| 1AF7	| 2FD	|	| }		| RTS
3	| 1AFA	| 2FF	|	| for(;;) {}	| BRA +0 
