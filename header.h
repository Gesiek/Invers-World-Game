#include <fstream>
#include <iostream>
#include <string>

#include <windows.h>
#include <conio.h>
#include <iomanip>

#include <ctime>
#include <cstdlib>

#include <cwchar>

#include <ios>
#include <limits>

#include <thread>

#undef max

CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
CONSOLE_SCREEN_BUFFER_INFOEX consoleScreenBufferInfoex;
CONSOLE_FONT_INFOEX consoleFontInfo;
CONSOLE_CURSOR_INFO consoleCursorInfo;
WINDOWINFO winfo;

auto screenX = GetSystemMetrics(SM_CXSCREEN);
auto screenY = GetSystemMetrics(SM_CYSCREEN);