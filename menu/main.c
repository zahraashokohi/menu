#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <conio.h>
#include <unistd.h>

#include "MenuHandler.h"




char input[300];
int main()
{
    printf("Hello world!\n");
    while (1)
    {
        if (_kbhit()) {
            scanf("%s", input);
            menuProcess(input);
        }


        Show_Menu_Process();
    }

    // return 0;
}
