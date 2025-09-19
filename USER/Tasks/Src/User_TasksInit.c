/* Private includes -----------------------------------------------------------*/
// includes
#include "user_TasksInit.h"
// sys
#include "sys.h"
#include "stdio.h"

// tasks

#include "User_KeyTask.h"
#include "User_MenuTask.h"
#include "User_DisplayTask.h"
#include "User_CardCheckTask.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Timers --------------------------------------------------------------------*/

/* Tasks ---------------------------------------------------------------------*/

// Key task
osThreadId_t KeyTaskHandle;
const osThreadAttr_t KeyTask_attributes = {
    .name = "KeyTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityAboveNormal,
};

osThreadId_t MenuTaskHandle;
const osThreadAttr_t MenuTask_attributes = {
    .name = "MenuTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};

osThreadId_t DisplayTaskHandle;
const osThreadAttr_t DisplayTask_attributes = {
    .name = "DisplayTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};

osThreadId_t CardCheckTaskHandle;
const osThreadAttr_t CardCheckTask_attributes = {
    .name = "CardCheckTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityAboveNormal,
};

/* Message queues ------------------------------------------------------------*/
// Key message
osMessageQueueId_t Key_MessageQueue;
osMessageQueueId_t Display_MessageQueue;

void User_Tasks_Init(void)
{
  /* add mutexes, ... */

  /* add semaphores, ... */

  /* start timers, add new ones, ... */

  /* add queues, ... */
  Key_MessageQueue = osMessageQueueNew(1, 1, NULL);
  Display_MessageQueue = osMessageQueueNew(2, sizeof(DisplayMsg), NULL);

  /* add threads, ... */
  KeyTaskHandle = osThreadNew(KeyTask, NULL, &KeyTask_attributes);
  MenuTaskHandle = osThreadNew(MenuTask, NULL, &MenuTask_attributes);
  DisplayTaskHandle = osThreadNew(DisplayTask, NULL, &DisplayTask_attributes);
  CardCheckTaskHandle = osThreadNew(CardCheckTask, NULL, &CardCheckTask_attributes);
  /* add events, ... */

  /* add  others ... */
}
