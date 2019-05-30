/*
   *********************************************************************************************************
   *                                                uC/OS-II
   *                                          The Real-Time Kernel
   *
*                                       WIN32 PORT & LINUX PORT
   *                          (c) Copyright 2004, Werner.Zimmermann@fht-esslingen.de
   *                 (Similar to Example 3 of the 80x86 Real Mode port by Jean J. Labrosse)
   *                                           All Rights Reserved
   *
   *                                               EXAMPLE #3
   *********************************************************************************************************
 */
#define _CRT_SECURE_NO_WARNINGS
#include "includes.h"

/*
   *********************************************************************************************************
   *                                              CONSTANTS
   *********************************************************************************************************
 */

#define          TASK_STK_SIZE     512                          // Size of each task's stacks (# of WORDs)

#define          TASK_START_ID       0                          // Application tasks IDs
#define          TASK_CLK_ID         1
#define          TASK_1_ID           2
#define          TASK_2_ID           3
#define          TASK_3_ID           4
#define          TASK_4_ID           5
#define          TASK_5_ID           6

#define          TASK_START_PRIO    10                          // Application tasks priorities
#define          TASK_CLK_PRIO      11
#define          TASK_1_PRIO        12
#define          TASK_2_PRIO        13
#define          TASK_3_PRIO        14
#define          TASK_4_PRIO        15
#define          TASK_5_PRIO        16

/*
   *********************************************************************************************************
   *                                              VARIABLES
   *********************************************************************************************************
 */

OS_STK TaskStartStk[TASK_STK_SIZE];                             // Startup    task stack
OS_STK TaskClkStk[TASK_STK_SIZE];                               // Clock      task stack
OS_STK Task1Stk[TASK_STK_SIZE];                                 // Task #1    task stack
OS_STK Task2Stk[TASK_STK_SIZE];                                 // Task #2    task stack
OS_STK Task3Stk[TASK_STK_SIZE];                                 // Task #3    task stack
OS_STK Task4Stk[TASK_STK_SIZE];                                 // Task #4    task stack
OS_STK Task5Stk[TASK_STK_SIZE];                                 // Task #5    task stack

/*
 *********************************************************************************************************
 * Define pointers for the mailboxes
 *********************************************************************************************************
 */
// Add your code here!!
OS_EVENT   *MboxChar;
OS_EVENT   *MboxAck;
// End of your code!!

/*
   *********************************************************************************************************
   *                                         FUNCTION PROTOTYPES
   *********************************************************************************************************
 */

void TaskStart(void *data);                                     // Function prototypes of tasks
static void TaskStartCreateTasks(void);
static void TaskStartDispInit(void);
static void TaskStartDisp(void);
void TaskClk(void *data);
void Task1(void *data);
void Task2(void *data);
void Task3(void *data);
void Task4(void *data);
void Task5(void *data);

/*$PAGE*/
/*
   *********************************************************************************************************
   *                                                  MAIN
   *********************************************************************************************************
 */

