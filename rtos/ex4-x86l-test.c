/*
   *********************************************************************************************************
   *                                                uC/OS-II
   *                                          The Real-Time Kernel
   *
   *                 (Measuring Execution Time of Application Tasks using uC/OS-II Timers)
   *                                           All Rights Reserved
   *
   *                                               EXAMPLE #4
   *********************************************************************************************************
 */
#define _CRT_SECURE_NO_WARNINGS
#include "includes.h"

/*
   *********************************************************************************************************
   *                                              CONSTANTS
   *********************************************************************************************************
 */

#define          TASK_STK_SIZE       1024                          // Size of each task's stacks (# of WORDs)

#define          TASK_START_PRIO    10                             // Application tasks priorities
#define          TASK_SPEEDY_PRIO   11
#define          TASK_SLOW_PRIO     12


/*
   *********************************************************************************************************
   *                                              VARIABLES
   *********************************************************************************************************
 */

OS_STK TaskStartStk[TASK_STK_SIZE];                             // Startup    task stack
OS_STK TaskSpeedyStk[TASK_STK_SIZE];                            // Speedy     task stack
OS_STK TaskSlowStk[TASK_STK_SIZE];                              // Slow       task stack
OS_FLAG_GRP * EventGrp;                                         // Event Flags Group
OS_TMR * StatTmr;                                               // Timer to calculate and print statistics

INT32U SpeedyTaskCntr = 0;                                      // Speedy task cycles counter
INT32U TotalSpeedyTaskTime = 0;                                 // Total speedy task execution time

INT32U SlowTaskCntr = 0;                                        // Slow task cycles counter
INT32U TotalSlowTaskTime = 0;                                   // Total slow task execution time

#define SlowFlags       0X0F                                    // Slow task flags
#define SpeedyFlags     0XF0                                    // Speedy task flags


/*
   *********************************************************************************************************
   *                                         FUNCTION PROTOTYPES
   *********************************************************************************************************
 */

void TaskStart(void *data);                                     // Function prototypes of tasks
static void TaskStartCreateTasks(void);
static void TaskStartDispInit(void);
static void TaskStartDisp(void);
void TaskSpeedy(void *data);
void TaskSlow(void *data);
void StatTmrFnct (void *ptmr, void *callback_arg);
/*$PAGE*/
/*
   *********************************************************************************************************
   *                                                  MAIN
   *********************************************************************************************************
 */

