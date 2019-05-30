/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                                       WIN32 PORT & LINUX PORT
*                          (c) Copyright 2004, Werner.Zimmermann@fht-esslingen.de
*                 (Similar to Example 1 of the 80x86 Real Mode port by Jean J. Labrosse)
*                           Modified to Test Interrupts by Amr Ali Abdel-Naby
*                                           All Rights Reserved
*
*                                               EXAMPLE #5
*********************************************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS
#include "includes.h"

/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/

#define  TASK_STK_SIZE                 512       /* Size of each task's stacks (# of WORDs)            */
#define  N_TASKS                        10       /* Number of identical tasks                          */
/* @May 29th, 2010 By: Amr Ali Abdel-Naby */
#define  N_INTERRUPTS                    5       /* Number of interrupts that will drive the tasks     */

/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/
OS_STK        TaskStk[N_TASKS][TASK_STK_SIZE];        /* Tasks stacks                                  */
OS_STK        TaskStartStk[TASK_STK_SIZE];

char          TaskData[N_TASKS];                      /* Parameters to pass to each task               */
OS_EVENT     *RandomSem;
/* @May 29th, 2010 By: Amr Ali Abdel-Naby */
/*
*********************************************************************************************************
* Define the 5 semaphores used by interrupts
*********************************************************************************************************
*/
// Add your code here!!
OS_EVENT* Sem0,* Sem1,* Sem2,* Sem3,* Sem4;
// End of your code!!

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

        void  Task(void *data);                       /* Function prototypes of tasks                       */
        void  TaskInterrupt(void *data);              /* Function prototypes of tasks derived by interrupts */
        void  TaskStart(void *data);                  /* Function prototypes of Startup task                */
static  void  TaskStartCreateTasks(void);
static  void  TaskStartDispInit(void);
static  void  TaskStartDisp(void);
/* @May 29th, 2010 By: Amr Ali Abdel-Naby */
/* ISRs installation function and ISRs prototypes */
static  void  TaskInstallISRs(void);
        void  ISR0(void);                             /* Function prototypes of the ISRs                    */
        void  ISR1(void);
        void  ISR2(void);
        void  ISR3(void);
        void  ISR4(void);

/*$PAGE*/
/*
*********************************************************************************************************
*                                                MAIN
*********************************************************************************************************
*/

int  main (void)
{
    INT8U i;
    OSInit();                                              /* Initialize uC/OS-II                      */


    RandomSem   = OSSemCreate(1);                          /* Random number semaphore                  */
    /* @May 29th, 2010 By: Amr Ali Abdel-Naby */
/*
*********************************************************************************************************
* Create the 5 semaphores to be used from interrupts
*********************************************************************************************************
*/
// Add your code here!!
    Sem0    = OSSemCreate(0);
    Sem1    = OSSemCreate(0);
    Sem2    = OSSemCreate(0);
    Sem3    = OSSemCreate(0);
    Sem4    = OSSemCreate(0);
// End of your code!!

    PC_DispClrScr(DISP_FGND_WHITE + DISP_BGND_BLACK);      /* Clear the screen                         */

    OSTaskCreate(TaskStart, (void *)0, &TaskStartStk[TASK_STK_SIZE - 1], 0);
    OSStart();                                             /* Start multitasking                       */
    return 0;
}