int main(void)
{   OS_STK *ptos;
    OS_STK *pbos;
    INT32U size;


    PC_DispClrScr(DISP_FGND_WHITE);                             // Clear the screen
    PC_ElapsedInit();                                           // Initialized elapsed time measurement

    OSInit();                                                   // Initialize uC/OS-II

    ptos = &TaskStartStk[TASK_STK_SIZE - 1];                    // TaskStart() will use Floating-Point
    pbos = &TaskStartStk[0];
    size = TASK_STK_SIZE;
    /* @Feb 17th, 2010 By: Amr Ali Abdel-Naby */
    /* Removed a commented line */
    OSTaskCreateExt(TaskStart,
                    (void *) 0,
                    ptos,
                    TASK_START_PRIO,
                    TASK_START_ID,
                    pbos,
                    size,
                    (void *) 0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

    OSStart();                                                  // Start multitasking

    return 0;
}
/*$PAGE*/
/*
   *********************************************************************************************************
   *                                               STARTUP TASK
   *********************************************************************************************************
 */

void TaskStart(void *pdata)
{
    INT16S key;


    pdata = pdata;                                              // Prevent compiler warning

    TaskStartDispInit();                                        // Setup the display
#if OS_TASK_STAT_EN > 0
    OSStatInit();                                               // Initialize uC/OS-II's statistics
#endif
/*
 *********************************************************************************************************
 * Create the mailboxes
 *********************************************************************************************************
 */
// Add your code here!!
    MboxChar   = OSMboxCreate(NULL);
    MboxAck    = OSMboxCreate(NULL);
// End of your code!!
    TaskStartCreateTasks();                                     // Create all other tasks

    for (;;)
    {   TaskStartDisp();                                        // Update the display

        if (PC_GetKey(&key))
        {                                                       // See if key has been pressed
            if (key == 0x1B)
            {                                                   // Yes, see if it's the ESCAPE key
                exit(0);                                        // Yes, return to DOS
            }
        }
        OSCtxSwCtr = 0;                                         // Clear context switch counter
        OSTimeDly(OS_TICKS_PER_SEC);                            // Wait one second
    }
}
/*$PAGE*/
/*
   *********************************************************************************************************
   *                                        INITIALIZE THE DISPLAY
   *********************************************************************************************************
 */

static void TaskStartDispInit(void)
{
//                                1111111111222222222233333333334444444444555555555566666666667777777777
//                      01234567890123456789012345678901234567890123456789012345678901234567890123456789
    PC_DispStr(0, 0, "                         uC/OS-II, The Real-Time Kernel                         ", DISP_FGND_WHITE + DISP_BGND_RED);
    /* @Feb 17th, 2010 By: Amr Ali Abdel-Naby */
    /* Removed Linux simulation code and kept only Windows simulation code and Added my Integration Message */
    PC_DispStr(0, 1, "   Original version by Jean J. Labrosse, PC Utility port by Werner Zimmermann   ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 2, "                    Integration on Vista by Amr A. Abdel-Naby                   ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 3, "                                    EXAMPLE #3                                  ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 4, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 5, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 6, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 7, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 8, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 9, "Task           Total Stack  Free Stack  Used Stack  ExecTime (uS)               ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 10,"-------------  -----------  ----------  ----------  -------------               ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 11, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 12, "TaskStart():                                                                    ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 13, "TaskClk()  :                                                                    ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 14, "Task1()    :                                                                    ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 15, "Task2()    :                                                                    ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 16, "Task3()    :                                                                    ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 17, "Task4()    :                                                                    ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 18, "Task5()    :                                                                    ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 19, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 20, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 21, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 22, "#Tasks          :        CPU Usage:     %                                       ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 23, "#Task switch/sec:                                                               ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 24, "                            <-PRESS 'ESC' TO QUIT->                             ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
//                                1111111111222222222233333333334444444444555555555566666666667777777777
//                      01234567890123456789012345678901234567890123456789012345678901234567890123456789
}

/*$PAGE*/
/*
   *********************************************************************************************************
   *                                           UPDATE THE DISPLAY
   *********************************************************************************************************
 */

static void TaskStartDisp(void)
{   char s[80];


    sprintf(s, "%5d", OSTaskCtr);                               // Display #tasks running
    PC_DispStr(18, 22, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);
#if OS_TASK_STAT_EN > 0
    sprintf(s, "%3d", OSCPUUsage);                              // Display CPU usage in %
    PC_DispStr(36, 22, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);
#endif
    sprintf(s, "%5d", OSCtxSwCtr);                              // Display #context switches per second
    PC_DispStr(18, 23, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);

    /* @Feb 17th, 2010 By: Amr Ali Abdel-Naby */
    /* Removed Linux simulation code, kept only Windows simulation code, and modified the version code to map to V2.86 */
    sprintf(s, "uCOS-II V%1d.%02d", OSVersion() / 100, OSVersion() % 100); /* Display uC/OS-II's version number    */
    PC_DispStr(54, 23, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);
}

/*$PAGE*/
/*
   *********************************************************************************************************
   *                                             CREATE TASKS
   *********************************************************************************************************
 */

static void TaskStartCreateTasks(void)
{   OSTaskCreateExt(TaskClk,
                    (void *) 0,
                    &TaskClkStk[TASK_STK_SIZE - 1],
                    TASK_CLK_PRIO,
                    TASK_CLK_ID,
                    &TaskClkStk[0],
                    TASK_STK_SIZE,
                    (void *) 0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

    OSTaskCreateExt(Task1,
                    (void *) 0,
                    &Task1Stk[TASK_STK_SIZE - 1],
                    TASK_1_PRIO,
                    TASK_1_ID,
                    &Task1Stk[0],
                    TASK_STK_SIZE,
                    (void *) 0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

    OSTaskCreateExt(Task2,
                    (void *) 0,
                    &Task2Stk[TASK_STK_SIZE - 1],
                    TASK_2_PRIO,
                    TASK_2_ID,
                    &Task2Stk[0],
                    TASK_STK_SIZE,
                    (void *) 0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

    OSTaskCreateExt(Task3,
                    (void *) 0,
                    &Task3Stk[TASK_STK_SIZE - 1],
                    TASK_3_PRIO,
                    TASK_3_ID,
                    &Task3Stk[0],
                    TASK_STK_SIZE,
                    (void *) 0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

    OSTaskCreateExt(Task4,
                    (void *) 0,
                    &Task4Stk[TASK_STK_SIZE - 1],
                    TASK_4_PRIO,
                    TASK_4_ID,
                    &Task4Stk[0],
                    TASK_STK_SIZE,
                    (void *) 0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

    OSTaskCreateExt(Task5,
                    (void *) 0,
                    &Task5Stk[TASK_STK_SIZE - 1],
                    TASK_5_PRIO,
                    TASK_5_ID,
                    &Task5Stk[0],
                    TASK_STK_SIZE,
                    (void *) 0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
}

/*$PAGE*/
/*
   *********************************************************************************************************
   *                                               TASK #1
   *
   * Description: This task executes every 100 mS and measures the time it task to perform stack checking
   *              for each of the 5 application tasks.  Also, this task displays the statistics related to
   *              each task's stack usage.
   *********************************************************************************************************
 */

void Task1(void *pdata)
{   INT8U err;
    OS_STK_DATA data;                                           // Storage for task stack data
    INT32U time;                                                // Execution time (in uS)
    INT8U i;
    char s[80];


    pdata = pdata;
    for (;;)
    {   for (i = 0; i < 7; i++)
        {   PC_ElapsedStart(0);
            err = OSTaskStkChk((INT8U) (TASK_START_PRIO + i), &data);
            time = PC_ElapsedStop(0);
            if (err == OS_ERR_NONE)
            {   sprintf(s, "%4ld        %4ld        %4ld        %6d",
                        data.OSFree + data.OSUsed,
                        data.OSFree,
                        data.OSUsed,
                        time);
                PC_DispStr(19, (INT8U) (12 + i), s, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
            }
        }
        OSTimeDlyHMSM(0, 0, 0, 100);                            // Delay for 100 mS
    }
}
/*$PAGE*/
/*
   *********************************************************************************************************
   *                                               TASK #2
   *
   * Description: This task displays a clockwise rotating wheel on the screen.
   *********************************************************************************************************
 */

void Task2(void *data)
{   data = data;

    /* @Feb 17th, 2010 By: Amr Ali Abdel-Naby */
    /* Changed the PC_DispChar to PC_DispStr to make the example work on Vista */
    for (;;)
    {   PC_DispStr(70, 15, "|", DISP_FGND_YELLOW + DISP_BGND_BLUE);
        OSTimeDly(10);
        PC_DispStr(70, 15, "/", DISP_FGND_YELLOW + DISP_BGND_BLUE);
        OSTimeDly(10);
        PC_DispStr(70, 15, "-", DISP_FGND_YELLOW + DISP_BGND_BLUE);
        OSTimeDly(10);
        PC_DispStr(70, 15, "\\", DISP_FGND_YELLOW + DISP_BGND_BLUE);
        OSTimeDly(10);
    }
}
/*$PAGE*/
/*
   *********************************************************************************************************
   *                                               TASK #3
   *
   * Description: This task displays a counter-clockwise rotating wheel on the screen.
   *
   * Note(s)    : I allocated 500 bytes of storage on the stack to artificially 'eat' up stack space.
   *********************************************************************************************************
 */

void Task3(void *data)
{   char dummy[500];
    INT16U i;


    data = data;
    for (i = 0; i < 499; i++)
    {                                                           // Use up the stack with 'junk'
        dummy[i] = '?';
    }

    /* @Feb 17th, 2010 By: Amr Ali Abdel-Naby */
    /* Changed the PC_DispChar to PC_DispStr to make the example work on Vista */
    for (;;)
    {   PC_DispStr(70, 16, "|", DISP_FGND_YELLOW + DISP_BGND_BLUE);
        OSTimeDly(20);
        PC_DispStr(70, 16, "\\", DISP_FGND_YELLOW + DISP_BGND_BLUE);
        OSTimeDly(20);
        PC_DispStr(70, 16, "-", DISP_FGND_YELLOW + DISP_BGND_BLUE);
        OSTimeDly(20);
        PC_DispStr(70, 16, "/", DISP_FGND_YELLOW + DISP_BGND_BLUE);
        OSTimeDly(20);
    }
}
/*$PAGE*/
/*
   *********************************************************************************************************
   *                                               TASK #4
   *
   * Description: This task sends a message to Task #5.  The message consist of a character that needs to
   *              be displayed by Task #5.  This task then waits for an acknowledgement from Task #5
   *              indicating that the message has been displayed.
   *********************************************************************************************************
 */

void Task4(void *data)
{   char txmsg;
    INT8U err;


    data = data;
    txmsg = 'A';
/*
 *********************************************************************************************************
 * In an infinite loop:
 *      Send a message through the Tx mailbox
 *      Wait for the Ack message from the Ack mailbox
 *      if the message = 'Z', start again from 'A'
 *********************************************************************************************************
 */
// Add your code here!!
    while (1) {
        OSMboxPost(MboxChar, (void *)&txmsg);
        OSMboxPend(MboxAck, 0, &err);
        if (txmsg == 'Z')
            txmsg = 'A';
        else
            txmsg++;
    }
// End of your code!!
}
/*$PAGE*/
/*
   *********************************************************************************************************
   *                                               TASK #5
   *
   * Description: This task displays messages sent by Task #4.  When the message is displayed, Task #5
   *              acknowledges Task #4.
   *********************************************************************************************************
 */

void Task5(void *data)
{   char *rxmsg;
    INT8U err;
    /* @Feb 17th, 2010 By: Amr Ali Abdel-Naby */
    /* Added a string buffer to make the example work on Vista */
    char s[2];

    data = data;
/*
 *********************************************************************************************************
 * In an infinite loop:
 *      Wait for  a message from the Tx mailbox
 *      Display the recieved message on the terminal
 *      Delay yourself for 1 second
 *      Send an Ack message through the Ack mailbox
 * To display the message, use these lines:
 *      sprintf(s,"%1c",rxmsg[0]);
 *      PC_DispStr(70, 18, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);
 *********************************************************************************************************
 */
// Add your code here!!
    while (1) {
        rxmsg = (char *)OSMboxPend(MboxChar, 0, &err);
        sprintf(s,"%1c",rxmsg[0]);
        PC_DispStr(70, 18, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);
        OSTimeDlyHMSM(0,0,1,0);
        OSMboxPost(MboxAck, NULL);
    }
// End of your code!!
}
/*$PAGE*/
/*
   *********************************************************************************************************
   *                                               CLOCK TASK
   *********************************************************************************************************
 */

void TaskClk(void *data)
{   char s[40];


    data = data;
    for (;;)
    {   PC_GetDateTime(s);
        PC_DispStr(60, 22, s, DISP_FGND_YELLOW + DISP_BGND_BLUE);
        OSTimeDly(OS_TICKS_PER_SEC);
    }
}


