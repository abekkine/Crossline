# Crossline.hpp

**Crossline.hpp** is a header only C++ implementation of jcwangxp's [Crossline](https://github.com/jcwangxp/Crossline) library.

## Crossline APIs

```cpp
// Set prompt.
void Crossline::SetPrompt(const std::string & prompt);

// Set line parser callback method.
void Crossline::SetLineParser(std::function<void(const std::string &)> parser);

// Set move/cut word delimiter, default is all not digital and alphabetic characters.
// void  crossline_delimiter_set (const char *delim);
void Crossline::SetDelimiter(const char delim);

// Main API to read a line, return buf if get line, return NULL if EOF.
// char* crossline_readline (const char *prompt, char *buf, int size);
void Crossline::Readline();

// Read a character from terminal without echo
int Crossline::GetChar();
// int     crossline_getch (void);
```

* History APIs

```c
void Crossline::SetHistoryFile(const std::string & filename);

// Save history to file
int Crossline::SaveHistory()
// int   crossline_history_save (const char *filename);

// Load history from file
int Crossline::LoadHistory();
//int   crossline_history_load (const char *filename);

// Show history in buffer
void Crossline::ShowHistory();
// void  crossline_history_show (void);

// Clear history
void Crossline::ClearHistory();
// void  crossline_history_clear (void);
```

* Completion APIs

`TODO :` Will be implemented later.

## Color APIs

```c
// Set text color, CROSSLINE_COLOR_DEFAULT will revert to default setting
// `\t` is not supported in Linux terminal, same below. Don't use `\n` in Linux terminal, same below.
void Crossline::SetTextColor(Crossline::Color color);
// void crossline_color_set (crossline_color_e color);

// Set default prompt color
void Crossline::SetPromptColor(Crossline::Color color);
// void crossline_prompt_color_set (crossline_color_e color);
```

## Paging APIs

`TODO :` Will be implemented later.

## Cursor APIs

These APIs are used internally first, then I think they're common and can be used by CLI tools also, so make them open and write some APIs which are not used by crossline at all.

```c
// Get screen rows and columns
void Crossline::GetScreen(int & rows, int & cols);
// void crossline_screen_get (int *pRows, int *pCols);

// Clear current screen
void Crossline::ClearScreen();
// void crossline_screen_clear (void);

// Get cursor postion (0 based)
int Crossline::GetCursorPosition(int & row, int & col);
// int  crossline_cursor_get (int *pRow, int *pCol);

// Set cursor postion (0 based)
void Crossline::SetCursorPosition(const int row, const int col);
// void crossline_cursor_set (int row, int col);

/* Move cursor with row and column offset, 
 *   row_off > 0 move up row_off lines, 
 *           < 0 move down abs(row_off) lines
 *           = 0 no move for row, 
 *   similar with col_off
 */
void Crossline::MoveCursor(const int row_offset, const int col_offset);
// void crossline_cursor_move (int row_off, int col_off);

// Hide or show cursor
void Crossline::ShowCursor(bool value);
// void crossline_cursor_hide (int bHide);
```
