#ifdef  OS_CPU_GLOBALS
#define OS_CPU_EXT
#else
#define OS_CPU_EXT  extern
#endif

typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                    
typedef signed   char  INT8S;                    
typedef unsigned int   INT16U;                   
typedef signed   int   INT16S;                   
typedef unsigned long  INT32U;                   
typedef signed   long  INT32S;                   
typedef float          FP32;                     
typedef double         FP64;                     

typedef unsigned char  OS_STK;                   
typedef unsigned char  OS_CPU_SR;                

#define BYTE           INT8S                     
#define UBYTE          INT8U                     
#define WORD           INT16S                    
#define UWORD          INT16U
#define LONG           INT32S
#define ULONG          INT32U
/* 
*********************************************************************************************************
*                              Motorola MC68HC908GP32
*********************************************************************************************************
*/
#define  OS_CRITICAL_METHOD    1

#if      OS_CRITICAL_METHOD == 1
#define  OS_ENTER_CRITICAL() {__asm SEI;}	
#define  OS_EXIT_CRITICAL() {__asm CLI;}
#endif

#if      OS_CRITICAL_METHOD == 2
#error "OS_CRITICAL_METHOD #2 - Not Implemented"
#endif

#if      OS_CRITICAL_METHOD == 3
#error "OS_CRITICAL_METHOD #1 - Not Implemented"
#endif


#define  OS_STK_GROWTH        1                       
#define  OS_TASK_SW()         {__asm SWI;}

/*
*********************************************************************************************************
*                                          FUNCTION PROTOTYPES
*********************************************************************************************************
*/
void OSTimerInit(void);
void OSStartHardware(void);

void OSStartHighRdy(void);
void OSIntCtxSw(void);
void OSCtxSw(void);
