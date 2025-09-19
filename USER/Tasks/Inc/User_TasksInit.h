#ifndef __USER_TASKSINIT_H__
#define __USER_TASKSINIT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include "cmsis_os.h"

#define SCRRENEW_DEPTH	5

typedef enum {
    DISP_SHOW_MENU,
    DISP_SHOW_MESSAGE
} DisplayCmd;

typedef struct {
    DisplayCmd cmd;      
    char message[32];    // 显示的字符串
    uint32_t duration;   // 显示持续时间（ms），仅对 MESSAGE 有效
} DisplayMsg;

extern osMessageQueueId_t Key_MessageQueue;
extern osMessageQueueId_t Idle_MessageQueue;
extern osMessageQueueId_t Stop_MessageQueue;
extern osMessageQueueId_t IdleBreak_MessageQueue;
extern osMessageQueueId_t HomeUpdata_MessageQueue;
extern osMessageQueueId_t DataSave_MessageQueue;

void User_Tasks_Init(void);
void TaskTickHook(void);

#ifdef __cplusplus
}
#endif

#endif

