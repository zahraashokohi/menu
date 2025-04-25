#include "MenuHandler.h"

const char yseLowerAccept[] = "y";
const char yseUpperAccept[] = "Y";

typedef struct {

    uint8_t divider : 1;
}flag_t;


typedef struct {

    uint8_t  decimal;
}cnt_t;
cnt_t   cnt = {0};

flag_t  flg = {0};


_Menu_Action Menu_Action;
_New_Data New_Data;
unsigned char Old_Data[100];
uint32_t Menu_State = MENU_MAIN;

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
                printf("Change_Params_Cmd");
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
                    for (uint32_t i = 0; (input[i] != '\0'); i++)
                    {
                        if ((input[i] >= '0') && (input[i] <= '9'))
                        {
                            New_Data.Float = (float)((input[i] - 48) + (New_Data.Float * 10));
                        }
                        if(flg.divider)
                        {
                            cnt.decimal++;
                        }
                        if(input[i] == '.')
                        {
                            flg.divider = 1;
                        }
                    }
                    if(flg.divider)
                    {
                        flg.divider = 0;
                        uint32_t power = 1;
                        for(uint8_t index = 0; index < cnt.decimal; index++)
                        {
                            power = power* 10;
                        }
                        New_Data.Float  = New_Data.Float / power;
                        printf("power = %d \r\n",power);
                    }

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
    printf("Menu_Action.State = %d , Menu_State = %d \r\n", Menu_Action.State,Menu_State );
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
