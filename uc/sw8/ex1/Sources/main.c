/**
 *--------------------------------------------------------------------\n
 *          HSLU T&A Hochschule Luzern Technik+Architektur            \n
 *--------------------------------------------------------------------\n
 *
 * \brief         Uebung 5: Function Call & Stack
 * \file
 * \author        Christian Jost, christian.jost@hslu.ch
 * \date          04.10.2012
 *
 * \b Language:   Ansi-C \n\n
 * \b Target:     MC-Car  \n
 *
 * \par Description:
 *
 * $Id: main.c 503 2013-10-23 05:51:56Z zajost $
 *--------------------------------------------------------------------
 */
#include "platform.h" /* include peripheral declarations */



#define AUFGABE 1       // Wähle Aufgabe = 1..4

/* Aufgabe 5.1
***********************************************************/
void function1(void)
{
    asm NOP;
}


/* Aufgabe 5.2
***********************************************************/
void function2(void)
{
    unsigned char ucl;
    int il;
    
    ucl = 1;
    il = (int)ucl;
    ucl++;            // Wegen diesem statement liegt ucl im
                    // Stack über il
}


/* Aufgabe 5.3
***********************************************************/
char function3 (unsigned char ucVal, unsigned char *ucRef)
{
    unsigned char ucl1;
    ucl1 = ucVal;
    ucl1++;
    (*ucRef)++; // Achtung: ohne Klammern wird Pointer inkrementiert
    return ucl1;
}


/* Aufgabe 5.4 (optional; Input von Sop)
***********************************************************/
struct point 
{
    int x;
    int y;
};              
struct point addpoint(struct point p1, struct point p2) 
{
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
}
  
/**
 * Hauptprogramm
 *
 */  
void main(void) 
{
#if AUFGABE == 1

    function1(); 

#elif AUFGABE == 2

    function2(); 

#elif AUFGABE == 3

    unsigned char uc1=0, uc2=0, uc3;
    
    uc3 = function3(uc1, &uc2);
    uc3++;
  
#else

    struct point pkt1 = {1, 3};   
    struct point pkt2 = {2, 4};
    struct point pkt3;

    pkt3 = addpoint(pkt1, pkt2);

#endif

    for(;;) {}

}
