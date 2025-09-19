#ifndef __MENU_H__
#define __MENU_H__

#include <stdint.h>

#define MAX_CHILDREN 8   

typedef struct MenuItem {
    char *name;                     
    struct MenuItem *parent;              
    struct MenuItem *children[MAX_CHILDREN]; 
    uint8_t childCount;                   
    void (*action)(void);                 
};
#endif // MENU_H


