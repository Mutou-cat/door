#include "User_MenuTask.h"
#include "User_TasksInit.h"
#include "menu.h"
#include "main.h"
#include "key.h"

/*typedef struct MenuItem {
    const char *name;                     
    struct MenuItem *parent;              
    struct MenuItem *children[MAX_CHILDREN]; 
    uint8_t childCount;                   
    void (*action)(void);                 
};*/

extern osMessageQueueId_t Key_MessageQueue;
extern osMessageQueueId_t Display_MessageQueue;
void addFingerAction()
{
    
}
void delFingerAction()
{
    
}
void addCardAction()
{
    
}
void delCardAction()
{
    
}


struct  MenuItem welcomePage = {"     Welcome    ", NULL, {NULL}, 0, NULL};

struct  MenuItem mainMenu   = { "    Main Menu   ", &welcomePage, {NULL}, 0, NULL };

struct  MenuItem fingerMenu = { "Fingerprint", &mainMenu, {NULL}, 0, NULL };
struct  MenuItem cardMenu   = { "Card", &mainMenu, {NULL}, 0, NULL };
struct  MenuItem systemMenu   = { "ResetSystem", &mainMenu, {NULL}, 0, NULL };

struct  MenuItem addFinger  = { "Add Finger", &fingerMenu, {NULL}, 0, addFingerAction };
struct  MenuItem delFinger  = { "Del Finger", &fingerMenu, {NULL}, 0, delFingerAction };

struct  MenuItem addCard    = { "Add Card", &cardMenu, {NULL}, 0, addCardAction };
struct  MenuItem delCard    = { "Del Card", &cardMenu, {NULL}, 0, delCardAction };

// 初始化菜单结构
void initMenu() {
    // 欢迎页面下挂主菜单
    welcomePage.children[welcomePage.childCount++] = &mainMenu;
    // 主菜单下挂 Fingerprint 和 Card
    mainMenu.children[mainMenu.childCount++] = &fingerMenu;
    mainMenu.children[mainMenu.childCount++] = &cardMenu;
    mainMenu.children[mainMenu.childCount++]=&systemMenu;

    // 指纹子菜单
    fingerMenu.children[fingerMenu.childCount++] = &addFinger;
    fingerMenu.children[fingerMenu.childCount++] = &delFinger;

    // 卡片子菜单
    cardMenu.children[cardMenu.childCount++] = &addCard;
    cardMenu.children[cardMenu.childCount++] = &delCard;
}

struct MenuItem *currentPage = &welcomePage;
uint8_t currentIndex = 0;  // 当前子菜单索引
uint8_t lastIndex = 0;  // 上一次子菜单索引


void menuNext() {
    if (currentPage->childCount > 0) {
        currentIndex = (currentIndex + 1) % currentPage->childCount;
    }
}

void menuPrev() {
    if (currentPage->childCount > 0) {
        currentIndex = (currentIndex + currentPage->childCount - 1) % currentPage->childCount;
    }
}

void menuEnter() {
    if (currentPage->childCount > 0) {
        currentPage = currentPage->children[currentIndex];
        lastIndex = currentIndex;
        currentIndex = 0;

    } else if (currentPage->action) {
        currentPage->action();
    }
}

void menuBack() {
    if (currentPage->parent) {
        currentPage = currentPage->parent;
        currentIndex = lastIndex;
    }
}



void MenuTask(void *argument)
{
    initMenu();
    DisplayMsg oledmsg;
    oledmsg.cmd = DISP_SHOW_MENU;
    while(1)
    {
        uint8_t keystr=0;
        uint8_t oledstr=0;
        if(osMessageQueueGet(Key_MessageQueue,&keystr,NULL,0)==osOK)
        {
            switch(keystr)
            {
                case KEY_UP: // Up
                    menuPrev();
                    break;
                case KEY_DOWN: // Down
                    menuNext();
                    break;
                case KEY_ENTER: // Enter
                    menuEnter();
                    break;
                case KEY_BACK: // Back
                    menuBack();
                    break;
            }
            osMessageQueuePut(Display_MessageQueue, &oledmsg, 0, 1);
            
        }
        osDelay(20);
    }
}