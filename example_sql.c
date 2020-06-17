/*

This Example implements a simple SQL syntax parser.
	INSERT INTO <table> SET column1=value1,column2=value2,...
	SELECT <* | column1,columnm2,...> FROM <table> [WHERE] [ORDER BY] [LIMIT] [OFFSET]
	UPDATE <table> SET column1=value1,column2=value2 [WHERE] [ORDER BY] [LIMIT] [OFFSET]
	DELETE FROM <table> [WHERE] [ORDER BY] [LIMIT] [OFFSET]
	CREATE [UNIQUE] INDEX <name> ON <table> (column1,column2,...)
	DROP {TABLE | INDEX} <name>
	SHOW {TABLES | DATABASES}
	DESCRIBE <TABLE>
	help {INSERT | SELECT | UPDATE | DELETE | CREATE | DROP | SHOW | DESCRIBE | help | exit | history}


Build

# Windows MSVC
cl -D_CRT_SECURE_NO_WARNINGS -W4 User32.Lib crossline.c example_sql.c /Feexample_sql.exe

# Windows Clang
clang -D_CRT_SECURE_NO_WARNINGS -Wall -lUser32 crossline.c example_sql.c -o example_sql.exe

# Linux Clang
clang -Wall crossline.c example_sql.c -o example_sql

# GCC(Linux, MinGW, Cygwin, MSYS2)
gcc -Wall crossline.c example_sql.c -o example_sql

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Crossline.hpp"

#ifdef _WIN32
	#define strcasecmp				_stricmp
	#define strncasecmp				_strnicmp
#endif

#define CLINE Crossline::Instance()

void sql_add_completion (crossline_completions_t *pCompletion, const char *prefix, const char **match, const char **help)
{
	int i, len = (int)strlen(prefix);
	crossline_color_e wcolor, hcolor;
	for (i = 0;  NULL != match[i]; ++i) {
		if (0 == strncasecmp(prefix, match[i], len)) {
			if (NULL != help) {
				if (i < 8) { 
					wcolor = (crossline_color_e) (CROSSLINE_FGCOLOR_BRIGHT | CROSSLINE_FGCOLOR_YELLOW); 
				} else { 
					wcolor = (crossline_color_e) (CROSSLINE_FGCOLOR_BRIGHT | CROSSLINE_FGCOLOR_CYAN); 
				}
				hcolor = i%2 ? CROSSLINE_FGCOLOR_WHITE : CROSSLINE_FGCOLOR_CYAN;
				CLINE.AddCompletionWithColor (pCompletion, match[i], wcolor, help[i], hcolor);
			} else {
				CLINE.AddCompletionWithColor (pCompletion, match[i], (crossline_color_e) (CROSSLINE_FGCOLOR_BRIGHT | CROSSLINE_FGCOLOR_MAGENTA), NULL, (crossline_color_e) 0);
			}
		}
	}
}

int sql_find_key (const char **match, const char *prefix)
{
	int i;
	for (i = 0; NULL != match[i]; ++i) {
		if (0 == strcasecmp(prefix, match[i])) {
		  return i;
		}
	}
	return -1;
}

enum {
	CMD_INSERT,
	CMD_SELECT,
	CMD_UPDATE,
	CMD_DELETE,
	CMD_CREATE,
	CMD_DROP,
	CMD_SHOW,
	CMD_DESCRIBE,
	CMD_HELP,
	CMD_EXIT,
	CMD_HISTORY,
};

void sql_completion_hook (char const *buf, crossline_completions_t *pCompletion)
{
	int	num, cmd, bUnique = 0;
	char split[8][128], last_ch;
	static const char* sql_cmd[] = {"INSERT", "SELECT", "UPDATE", "DELETE", "CREATE", "DROP", "SHOW", "DESCRIBE", "help", "exit", "history", NULL};
	static const char* sql_cmd_help[] = {
		"Insert a record to table",
		"Select records from table",
		"Update records in table",
		"Delete records from table",
		"Create index on table",
		"Drop index or table",
		"Show tables or databases",
		"Show table schema",
		"Show help for topic",
		"Exit shell",
		"Show history"};
	static const char* sql_caluse[] = {"WHERE", "ORDER BY", "LIMIT", "OFFSET", NULL};
	static const char* sql_index[]  = {"UNIQUE", "INDEX", NULL};
	static const char* sql_drop[]   = {"TABLE", "INDEX", NULL};
	static const char* sql_show[]   = {"TABLES", "DATABASES", NULL};
	crossline_color_e tbl_color = (crossline_color_e) (CROSSLINE_FGCOLOR_WHITE | CROSSLINE_BGCOLOR_GREEN);
	crossline_color_e col_color = (crossline_color_e) (CROSSLINE_FGCOLOR_WHITE | CROSSLINE_BGCOLOR_CYAN);
	crossline_color_e idx_color = (crossline_color_e) (CROSSLINE_FGCOLOR_WHITE | CROSSLINE_BGCOLOR_YELLOW);

	memset (split, '\0', sizeof (split));
	num = sscanf (buf, "%s %s %s %s %s %s %s %s", split[0], split[1], split[2], split[3], split[4], split[5], split[6], split[7]);
	cmd = sql_find_key (sql_cmd, split[0]);

	if ((cmd < 0) && (num <= 1)) {
		sql_add_completion (pCompletion, split[0], sql_cmd, sql_cmd_help);
	}
	last_ch = buf[strlen(buf) - 1];
	switch (cmd) {
	case CMD_INSERT: // INSERT INTO <table> SET column1=value1,column2=value2,...
		if ((1 == num) && (' ' == last_ch)) {
			CLINE.AddCompletion (pCompletion, "INTO", NULL);
		} else if ((2 == num) && (' ' == last_ch)) {
			CLINE.SetHintColor (pCompletion, "table name", tbl_color);
		} else if ((3 == num) && (' ' == last_ch)) {
			CLINE.AddCompletion (pCompletion, "SET", NULL);
		} else if ((4 == num) && (' ' == last_ch)) {
			CLINE.SetHintColor (pCompletion, "column1=value1,column2=value2,...", col_color);
		}
		break;
	case CMD_SELECT: // SELECT < * | column1,columnm2,...> FROM <table> [WHERE] [ORDER BY] [LIMIT] [OFFSET]
		if ((1 == num) && (' ' == last_ch)) {
			CLINE.SetHintColor (pCompletion, "* | column1,columnm2,...", col_color);
		} else if ((2 == num) && (' ' == last_ch)) {
			CLINE.AddCompletion (pCompletion, "FROM", NULL);
		} else if ((3 == num) && (' ' == last_ch)) {
			CLINE.SetHintColor (pCompletion, "table name", tbl_color);
		} else if ((4 == num) && (' ' == last_ch)) {
			sql_add_completion (pCompletion, "", sql_caluse, NULL);
		} else if ((num > 4) && (' ' != last_ch)) {
			sql_add_completion (pCompletion, split[num-1], sql_caluse, NULL);
		}
		break;
	case CMD_UPDATE: // UPDATE <table> SET column1=value1,column2=value2 [WHERE] [ORDER BY] [LIMIT] [OFFSET]
		if ((1 == num) && (' ' == last_ch)) {
			CLINE.SetHintColor (pCompletion, "table name", tbl_color);
		} else if ((2 == num) && (' ' == last_ch)) {
			CLINE.AddCompletion (pCompletion, "SET", NULL);
		} else if ((3 == num) && (' ' == last_ch)) {
			CLINE.SetHintColor (pCompletion, "column1=value1,column2=value2,...", col_color);
		} else if ((4 == num) && (' ' == last_ch)) {
			sql_add_completion (pCompletion, "", sql_caluse, NULL);
		} else if ((num > 4) && (' ' != last_ch)) {
			sql_add_completion (pCompletion, split[num-1], sql_caluse, NULL);
		}
		break;
	case CMD_DELETE: // DELETE FROM <table> [WHERE] [ORDER BY] [LIMIT] [OFFSET]
		if ((1 == num) && (' ' == last_ch)) {
			CLINE.AddCompletion (pCompletion, "FROM", NULL);
		} else if ((2 == num) && (' ' == last_ch)) {
			CLINE.SetHintColor (pCompletion, "table name", tbl_color);
		} else if ((3 == num) && (' ' == last_ch)) {
			sql_add_completion (pCompletion, "", sql_caluse, NULL);
		} else if ((num > 3) && (' ' != last_ch)) {
			sql_add_completion (pCompletion, split[num-1], sql_caluse, NULL);
		}
		break;
	case CMD_CREATE: // CREATE [UNIQUE] INDEX <name> ON <table> (column1,column2,...)
		if ((1 == num) && (' ' == last_ch)) {
			sql_add_completion (pCompletion, "", sql_index, NULL);
		} else if ((2 == num) && (' ' != last_ch)) {
			sql_add_completion (pCompletion, split[1], sql_index, NULL);
		} else {
			if ((num >= 2) && !strcasecmp (split[1], "UNIQUE")) {
				bUnique = 1;
			}
			if ((2 == num) && bUnique && (' ' == last_ch)) {
				CLINE.AddCompletion (pCompletion, "INDEX", NULL);
			}
			else if ((2+bUnique == num) && (' ' == last_ch)) {
				CLINE.SetHintColor (pCompletion, "index name", idx_color);
			} else if ((3+bUnique == num) && (' ' == last_ch)) {
				CLINE.AddCompletion (pCompletion, "ON", NULL);
			} else if ((4+bUnique == num) && (' ' == last_ch)) {
				CLINE.SetHintColor (pCompletion, "table name", tbl_color);
			} else if ((5+bUnique == num) && (' ' == last_ch)) {
				CLINE.SetHintColor (pCompletion, "(column1,column2,...)", col_color);
			}
		}
		break;
	case CMD_DROP:	// DROP TABLE <name>, DROP INDEX <name>
		if ((1 == num) && (' ' == last_ch)) {
			sql_add_completion (pCompletion, "", sql_drop, NULL);
		} else if ((2 == num) && (' ' != last_ch)) {
			sql_add_completion (pCompletion, split[1], sql_drop, NULL);
		} else if ((num == 2) && (' ' == last_ch)) {
			if (!strcasecmp (split[1], "TABLE")) {
				CLINE.SetHintColor (pCompletion, "table name", tbl_color);
			} else if (!strcasecmp (split[1], "INDEX")) {
				CLINE.SetHintColor (pCompletion, "index name", idx_color);
			}
		}
		break;
	case CMD_SHOW: // SHOW TABLES, SHOW DATABASES
		if ((1 == num) && (' ' == last_ch)) {
			sql_add_completion (pCompletion, "", sql_show, NULL);
		} else if ((2 == num) && (' ' != last_ch)) {
			sql_add_completion (pCompletion, split[1], sql_show, NULL);
		}
		break;
	case CMD_DESCRIBE: // describe <table>
		if (' ' == last_ch) {
			CLINE.SetHintColor (pCompletion, "table name", tbl_color);
		}
		break;
	case CMD_HELP:
		if ((1 == num) && (' ' == last_ch)) {
			sql_add_completion (pCompletion, "", sql_cmd, NULL);
		} else if ((2 == num) && (' ' != last_ch)) {
			sql_add_completion (pCompletion, split[1], sql_cmd, NULL);
		}
		break;
	case CMD_EXIT:
		break;
	}
}

int main ()
{
	char buf[256];

	CLINE.RegisterCompletionHook (sql_completion_hook);
	CLINE.LoadHistory ("history.txt");
	CLINE.PromptColor ((crossline_color_e) (CROSSLINE_FGCOLOR_BRIGHT | CROSSLINE_FGCOLOR_GREEN));

	while (NULL != CLINE.ReadLine ("SQL> ", buf, sizeof(buf))) {
		printf ("Read line: \"%s\"\n", buf);
		if (!strcmp (buf, "history")) {
			CLINE.ShowHistory ();
		} else if (!strcmp (buf, "exit")) {
			break;
		}
	}

	CLINE.SaveHistory ("history.txt");
	return 0;
}
