/* Private includes -----------------------------------------------------------*/
//includes
#include "User_TasksInit.h"
#include "main.h"
#include "key.h"
#include "oled.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/


/**
  * @brief  Key press check task
  * @param  argument: Not used
  * @retval None
  */
void KeyTask(void *argument)
{
  Key_Port_Init();
	while(1)
	{
    uint8_t keystr=0;
    
    switch(KeyScan())
    {
      case 1:
				keystr = 1;
				osMessageQueuePut(Key_MessageQueue, &keystr, 0, 1);
        break;
      case 2:
				keystr = 2;
				osMessageQueuePut(Key_MessageQueue, &keystr, 0, 1);
        break;
      case 3:
				keystr = 3;
				osMessageQueuePut(Key_MessageQueue, &keystr, 0, 1);
        break;
      case 4:
        keystr = 4;
				osMessageQueuePut(Key_MessageQueue, &keystr, 0, 1);
        break;
    }
		osDelay(10);
	}
}
