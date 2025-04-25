#include "MenuHandler.h"
#define   null_    0
const char yseLowerAccept[] = "y";
const char yseUpperAccept[] = "Y";

_Menu_Action Menu_Action;
_New_Data New_Data;
unsigned char Old_Data[100];
uint32_t Menu_State = MENU_MAIN;
void show_1(char *input, char *message)
{
    strcpy(message, "show one function \r\n");
}
void show_2(char *input, char *message)
{
    strcpy(message, "change Frequency\r\n");
}
void show_3(char *input, char *message)
{
    strcpy(message, "show three function \r\n");
}
void show_4(char *input, char *message)
{
    strcpy(message, "show four function \r\n");
}
void show_5(char *input, char *message)
{
    strcpy(message, "show five function \r\n");
}
void mainmenu1(char *input, char *message)
{
    float newPram = 0;
    printf("mainmenu1 \r\n");
    for (uint8_t index = 0; input[index] != '\r'; index++)
    {
        newPram = (input[index] - 0x30) + newPram * 10;
    }
    sprintf(message, "Do you want to change from last to new %f\r\n", newPram);
}
float frequency = 0;
submenu_t main_menu[] = {
    {"1-> show 1", show_1, "1\r\n", MENU_MAIN, NULL, 0},
    {"2-> show 2", show_2, "2\r\n", MENU_1, NULL, null_},
    {"3-> show 3", NULL, "3\r\n", MENU_MAIN, {"frequency = ", _float, Report_Params_Cmd}, &frequency},
    {"4-> show 4", show_4, "4\r\n", MENU_MAIN, NULL, null_},
    {"5-> show 5", show_5, "5\r\n", MENU_MAIN, NULL, null_},
};

