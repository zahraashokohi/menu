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
    char *String;
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
    char *title;
    Data_Types data_type;
    _Cmd_Type cmd_type;

}Parameters_Type;

typedef struct
{

    char                stringData[500];
    void                (*function)(char *input, char *message);
    char*                stringIndex;
    uint8_t             nextMenu;
    Parameters_Type     Data_Type;
    void*               Data;
} submenu_t;

typedef struct
{

    char menutitle[300];
    submenu_t *menus;
    uint8_t sizeMenu;
    char footerMenu[200];
} menu_t;
typedef enum
{
    MENU_NONE,
    MENU_MAIN,
    MENU_1,
    MENU_2,
    MENU_3,
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
    char Message[500];
} _Menu_Action;

extern _Menu_Action Menu_Action;




#ifdef __cplusplus
};
#endif

#endif // _MENU_HANDLER_H_
