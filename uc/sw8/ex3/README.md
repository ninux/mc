# Exercise 1

Trace	| PC	| SP	| H/X	| C					| ASM
--------|-------|-------|-------|---------------------------------------|---------
BP	| 1B02  | 02FF 	| 01/00	| void main(void)			| AIS #-3 
1	| 1B04	| 02FC 	| 01/00	| unsinged char uc1=0, uc2=0, uc3; 	| TSX
2	| 1B05	| 02FC	| 02/FD	| unsinged char uc1=0, uc2=0, uc3;	| CLR 2,X
3	| 1B07	| 02FC	| 02/FD	| unsigned char uc1=0, uc2=0, uc3; 	| CLR ,X
4	| 1B08	| 02FC	| 02/FD	| uc3 = function3(uc1, &uc2);		| CLRA 
5	| 1B09	| 02FC	| 02/FD	| uc3 = function3(uc1, &uc2);		| BSR -19 
6	| 1AF6	| 02FA 	| 02/FD	| char function3(unsigned char ucVal, unsigend char *ucRef)	| PSHH 
7	| 1AF7 	| 02F9 	| 02/FD	| ucl1 = ucVal;				| STA 1,SP 
8	|  	|  	|	| 	| 
9	| 	| 	|	| 	| 
10	| 	| 	|	| 	| 
11	| 	| 	|	| 	| 
12	| 	| 	|	| 	| 
13	| 	| 	|	| 	| 
