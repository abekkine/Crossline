// Build
//
// # Windows MSVC
// cl -D_CRT_SECURE_NO_WARNINGS -W4 User32.Lib crossline.c example2.c /Feexample2.exe
//
// # Windows Clang
// clang -D_CRT_SECURE_NO_WARNINGS -Wall -lUser32 crossline.c example2.c -o example2.exe
//
// # Linux Clang
// clang -Wall crossline.c example2.c -o example2
//
// # GCC(Linux, MinGW, Cygwin, MSYS2)
// gcc -Wall crossline.c example2.c -o example2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Crossline.hpp"

#define CLINE Crossline::Instance()

static void pagint_test ()
{
	int i;
	CLINE.ResetPaging ();
	for (i = 0; i < 256; ++i) {
		printf ("Paging test: %3d\n", i);
		if (CLINE.CheckPaging (sizeof("paging test: ") + 3)) {
			break;
		}
	}
}

static void color_test ()
{
	printf ("\n*** Color test *** \n");
	printf ("  Default Foregroud and Backgroud\n\n");

	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_BLACK | CROSSLINE_BGCOLOR_WHITE));
	printf ("  Foregroud: Black");
	CLINE.SetColor (CROSSLINE_COLOR_DEFAULT);
	printf ("\n");	
	CLINE.SetColor ((crossline_color_e) (CROSSLINE_UNDERLINE | CROSSLINE_FGCOLOR_RED));
	printf ("  Foregroud: Red Underline\n");
	CLINE.SetColor (CROSSLINE_FGCOLOR_GREEN);
	printf ("  Foregroud: Green\n");
	CLINE.SetColor (CROSSLINE_FGCOLOR_YELLOW);
	printf ("  Foregroud: Yellow\n");
	CLINE.SetColor (CROSSLINE_FGCOLOR_BLUE);
	printf ("  Foregroud: Blue\n");
	CLINE.SetColor (CROSSLINE_FGCOLOR_MAGENTA);
	printf ("  Foregroud: Magenta\n");
	CLINE.SetColor (CROSSLINE_FGCOLOR_CYAN);
	printf ("  Foregroud: Cyan\n");
	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_WHITE | CROSSLINE_BGCOLOR_BLACK));
	printf ("  Foregroud: White");
	CLINE.SetColor (CROSSLINE_COLOR_DEFAULT);
	printf ("\n\n");	

	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_BRIGHT | CROSSLINE_FGCOLOR_BLACK | CROSSLINE_BGCOLOR_WHITE));
	printf ("  Foregroud: Bright Black");
	CLINE.SetColor (CROSSLINE_COLOR_DEFAULT);
	printf ("\n");	
	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_BRIGHT | CROSSLINE_FGCOLOR_RED));
	printf ("  Foregroud: Bright Red\n");
	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_BRIGHT | CROSSLINE_FGCOLOR_GREEN));
	printf ("  Foregroud: Bright Green\n");
	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_BRIGHT | CROSSLINE_FGCOLOR_YELLOW));
	printf ("  Foregroud: Bright Yellow\n");
	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_BRIGHT | CROSSLINE_FGCOLOR_BLUE));
	printf ("  Foregroud: Bright Blue\n");
	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_BRIGHT | CROSSLINE_FGCOLOR_MAGENTA));
	printf ("  Foregroud: Bright Magenta\n");
	CLINE.SetColor ((crossline_color_e) (CROSSLINE_UNDERLINE | CROSSLINE_FGCOLOR_BRIGHT | CROSSLINE_FGCOLOR_CYAN));
	printf ("  Foregroud: Bright Cyan Underline\n");
	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_BRIGHT | CROSSLINE_FGCOLOR_WHITE | CROSSLINE_BGCOLOR_BLACK));
	printf ("  Foregroud: Bright White\n\n");

	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_WHITE | CROSSLINE_BGCOLOR_BLACK));
	printf ("  Backgroud: Black   ");
	CLINE.SetColor (CROSSLINE_COLOR_DEFAULT);
	printf ("\n");	
	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_WHITE | CROSSLINE_BGCOLOR_RED));
	printf ("  Backgroud: Red     ");
	CLINE.SetColor (CROSSLINE_COLOR_DEFAULT);
	printf ("\n");	
	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_WHITE | CROSSLINE_BGCOLOR_GREEN));
	printf ("  Backgroud: Green   ");
	CLINE.SetColor (CROSSLINE_COLOR_DEFAULT);
	printf ("\n");	
	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_WHITE | CROSSLINE_BGCOLOR_YELLOW));
	printf ("  Backgroud: Yellow  ");
	CLINE.SetColor (CROSSLINE_COLOR_DEFAULT);
	printf ("\n");	
	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_WHITE | CROSSLINE_BGCOLOR_BLUE));
	printf ("  Backgroud: Blue    ");
	CLINE.SetColor (CROSSLINE_COLOR_DEFAULT);
	printf ("\n");	
	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_WHITE | CROSSLINE_BGCOLOR_MAGENTA));
	printf ("  Backgroud: Magenta ");
	CLINE.SetColor (CROSSLINE_COLOR_DEFAULT);
	printf ("\n");	
	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_WHITE | CROSSLINE_BGCOLOR_CYAN));
	printf ("  Backgroud: Cyan    ");
	CLINE.SetColor (CROSSLINE_COLOR_DEFAULT);
	printf ("\n");	
	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_BRIGHT | CROSSLINE_FGCOLOR_BLACK | CROSSLINE_BGCOLOR_WHITE));
	printf ("  Backgroud: White   ");
	CLINE.SetColor (CROSSLINE_COLOR_DEFAULT);
	printf ("\n\n");	

	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_WHITE | CROSSLINE_BGCOLOR_BRIGHT | CROSSLINE_BGCOLOR_BLACK));
	printf ("  Backgroud: Bright Black   ");
	CLINE.SetColor (CROSSLINE_COLOR_DEFAULT);
	printf ("\n");	
	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_WHITE | CROSSLINE_BGCOLOR_BRIGHT | CROSSLINE_BGCOLOR_RED));
	printf ("  Backgroud: Bright Red     ");
	CLINE.SetColor (CROSSLINE_COLOR_DEFAULT);
	printf ("\n");	
	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_BRIGHT | CROSSLINE_FGCOLOR_BLACK | CROSSLINE_BGCOLOR_BRIGHT | CROSSLINE_BGCOLOR_GREEN));
	printf ("  Backgroud: Bright Green   ");
	CLINE.SetColor (CROSSLINE_COLOR_DEFAULT);
	printf ("\n");	
	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_BRIGHT | CROSSLINE_FGCOLOR_BLACK | CROSSLINE_BGCOLOR_BRIGHT | CROSSLINE_BGCOLOR_YELLOW));
	printf ("  Backgroud: Bright Yellow  ");
	CLINE.SetColor (CROSSLINE_COLOR_DEFAULT);
	printf ("\n");	
	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_WHITE | CROSSLINE_BGCOLOR_BRIGHT | CROSSLINE_BGCOLOR_BLUE));
	printf ("  Backgroud: Bright Blue    ");
	CLINE.SetColor (CROSSLINE_COLOR_DEFAULT);
	printf ("\n");	
	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_WHITE | CROSSLINE_BGCOLOR_BRIGHT | CROSSLINE_BGCOLOR_MAGENTA));
	printf ("  Backgroud: Bright Magenta ");
	CLINE.SetColor (CROSSLINE_COLOR_DEFAULT);
	printf ("\n");	
	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_BRIGHT | CROSSLINE_FGCOLOR_BLACK | CROSSLINE_BGCOLOR_BRIGHT | CROSSLINE_BGCOLOR_CYAN));
	printf ("  Backgroud: Bright Cyan    ");
	CLINE.SetColor (CROSSLINE_COLOR_DEFAULT);
	printf ("\n");	
	CLINE.SetColor ((crossline_color_e) (CROSSLINE_FGCOLOR_BRIGHT | CROSSLINE_FGCOLOR_BLACK | CROSSLINE_BGCOLOR_BRIGHT | CROSSLINE_BGCOLOR_WHITE));
	printf ("  Backgroud: Bright White   ");
	CLINE.SetColor (CROSSLINE_COLOR_DEFAULT);
	printf ("\n");	
}

int main ()
{
	char buf[1024]="select ";

	CLINE.LoadHistory ("history.txt");
	CLINE.PromptColor ((crossline_color_e) (CROSSLINE_FGCOLOR_BRIGHT | CROSSLINE_FGCOLOR_GREEN));

	// Readline with initail text input
	if (NULL != CLINE.ReadLineWithText ("Crossline> ", buf, sizeof(buf))) {
		printf ("Read line: \"%s\"\n", buf);
	}
	// Readline loop
	while (NULL != CLINE.ReadLine ("Crossline> ", buf, sizeof(buf))) {
		printf ("Read line: \"%s\"\n", buf);

		if (!strcmp (buf, "history")) {
			CLINE.ShowHistory ();
		}

		if (!strcmp (buf, "paging")) {
			pagint_test ();
		}
		if (!strcmp (buf, "color")) {
			color_test ();
		}
	}

	CLINE.SaveHistory ("history.txt");
	return 0;
}