uint32_t safetyTime = 0;
submenu_t menu_1[] = {
    {"Enter new frequency param  -> ", NULL, NULL, MENU_MAIN, {"frequency", _float, Change_Params_Cmd}, &frequency},
};
uint32_t currentMenu = 0;
menu_t allMenus[] = {
    {},
    {"\r\n********* test menu *******\r\n", main_menu, sizeof(main_menu) / sizeof(main_menu[0]), "\r\n end menu \r\n"},
    {"\r\n********* change frequncy menu*******\r\n", menu_1, sizeof(menu_1) / sizeof(menu_1[0]), ""},
};
char outputFuc[500];
char *hasEnterchar;
void menuProcess(char *input)
{

    if (memcmp(input, "start\r\n", 5) == 0)
    {
        Menu_Action.State = Refresh_Menu_Items;
    }
    else
    {
        if (Menu_Action.State == Answer_Save_Params)
        {
            Menu_Action.State = No_Action;
            if (memcmp(input, yseLowerAccept, 1) == 0 || memcmp(input, yseUpperAccept, 1) == 0)
            {
                switch (allMenus[Menu_State].menus[0].Data_Type.data_type)
                {
                case _char:

                    break;
                case _int:
                    *((uint32_t *)allMenus[Menu_State].menus[0].Data) = New_Data.Int;
                    break;
                case _float:
                    *((float *)allMenus[Menu_State].menus[0].Data) = New_Data.Float;
                    break;
                case _string:
                    *(char *)allMenus[Menu_State].menus[0].Data = malloc(strlen(New_Data.String));
                    strcpy((char *)allMenus[Menu_State].menus[0].Data, New_Data.String);
                    break;
                }
            }
            Menu_State = allMenus[Menu_State].menus[0].nextMenu;
            Menu_Action.State = Refresh_Menu_Items;
            // return;
        }
        for (uint32_t i = 0; i < allMenus[Menu_State].sizeMenu; i++)
        {
            if (allMenus[Menu_State].menus[i].Data_Type.cmd_type == Change_Params_Cmd)
            {
                switch (allMenus[Menu_State].menus[i].Data_Type.data_type)
                {
                case _char:

                    break;
                case _int:
                    sprintf(Old_Data, "%d", *((uint32_t *)allMenus[Menu_State].menus[i].Data));
                    New_Data.Int = 0;
                    for (uint32_t i = 0; (input[i] != '\0'); i++)
                    {
                        if ((input[i] >= '0') && (input[i] <= '9'))
                        {
                            New_Data.Int = (uint32_t)((input[i] - 48) + (New_Data.Int * 10));
                        }
                    }
                    // New_Data.Int = (int)atoi(input);
                    break;
                case _float:
                    sprintf(Old_Data, "%f", *((float *)allMenus[Menu_State].menus[i].Data));
                    New_Data.Float = (float)atof(input);
                    break;
                case _string:
                    strcpy(Old_Data, (char *)allMenus[Menu_State].menus[i].Data);
                    New_Data.String = malloc(strlen(input));
                    strcpy(New_Data.String, input);
                    break;
                }
                sprintf(Menu_Action.Message, "Are you sure change %s from *%s* to *%s* ? yes (y) / no (n) : ", allMenus[Menu_State].menus[i].Data_Type.title, Old_Data, input);
                Menu_Action.State = Request_Save_Params;
                break;
            }
            if (allMenus[Menu_State].menus[i].stringIndex == NULL)
            {
                hasEnterchar = strchr(input, '\r');
                if (hasEnterchar != '\0')
                {
                    printf("has  enter char \r\n");
                    strncpy(outputFuc, input, strlen(input) - 2);
                }
                else
                {
                    printf("not enter char \r\n");
                    strncpy(outputFuc, input, strlen(input));
                }
                allMenus[Menu_State].menus[i].function(outputFuc, Menu_Action.Message);
                Menu_State = allMenus[Menu_State].menus[i].nextMenu;
                if (strlen(Menu_Action.Message) != 0)
                {
                    Menu_Action.State = Display_Function_Output;
                }
                else
                {
                    Menu_Action.State = Refresh_Menu_Items;
                }

                break;
            }
            else
            {
                // if (my_memcmp(input, allMenus[Menu_State].menus[i].stringIndex, strlen(input)) == 0)
                if (memcmp(input, allMenus[Menu_State].menus[i].stringIndex, strlen(input)) == 0)
                {

                    if (allMenus[Menu_State].menus[i].Data_Type.cmd_type == Report_Params_Cmd)
                    {
                        switch (allMenus[Menu_State].menus[i].Data_Type.data_type)
                        {
                        case _char:

                            break;
                        case _int:
                            // itoa(*((int*)allMenus[Menu_State].menus[i].Data),Old_Data,100);
                            sprintf(Old_Data, "%d", *((uint32_t *)allMenus[Menu_State].menus[i].Data));
                            break;
                        case _float:
                            sprintf(Old_Data, "%f", *((float *)allMenus[Menu_State].menus[i].Data));
                            // ftoa(*((float*)allMenus[Menu_State].menus[i].Data),Old_Data,2);
                            break;
                        case _string:
                            strcpy(Old_Data, (char *)allMenus[Menu_State].menus[i].Data);
                            break;
                        }

                        sprintf(Menu_Action.Message, "%s = %s\r\n", allMenus[Menu_State].menus[i].Data_Type.title, Old_Data);
                        Menu_Action.State = Report_Params;
                    }
                    else if (allMenus[Menu_State].menus[i].function != NULL)
                    {
                        hasEnterchar = strchr(input, '\r');
                        if (hasEnterchar != '\0')
                        {
                            printf("has  enter char \r\n");
                            strncpy(outputFuc, input, strlen(input) - 2);
                        }
                        else
                        {
                            printf("not enter char \r\n");
                            strncpy(outputFuc, input, strlen(input));
                        }
                        allMenus[Menu_State].menus[i].function(input, Menu_Action.Message);
                        if (strlen(Menu_Action.Message) != 0)
                        {
                            Menu_Action.State = Display_Function_Output;
                            Menu_State = allMenus[Menu_State].menus[i].nextMenu;
                        }
                        else
                        {
                            Menu_Action.State = Refresh_Menu_Items;
                        }
                    }
                    else if (allMenus[Menu_State].menus[i].nextMenu != 0)
                    {
                        Menu_State = allMenus[Menu_State].menus[i].nextMenu;
                        Menu_Action.State = Refresh_Menu_Items;
                    }

                    break;
                }
                else
                {
                    Menu_Action.State = Refresh_Menu_Items;
                }
            }
        }
    }
}
char display[500];
void Show_Menu_Process(void)
{
    if (Menu_Action.State == Display_Function_Output)
    {
        memset(display, 0, sizeof(display));
        sprintf(display, "%s", Menu_Action.Message);
        printf("%s\r\n", display);
        Menu_Action.State = Refresh_Menu_Items;
        *Menu_Action.Message = NULL;
    }
    if (Menu_Action.State == Request_Save_Params)
    {
        Menu_Action.State = Answer_Save_Params;
        memset(display, 0, sizeof(display));
        sprintf(display, "%s", Menu_Action.Message);
        *Menu_Action.Message = NULL;
        printf("%s\r\n", display);
    }
    if (Menu_Action.State == Report_Params)
    {
        Menu_Action.State = Refresh_Menu_Items;
        memset(display, 0, sizeof(display));
        sprintf(display, "%s", Menu_Action.Message);
        *Menu_Action.Message = NULL;
        printf("%s\r\n", display);
    }

    if (Menu_Action.State == Refresh_Menu_Items)
    {
        memset(display, 0, sizeof(display));
        sprintf(display, "%s", allMenus[Menu_State].menutitle);
        printf("%s\r\n", display);
        for (int j = 0; j < allMenus[Menu_State].sizeMenu; j++)
        {
            memset(display, 0, sizeof(display));
            sprintf(display, "%s", allMenus[Menu_State].menus[j].stringData);
            printf("%s\r\n", display);
        }
        memset(display, 0, sizeof(display));
        sprintf(display, "%s", allMenus[Menu_State].footerMenu);
        Menu_Action.State = No_Action;
        printf("%s\r\n", display);
    }
}
