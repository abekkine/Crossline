/*

Build

# Windows MSVC
cl -D_CRT_SECURE_NO_WARNINGS -W4 User32.Lib crossline.c example.c /Feexample.exe

# Windows Clang
clang -D_CRT_SECURE_NO_WARNINGS -Wall -lUser32 crossline.c example.c -o example.exe

# Linux Clang
clang -Wall crossline.c example.c -o example

# GCC(Linux, MinGW, Cygwin, MSYS2)
gcc -Wall crossline.c example.c -o example

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Crossline.hpp"

#define CLINE Crossline::Instance()

static void completion_hook (char const *buf, crossline_completions_t *pCompletion)
{
    int i;
    static const char *cmd[] = {"insert", "select", "update", "delete", "create", "drop", "show", "describe", "help", "exit", "history", NULL};

    for (i = 0; NULL != cmd[i]; ++i) {
        if (0 == strncmp(buf, cmd[i], strlen(buf))) {
            CLINE.crossline_completion_add (pCompletion, cmd[i], NULL);
        }
    }

}

int main ()
{
    char buf[256];
    
    CLINE.crossline_completion_register (completion_hook);
    CLINE.crossline_history_load ("history.txt");

    while (NULL != CLINE.crossline_readline ("Crossline> ", buf, sizeof(buf))) {
        printf ("Read line: \"%s\"\n", buf);
    }    

    CLINE.crossline_history_save ("history.txt");
    return 0;
}