int main(void)
{   OS_STK *ptos;

    PC_DispClrScr(DISP_FGND_WHITE);                             // Clear the screen

    OSInit();                                                   // Initialize uC/OS-II

    ptos = &TaskStartStk[TASK_STK_SIZE - 1];                    // TaskStart() will use Floating-Point
    /* @Feb 17th, 2010 By: Amr Ali Abdel-Naby */
    /* Removed a commented line */
    OSTaskCreate(TaskStart,
                    (void *) 0,
                    ptos,
                    TASK_START_PRIO);

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
    INT8U err;
    OS_FLAGS status;


    pdata = pdata;                                                 // Prevent compiler warning

    TaskStartDispInit();                                           // Setup the display
#if OS_TASK_STAT_EN > 0
    OSStatInit();                                                  // Initialize uC/OS-II's statistics
#endif
    TaskStartCreateTasks();                                        // Create all other tasks
/*
*********************************************************************************************************
* Create the flag group with zero initialized flags then set the slow task flags
*********************************************************************************************************
*/
// Add your code here!!
    EventGrp   = OSFlagCreate(0, &err);
    status     = OSFlagPost(EventGrp, SlowFlags, OS_FLAG_SET, &err);
// End of your code!!

/*
*********************************************************************************************************
* Create the timer with delay 10 and period 100, then start it
*********************************************************************************************************
*/
// Add your code here!!
    StatTmr   = OSTmrCreate(10, 100, OS_TMR_OPT_PERIODIC, StatTmrFnct, NULL, "StatTmr", &err);
    (void)OSTmrStart(StatTmr, &err);
// End of your code!!

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
    PC_DispStr(0, 3, "                                    EXAMPLE #4                                  ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 4, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 5, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 6, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 7, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 8, "                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 9, "Task           Counter       Average Time                                       ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 10,"-------------  -----------   ----------------                                   ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 11,"                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 12,"                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 13,"TaskSpeedy()  :                                                                 ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 14,"                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 15,"                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 16,"TaskSlow()    :                                                                 ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 17,"                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 18,"                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 19,"                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 20,"                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 21,"                                                                                ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 22,"#Tasks          :        CPU Usage:     %                                       ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 23,"#Task switch/sec:                                                               ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
    PC_DispStr(0, 24,"                            <-PRESS 'ESC' TO QUIT->                             ", DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
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
{
        OSTaskCreate(TaskSpeedy,                                // Create the Speedy task
                    (void *) 0,
                    &TaskSpeedyStk[TASK_STK_SIZE-1],
                    TASK_SPEEDY_PRIO);

        OSTaskCreate(TaskSlow,                                  // Create the Slow task
                    (void *) 0,
                    &TaskSlowStk[TASK_STK_SIZE-1],
                    TASK_SLOW_PRIO);


}

/*$PAGE*/
/*
   *********************************************************************************************************
   *                                               TASK Speedy
   *********************************************************************************************************
 */
void TaskSpeedy(void *pdata){
   OS_FLAGS  status;
   INT32U    start_time, cycle_time, current_time;
   INT8U err;

   pdata = pdata;

   for(;;)
   {

      start_time = OSTimeGet();                                                   // Get the starting time for this cycle


      OSTimeDly(2);                                                               // Delay for 2 ticks

/*
*********************************************************************************************************
* Wait for the speedy task flags to be set then clear them
*********************************************************************************************************
*/
// Add your code here!!
        status   = OSFlagPend(EventGrp, SpeedyFlags, OS_FLAG_WAIT_SET_ALL, 0, &err);
        OSFlagPost(EventGrp, SpeedyFlags, OS_FLAG_CLR, &err);
// End of your code!!

      OSTimeDly(5);                                                               // Delay for 5 ticks


/*
*********************************************************************************************************
* Set the slow task flags
*********************************************************************************************************
*/
// Add your code here!!
        OSFlagPost(EventGrp, SlowFlags, OS_FLAG_SET, &err);
// End of your code!!


       SpeedyTaskCntr++;                                                          // Increment the speedy task counter

       current_time = OSTimeGet();                                                // Get the finishing time for this cycle
       cycle_time = current_time - start_time;                                    // Calculate the cycle time
       TotalSpeedyTaskTime += cycle_time;                                         // Increment the speedy task total time

   }
}

/*$PAGE*/

/*
   *********************************************************************************************************
   *                                               TASK Slow
   *********************************************************************************************************
 */
void    TaskSlow(void * pdata)
{
   OS_FLAGS  status;
   INT32U    start_time, cycle_time, current_time;
   INT8U err;


   for(;;)
   {

      start_time = OSTimeGet();                                                   // Get the starting time for this cycle

/*
*********************************************************************************************************
* Wait for the slow task flags to be set then clear them
*********************************************************************************************************
*/
// Add your code here!!
        status   = OSFlagPend(EventGrp, SlowFlags, OS_FLAG_WAIT_SET_ALL, 0, &err);
        OSFlagPost(EventGrp, SlowFlags, OS_FLAG_CLR, &err);

// End of your code!!

      OSTimeDly(12);                                                              // Delay for 12 ticks


/*
*********************************************************************************************************
* Set the speedy task flags
*********************************************************************************************************
*/
// Add your code here!!
      OSFlagPost(EventGrp, SpeedyFlags, OS_FLAG_SET, &err);
// End of your code!!


      /* Increment the thread counter and get timing info  */
      SlowTaskCntr++;


      current_time = OSTimeGet();                                                // Get the finishing time for this cycle
      cycle_time = current_time - start_time;                                    // Calculate the cycle time
      TotalSlowTaskTime += cycle_time;                                           // Increment the slow task total time

   }
}
/*$PAGE*/
/*
   *********************************************************************************************************
   *                                               StatTmrFnct
   * Description: Timer Callback Function
   *********************************************************************************************************
 */
void StatTmrFnct (void *ptmr, void *callback_arg){

        INT32U   current_time;
        INT32U   avg_slow_time;
        INT32U   avg_speedy_time;
        char s[80];

        ptmr = ptmr;
        callback_arg = callback_arg;

       if ((SpeedyTaskCntr>0) && (SlowTaskCntr>0)){
                avg_slow_time = TotalSlowTaskTime / SlowTaskCntr;
                avg_speedy_time = TotalSpeedyTaskTime / SpeedyTaskCntr;
                sprintf(s,"%10d  %10d", SpeedyTaskCntr, avg_speedy_time);
                PC_DispStr(16, 13,s, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
                sprintf(s,"%10d  %10d", SlowTaskCntr, avg_slow_time);
                PC_DispStr(16, 16,s, DISP_FGND_BLACK + DISP_BGND_LIGHT_GRAY);
        }
}
