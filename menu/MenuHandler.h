#ifndef _MENU_HANDLER_H_
#define _MENU_HANDLER_H_


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <conio.h>




typedef struct
{
    char Char;
    uint32_t Int;
    float Float;
    const char* String;
}_New_Data;

typedef enum
{
    _char = 10,
    _int = 11,
    _float = 12,
    _string = 13
}Data_Types;

typedef enum
{
    Change_Params_Cmd = 10,
    Report_Params_Cmd = 11,
    Both_Params_Cmd = 12,
}_Cmd_Type;

typedef struct
{
    const char* title;
    Data_Types data_type;
    _Cmd_Type cmd_type;

}Parameters_Type;

typedef struct
{

    const char*          stringData;
    void                (*function)(char *input, char *message);
    char*                stringIndex;
    uint8_t             nextMenu;
    Parameters_Type     Data_Type;
    void*               Data;
} submenu_t;

typedef struct
{

    const char* menutitle;
    submenu_t *menus;
    uint8_t sizeMenu;
    const char* footerMenu;
} menu_t;

#define MENU_INIT(M, T, F)                              { .menus = M, .sizeMenu = sizeof(M) / sizeof(M[0]), .menutitle = T, .footerMenu = F  }

typedef enum
{
    MENU_NONE,
    MENU_MAIN,
    MENU_Frequencys,
    MENU_One_Frequency,
    MENU_Three_Frequency,
    MENU_4,
    MENU_5,
    MENU_BACK,
} menu_state;

typedef enum
{
    Init_Menu = 0,
    No_Action,
    Refresh_Menu_Items,
    Display_Function_Output,
    Request_Save_Params,
    Answer_Save_Params,
    Report_Params,
    Nothing,
}Menu_Actions;

typedef struct
{
    Menu_Actions State;
    char Message[1000];
} _Menu_Action;

extern _Menu_Action Menu_Action;
extern menu_t allMenus[];

void func (void);

#ifdef __cplusplus
};
#endif

#endif // _MENU_HANDLER_H_
