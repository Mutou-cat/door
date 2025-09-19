#include "User_CardCheckTask.h"
#include "User_TasksInit.h"
#include "RC522.h"
#include "servo.h"


uint8_t UID[4],Temp[4];//临时变量，前者储存卡数据，后者储存卡类别
uint8_t UI1[4]={0xFF,0xFF,0xFF,0xFF};		 	//卡1ID号
uint8_t UI2[4]={0xFF,0xFF,0xFF,0xFF};	 		//卡2ID号
uint8_t UI3[4]={0xFF,0xFF,0xFF,0xFF};			//卡3ID号
uint8_t UI4[4]={0xFF,0xFF,0xFF,0xFF};			//卡4ID号


DisplayMsg oledmsg;


extern osMessageQueueId_t Display_MessageQueue;


void RC522_Check()
{
   
    uint8_t cardno;
   
    if (PcdRequest(REQ_ALL, Temp) == MI_OK)
	{
       
		if (PcdAnticoll(UID) == MI_OK)
		{
			cardno=0;	
			if(UID[0]==UI1[0]&&UID[1]==UI1[1]&&UID[2]==UI1[2]&&UID[3]==UI1[3])
			{
				cardno=1;
			}
			else if(UID[0]==UI2[0]&&UID[1]==UI2[1]&&UID[2]==UI2[2]&&UID[3]==UI2[3])
			{
				cardno=2;
			}
			else if(UID[0]==UI2[0]&&UID[1]==UI2[1]&&UID[2]==UI2[2]&&UID[3]==UI2[3])
			{
				cardno=3;
			}
			else if(UID[0]==UI4[0]&&UID[1]==UI4[1]&&UID[2]==UI4[2]&&UID[3]==UI4[3])
			{
				cardno=4;
			}			
		
		}

	}

	if(cardno == 0)			//如果为0，表示“卡片错误”，系统中没有这张卡
	{

		Servo_SetAngle(90); // 设置舵机角度为90度，打开门
		oledmsg.cmd=DISP_SHOW_MESSAGE;
       	strcpy(oledmsg.message, "Card Error!");
        oledmsg.duration = 1200; // 显示1.2秒
        osMessageQueuePut(Display_MessageQueue, &oledmsg, 0, 1);
		osDelay(1200);
		WaitCardOff();		//等待卡片移
		oledmsg.cmd=DISP_SHOW_MENU;
		osMessageQueuePut(Display_MessageQueue, &oledmsg, 0, 1);
		Servo_SetAngle(0); // 设置舵机角度为90度，打开门

	}
	else if(cardno==1||cardno==2||cardno==3||cardno == 4)	//如果卡编号为1-4，说明是系统中的4张卡
	{	
		oledmsg.cmd=DISP_SHOW_MESSAGE;
		sprintf(oledmsg.message,"Card: %d",cardno);
        oledmsg.duration = 1200; // 显示1.2秒
        osMessageQueuePut(Display_MessageQueue, &oledmsg, 0, 1);
		WaitCardOff();		//等待卡片移
		oledmsg.cmd=DISP_SHOW_MENU;
		osMessageQueuePut(Display_MessageQueue, &oledmsg, 0, 1);
		

	}


}

void CardCheckTask(void *argument)
{
    RFID_Init();
	Servo_Init();

    while(1)
    {
        RC522_Check();
        osDelay(100);
    }
}