/*
*********************************************************************************************************
*                                              STARTUP TASK
*********************************************************************************************************
*/
void  TaskStart (void *pdata)
{
    INT16S     key;


    pdata = pdata;                                         /* Prevent compiler warning                 */

    TaskStartDispInit();                                   /* Initialize the display                   */

    TaskStartCreateTasks();                                /* Create all the application tasks         */

/* @May 29th, 2010 By: Amr Ali Abdel-Naby */
/* Added to install ISRs */
    TaskInstallISRs();                                     /* Install all the application ISRs         */

#if OS_TASK_STAT_EN > 0
    OSStatInit();                                          /* Initialize uC/OS-II's statistics         */
#endif
    for (;;) {
        TaskStartDisp();                                   /* Update the display                       */

        if (PC_GetKey(&key) == TRUE) {                     /* See if key has been pressed              */
            if (key == 0x1B) {                             /* Yes, see if it's the ESCAPE key          */
                exit(0);                                   /* End program                              */
            }
        }

        OSCtxSwCtr = 0;                                    /* Clear context switch counter             */
        OSTimeDlyHMSM(0, 0, 1, 0);                         /* Wait one second                          */

    }
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                        INITIALIZE THE DISPLAY
*********************************************************************************************************
*/

static  void  TaskStartDispInit (void)
{
/*                                1111111111222222222233333333334444444444555555555566666666667777777777 */
/*                      01234567890123456789012345678901234567890123456789012345678901234567890123456789 */
    PC_DispStr( 0,  0, "                         uC/OS-II, The Real-Time Kernel                         ", DISP_FGND_WHITE + DISP_BGND_RED);
    /* @Feb 17th, 2010 By: Amr Ali Abdel-Naby */
    /* Removed Linux simulation code and kept only Windows simulation code and Added my Integration Message */
    PC_DispStr( 0,  1, "   Original version by Jean J. Labrosse, PC Utility port by Werner Zimmermann   ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0,  2, "                    Integration on Vista by Amr A. Abdel-Naby                   ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr( 0,  3, "                                    EXAMPLE #5                                  ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr( 0,  4, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr( 0,  5, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr( 0,  6, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr( 0,  7, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr( 0,  8, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr( 0,  9, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr( 0, 10, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr( 0, 11, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr( 0, 12, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr( 0, 13, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr( 0, 14, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr( 0, 15, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr( 0, 16, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr( 0, 17, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr( 0, 18, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr( 0, 19, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr( 0, 20, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr( 0, 21, "#Tasks          :        CPU Usage:     %                                       ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr( 0, 22, "#Task switch/sec:                                                               ", DISP_FGND_BLACK + DISP_BGND_WHITE);
    PC_DispStr( 0, 23, "                            <-PRESS 'ESC' TO QUIT->                             ", DISP_FGND_BLACK + DISP_BGND_WHITE);
/*                                1111111111222222222233333333334444444444555555555566666666667777777777 */
/*                      01234567890123456789012345678901234567890123456789012345678901234567890123456789 */
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                           UPDATE THE DISPLAY
*********************************************************************************************************
*/

static  void  TaskStartDisp (void)
{
    char   s[80];

    sprintf(s, "%5d", OSTaskCtr);                                  /* Display #tasks running               */
    PC_DispStr(18, 21, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);

#if OS_TASK_STAT_EN > 0
    sprintf(s, "%3d", OSCPUUsage /*OSIdleCtr/(OSIdleCtrMax/100)*/);/* Display CPU usage in %               */
    PC_DispStr(36, 21, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);
#endif

    PC_GetDateTime(s);
    PC_DispStr(58, 21, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);

    sprintf(s, "%5d", OSCtxSwCtr);                                 /* Display #context switches per second */
    PC_DispStr(18, 22, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);

    /* @Feb 17th, 2010 By: Amr Ali Abdel-Naby */
    /* Removed Linux simulation code, kept only Windows simulation code, and modified the version code to map to V2.86 */
    sprintf(s, "uCOS-II V%1d.%02d", OSVersion() / 100, OSVersion() % 100); /* Display uC/OS-II's version number    */
    PC_DispStr(58, 22, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);
}

/*$PAGE*/
/*
*********************************************************************************************************
*                                             CREATE TASKS
*********************************************************************************************************
*/

static  void  TaskStartCreateTasks (void)
{
    INT8U  i;
/*
*********************************************************************************************************
* Create the 10 tasks
*********************************************************************************************************
*/
// Add your code here!!
    TaskData[0] = '0', OSTaskCreate(Task, &TaskData[0], &TaskStk[0][TASK_STK_SIZE - 1], 1);
    TaskData[1] = '1', OSTaskCreate(Task, &TaskData[1], &TaskStk[1][TASK_STK_SIZE - 1], 2);
    TaskData[2] = '2', OSTaskCreate(Task, &TaskData[2], &TaskStk[2][TASK_STK_SIZE - 1], 3);
    TaskData[3] = '3', OSTaskCreate(Task, &TaskData[3], &TaskStk[3][TASK_STK_SIZE - 1], 4);
    TaskData[4] = '4', OSTaskCreate(Task, &TaskData[4], &TaskStk[4][TASK_STK_SIZE - 1], 5);
    TaskData[5] = '5', OSTaskCreate(TaskInterrupt, &TaskData[5], &TaskStk[5][TASK_STK_SIZE - 1], 6);
    TaskData[6] = '6', OSTaskCreate(TaskInterrupt, &TaskData[6], &TaskStk[6][TASK_STK_SIZE - 1], 7);
    TaskData[7] = '7', OSTaskCreate(TaskInterrupt, &TaskData[7], &TaskStk[7][TASK_STK_SIZE - 1], 8);
    TaskData[8] = '8', OSTaskCreate(TaskInterrupt, &TaskData[8], &TaskStk[8][TASK_STK_SIZE - 1], 9);
    TaskData[9] = '9', OSTaskCreate(TaskInterrupt, &TaskData[9], &TaskStk[9][TASK_STK_SIZE - 1], 10);

// End of your code!!
}
/*$PAGE*/

/* @May 29th, 2010 By: Amr Ali Abdel-Naby */
/* Added to install ISRs */

/*
*********************************************************************************************************
*                                             INSTALL ISRS
*********************************************************************************************************
*/
static  void  TaskInstallISRs(void)
{
    PC_IntVectSet(0, ISR0);
    PC_IntVectSet(1, ISR1);
    PC_IntVectSet(2, ISR2);
    PC_IntVectSet(3, ISR3);
    PC_IntVectSet(4, ISR4);
}
/*
*********************************************************************************************************
*                                                  TASKS
*********************************************************************************************************
*/

void  Task (void *pdata)
{
    INT8U  x;
    INT8U  y;
    INT8U  err;
    /* @Feb 17th, 2010 By: Amr Ali Abdel-Naby */
    /* Added a string buffer to make the example work on Vista */
    char   s[80];

    /* @Feb 17th, 2010 By: Amr Ali Abdel-Naby */
    /* Removed Linux simulation code and kept only Windows simulation code */
    srand(GetCurrentThreadId());

    for (;;) {

        OSSemPend(RandomSem, 0, &err);           /* Acquire semaphore to perform random numbers        */
        x = rand() % 78;                         /* Find X position where task number will appear      */
        y = rand() % 15;                         /* Find Y position where task number will appear      */
        OSSemPost(RandomSem);                    /* Release semaphore                                  */

                                                 /* Display the task number on the screen              */
        /* @Feb 17th, 2010 By: Amr Ali Abdel-Naby */
        /* Changed the PC_DispChar to PC_DispStr to make the example work on Vista */
        sprintf(s, "%1c", *((char *)pdata));
        PC_DispStr(x,(INT8U)(y+5),s , DISP_FGND_BLACK + DISP_BGND_GRAY);
        OSTimeDly(1);                            /* Delay 1 clock tick                                 */


    }
}
/* @May 29th, 2010 By: Amr Ali Abdel-Naby */
/* Added to be triggered by a semaphore through ISRs */

void  TaskInterrupt (void *pdata)
{
    INT8U  x;
    INT8U  y;
    INT8U  err;
    char   s[80];

    srand(GetCurrentThreadId());

    for (;;) {

/*
*********************************************************************************************************
* Wait for ISR to trigger related semaphore
*********************************************************************************************************
*/
// Add your code here!!
        switch( *((char *)pdata) ) {
        case '5': OSSemPend(Sem0, 0, &err); break;
        case '6': OSSemPend(Sem1, 0, &err); break;
        case '7': OSSemPend(Sem2, 0, &err); break;
        case '8': OSSemPend(Sem3, 0, &err); break;
        case '9': OSSemPend(Sem4, 0, &err); break;
        default:
            ;;
        }
// End of your code!!
        OSSemPend(RandomSem, 0, &err);                            /* Acquire semaphore to perform random numbers        */
        x = rand() % 78;                                          /* Find X position where task number will appear      */
        y = rand() % 15;                                          /* Find Y position where task number will appear      */
        OSSemPost(RandomSem);                                     /* Release semaphore                                  */

                                                                  /* Display the task number on the screen              */
        sprintf(s, "%1c", *((char *)pdata));
        PC_DispStr(x,(INT8U)(y+5),s , DISP_FGND_YELLOW + DISP_BGND_BLUE);
        OSTimeDly(1);                            /* Delay 1 clock tick                                 */


    }
}

/* @May 29th, 2010 By: Amr Ali Abdel-Naby */
/* Added ISRS that will trigger interrupt driven tasks */
/*
*********************************************************************************************************
*                                                   ISRS
*********************************************************************************************************
*/
void ISR0 (void)
{
/*
*********************************************************************************************************
* Trigger related semaphore
*********************************************************************************************************
*/
// Add your code here!!
    OSSemPost(Sem0);
// End of your code!!
}
void ISR1 (void)
{
/*
*********************************************************************************************************
* Trigger related semaphore
*********************************************************************************************************
*/
// Add your code here!!
    OSSemPost(Sem1);
// End of your code!!
}
void ISR2 (void)
{
/*
*********************************************************************************************************
* Trigger related semaphore
*********************************************************************************************************
*/
// Add your code here!!
    OSSemPost(Sem2);
// End of your code!!
}
void ISR3 (void)
{
/*
*********************************************************************************************************
* Trigger related semaphore
*********************************************************************************************************
*/
// Add your code here!!
    OSSemPost(Sem3);
// End of your code!!
}
void ISR4 (void)
{
/*
*********************************************************************************************************
* Trigger related semaphore
*********************************************************************************************************
*/
// Add your code here!!
    OSSemPost(Sem4);
// End of your code!!
}

