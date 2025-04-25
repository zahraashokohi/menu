#include "MenuHandler.h"
#define null_ 0
typedef struct
{
    float one;
    float two;
    float three;

} frequency_t;

frequency_t frequency = {0};
void show_Reports(char *input, char *message)
{
    strcpy(message, "show one function \r\n");
}
void ChangeFrequency(char *input, char *message)
{
    strcpy(message, "change Frequency\r\n");
}
void show_3(char *input, char *message)
{
    strcpy(message, "show three function \r\n");
    printf("one = %f , second = %f, third = %f \r\n", frequency.one, frequency.two, frequency.three);
}

void show_4(char *input, char *message)
{
    strcpy(message, "just change flag \r\n");

}

uint32_t safetyTime = 0;
submenu_t main_menu[] = {
    {"1-> Show Reports", show_Reports, "1\r\n", MENU_MAIN, NULL, null_},
    {"2-> Change One Frequency", NULL, "2\r\n", MENU_One_Frequency, NULL, null_},
    {"3-> Change Three Frequency", show_4, "3\r\n", MENU_Three_Frequency, NULL, null_},
    {"4-> Show Frequencys", show_3, "4\r\n", MENU_MAIN, NULL, null_},
    {"5-> Show SafetyTime", NULL, "5\r\n", MENU_MAIN, {"SafetyTime", _int, Report_Params_Cmd}, &safetyTime},
    {"6-> Change SafetyTime", NULL, "6\r\n", MENU_SAFETYTIME, NULL, null_},
};

submenu_t changeSafetyTime[] = {
    {"Enter new frequency param  -> ", NULL, NULL, MENU_MAIN, {"safetytime", _int, Change_Params_Cmd}, &safetyTime},
};
submenu_t frequncy_one[] = {
    {"Enter new frequency param  -> ", NULL, NULL, MENU_Frequencys, {"frequency", _float, Change_Params_Cmd}, &frequency.one},
};

submenu_t frequncy_threeFirst[] = {
    {"Enter new frequency param  -> ", NULL, NULL, MENU_Three_Frequency, {"frequency", _float, Change_Params_Cmd}, &frequency.one},
};
submenu_t frequncy_threeSecond[] = {
    {"Enter new frequency param  -> ", NULL, NULL, MENU_Three_Frequency, {"frequency", _float, Change_Params_Cmd}, &frequency.two},
};
submenu_t frequncy_threeThird[] = {
    {"Enter new frequency param  -> ", NULL, NULL, MENU_Three_Frequency, {"frequency", _float, Change_Params_Cmd}, &frequency.three},
};
submenu_t frequncy_three[] = {
    {"1-> Change One Frequency", NULL, "1\r\n", MENU_Three_One_Frequency, NULL, null_},
    {"2-> Change Second Frequency", NULL, "2\r\n", MENU_Three_Two_Frequency, NULL, null_},
    {"3-> Change The Third Frequency", NULL, "3\r\n", MENU_Three_Third_Frequency, NULL, null_},
    {"4-> Back", NULL, "4\r\n", MENU_Frequencys, NULL, null_},
};
submenu_t frequncys[] = {
    {"1-> Change One Frequency", NULL, "1\r\n", MENU_One_Frequency, NULL, null_},
    {"2-> Change Three Frequency", NULL, "2\r\n", MENU_Three_Frequency, NULL, null_},
    {"3-> Back", NULL, "3\r\n", MENU_MAIN, NULL, null_},
};

uint32_t currentMenu = 0;
uint32_t size_main = sizeof(main_menu) / sizeof(main_menu[0]);
void func(void)
{
    printf("size_main = %d \r\n", size_main);
}
menu_t allMenus[] = {
    {},
    MENU_INIT(main_menu, "\r\n********* test menu *******\r\n", "\r\n end menu \r\n"),
     MENU_INIT(frequncys, "\r\n********* change frequncy menu*******\r\n", ""),
     MENU_INIT(frequncy_one, "\r\n********* change One Frequencys *******\r\n", ""),
     MENU_INIT(frequncy_three, "\r\n*********change Three Frequencys *******\r\n", ""),

     MENU_INIT(frequncy_threeFirst, "\r\n*********change frist Frequencys *******\r\n", ""),
     MENU_INIT(frequncy_threeSecond, "\r\n*********change seconf Frequencys *******\r\n", ""),
     MENU_INIT(frequncy_threeThird, "\r\n*********change third Frequencys *******\r\n", ""),
     MENU_INIT(changeSafetyTime, "\r\n*********change third Frequencys *******\r\n", ""),
    /*{"\r\n************************ Main Menu  ************************ \r\n",
        main_menu, sizeof(main_menu) / sizeof(main_menu[0]),
        ""},
    {"\r\n************************ frequncys Menu  ************************ \r\n",
        frequncys, sizeof(frequncys) / sizeof(frequncys[0]),
        ""},

    {"\r\n************************ frequncy_one Menu  ************************ \r\n",
        frequncy_one, sizeof(frequncy_one) / sizeof(frequncy_one[0]),
        ""},
    {"\r\n************************ frequncy_three Menu  ************************ \r\n",
        frequncy_three, sizeof(frequncy_three) / sizeof(frequncy_three[0]),
        ""},*/
};
