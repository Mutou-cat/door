#include "User_TasksInit.h"
#include "oled.h"
#include "menu.h"



extern struct MenuItem *currentPage;
extern uint8_t currentIndex;
extern osMessageQueueId_t Display_MessageQueue;

void DisplayTask(void *argument)
{
    DisplayMsg oledmsg;
    OLED_Init();
    OLED_NewFrame();
    OLED_DrawImage(0,0,&HomePageImg,OLED_COLOR_NORMAL);
    OLED_PrintString(0,0,currentPage->name,&font16x16,OLED_COLOR_NORMAL);
    OLED_ShowFrame();
    while(1)
    {
        if(osMessageQueueGet(Display_MessageQueue,&oledmsg,NULL,0)==osOK)
        {
            OLED_NewFrame();
            switch(oledmsg.cmd)
            {
                case DISP_SHOW_MESSAGE:
                    OLED_PrintString(0,0,oledmsg.message,&font16x16,OLED_COLOR_NORMAL);
                    OLED_ShowFrame();
                    osDelay(oledmsg.duration);
                    break;
                    
                case DISP_SHOW_MENU:
                    if(currentPage->parent!=NULL)
                   { 
                        OLED_PrintString(0,0,currentPage->name,&font16x16,OLED_COLOR_NORMAL);
                        for(int i=0;i<currentPage->childCount;i++)
                        {
                            if(i==currentIndex)
                            {
                                OLED_PrintString(0,16*(i+1),">",&font16x16,OLED_COLOR_NORMAL);
                                OLED_PrintString(16,16*(i+1),currentPage->children[i]->name,&font16x16,OLED_COLOR_REVERSED);
                            }
                            else
                            {
                                OLED_PrintString(16,16*(i+1),currentPage->children[i]->name,&font16x16,OLED_COLOR_NORMAL);
                            }
                            
                        }
                   }
                   else
                   {
                        
                        OLED_DrawImage(0,0,&HomePageImg,OLED_COLOR_NORMAL);
                        OLED_PrintString(0,0,currentPage->name,&font16x16,OLED_COLOR_NORMAL);
                   }
                    break;

            }
        }

        OLED_ShowFrame();
    
        osDelay(1);
    }
}