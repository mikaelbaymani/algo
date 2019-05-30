/*
*********************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                                       WIN32 PORT & LINUX PORT
*                          (c) Copyright 2004, Werner.Zimmermann@fht-esslingen.de
*                 (Similar to Example 1 of the 80x86 Real Mode port by Jean J. Labrosse)
*                                           All Rights Reserved
*
*                                               EXAMPLE #1
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

/*
*********************************************************************************************************
*                                               VARIABLES
*********************************************************************************************************
*/
/*




*********************************************************************************************************
* Define stack for the 10 tasks and for the TaskStart task
*********************************************************************************************************
*/
// Add your code here!!
OS_STK Task0Stack[TASK_STK_SIZE];
OS_STK Task1Stack[TASK_STK_SIZE];
OS_STK Task2Stack[TASK_STK_SIZE];
OS_STK Task3Stack[TASK_STK_SIZE];
OS_STK Task4Stack[TASK_STK_SIZE];
OS_STK Task5Stack[TASK_STK_SIZE];
OS_STK Task6Stack[TASK_STK_SIZE];
OS_STK Task7Stack[TASK_STK_SIZE];
OS_STK Task8Stack[TASK_STK_SIZE];
OS_STK Task9Stack[TASK_STK_SIZE];
OS_STK TaskStartStack[TASK_STK_SIZE];
// End of your code!!
char          TaskData[N_TASKS];                      /* Parameters to pass to each task               */
OS_EVENT     *RandomSem;


/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

        void  Task(void *data);                       /* Function prototypes of tasks                  */
        void  TaskStart(void *data);                  /* Function prototypes of Startup task           */
static  void  TaskStartCreateTasks(void);
static  void  TaskStartDispInit(void);
static  void  TaskStartDisp(void);

/*$PAGE*/
/*
*********************************************************************************************************
*                                                MAIN
*********************************************************************************************************
*/

int  main (void)
{
    INT8U err;
/*
*********************************************************************************************************
* Initialize uCOS-II
*********************************************************************************************************
*/

// Add your code here!!
    OSInit();
// End of your code!!

    RandomSem   = OSSemCreate(1);                          /* Random number semaphore                  */
    PC_DispClrScr(DISP_FGND_WHITE + DISP_BGND_BLACK);      /* Clear the screen                         */

/*
*********************************************************************************************************
* Create the first task then start multitasking
*********************************************************************************************************
*/
// Add your code here!!
    OSTaskCreate(TaskStart,
                 NULL,
                 &TaskStartStack[TASK_STK_SIZE-1],
                 10);
    OSStart();
// End of your code!!
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

/*
*********************************************************************************************************
* Create the 10 tasks
*********************************************************************************************************
*/

    TaskStartCreateTasks();                                /* Create all the application tasks         */

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
/*
*********************************************************************************************************
* Wait one second
*********************************************************************************************************
*/
// Add your code here!!
    OSTimeDlyHMSM(0,  // hours
                  0,  // minutes
                  1,  // seconds
                  0); // milli
// End of your code!!
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
    PC_DispStr( 0,  3, "                                    EXAMPLE #1                                  ", DISP_FGND_BLACK + DISP_BGND_WHITE);
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
    TaskData[0] = '0', OSTaskCreate(Task, &TaskData[0], &Task0Stack[TASK_STK_SIZE-1], 0);
    TaskData[1] = '1', OSTaskCreate(Task, &TaskData[1], &Task1Stack[TASK_STK_SIZE-1], 1);
    TaskData[2] = '2', OSTaskCreate(Task, &TaskData[2], &Task2Stack[TASK_STK_SIZE-1], 2);
    TaskData[3] = '3', OSTaskCreate(Task, &TaskData[3], &Task3Stack[TASK_STK_SIZE-1], 3);
    TaskData[4] = '4', OSTaskCreate(Task, &TaskData[4], &Task4Stack[TASK_STK_SIZE-1], 4);
    TaskData[5] = '5', OSTaskCreate(Task, &TaskData[5], &Task5Stack[TASK_STK_SIZE-1], 5);
    TaskData[6] = '6', OSTaskCreate(Task, &TaskData[6], &Task6Stack[TASK_STK_SIZE-1], 6);
    TaskData[7] = '7', OSTaskCreate(Task, &TaskData[7], &Task7Stack[TASK_STK_SIZE-1], 7);
    TaskData[8] = '8', OSTaskCreate(Task, &TaskData[8], &Task8Stack[TASK_STK_SIZE-1], 8);
    TaskData[9] = '9', OSTaskCreate(Task, &TaskData[9], &Task9Stack[TASK_STK_SIZE-1], 9);
// End of your code!!
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
/*
*********************************************************************************************************
* Delay 1 clock tick
*********************************************************************************************************
*/
// Add your code here!!
    OSTimeDly(1);
// End of your code!!

    }
}
