// Build
//
// # Windows MSVC
// cl -D_CRT_SECURE_NO_WARNINGS -W4 User32.Lib crossline.c example.c /Feexample.exe
//
// # Windows Clang
// clang -D_CRT_SECURE_NO_WARNINGS -Wall -lUser32 crossline.c example.c -o example.exe
//
// # Linux Clang
// clang -Wall crossline.c example.c -o example
//
// # GCC(Linux, MinGW, Cygwin, MSYS2)
// gcc -Wall crossline.c example.c -o example

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Crossline.hpp"

#include <functional>
#include <iostream>

#define CLINE Crossline::Instance()

struct Commands {
    int Insert(CommandParam & param) {
        // TODO
        std::cout << "insert command.\n";
        return 1;
    }
    int Select(CommandParam & param) {
        // TODO
        std::cout << "select command.\n";
        return 1;
    }
    int Update(CommandParam & param) {
        return 1;
    }
};

int main ()
{
    char buf[256];
    Commands cmds;

    CLINE.LoadHistory ("history.txt");

    CLINE.AddCommand("insert", std::bind(&Commands::Insert, &cmds, std::placeholders::_1));
    CLINE.AddCommand("select", std::bind(&Commands::Select, &cmds, std::placeholders::_1));

    while (NULL != CLINE.ReadLine ("Crossline> ", buf, sizeof(buf))) {
        printf ("Read line: \"%s\"\n", buf);
    }    

    CLINE.SaveHistory ("history.txt");
    return 0;
}
