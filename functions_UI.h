#pragma once

/*f1 - cls przed, f2 - cls po */
void loadingScreen(int s = 10, bool f1 = 0, bool f2 = 0) {

    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &screenBufferInfo);
    int bufSize = screenBufferInfo.dwSize.X;

    char chars[] = {'-', '\\', '|', '/'};
    unsigned int i;

    if (f1) system("cls");
    for (i = 0; i < s; ++i) {
        //printf("%c \r", chars[ i % sizeof(chars) ]);
        cout << setw(bufSize / 2);
        cout << chars[i % 4];
        cout << "\r";
        ///fflush(stdout);
        Sleep(200);
    }
    if (f2) system("cls");

}

/* ukryj migajacy kursor*/
void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void showCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void maximize() {
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
}

void goFullscreen() {
    system("mode 650");
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
}

void hideScrollbars() {

    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    // Get console handle and get screen buffer information from that handle.
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &screenBufferInfo);
    // Get rid of the scrollbar by setting the screen buffer size the same as 
    // the console window size.
    COORD new_screen_buffer_size;
    // screenBufferInfo.srWindow allows us to obtain the width and height info 
    // of the visible console in character cells.
    // That visible portion is what we want to set the screen buffer to, so that 
    // no scroll bars are needed to view the entire buffer.
    new_screen_buffer_size.X = screenBufferInfo.srWindow.Right - screenBufferInfo.srWindow.Left + 1; // Columns
    new_screen_buffer_size.Y = screenBufferInfo.srWindow.Bottom - screenBufferInfo.srWindow.Top + 1; // Rows
    // Set new buffer size
    SetConsoleScreenBufferSize(hConsole, new_screen_buffer_size);

}

void blockScrollbars() {
    ShowScrollBar(GetConsoleWindow(), SB_BOTH, FALSE);
}

/*backspace od bie¾¥cej lini do lini nr lin, */
void clearLines(int lin) {

    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsole, &screenBufferInfo);

    short yy = lin;
    COORD cord = {0, yy};
    int bufSize = screenBufferInfo.dwSize.X;

    //cout<<bufSize<<endl;
    //cout<<screenBufferInfo.srWindow.Right<<endl;
    //cout<<screenBufferInfo.dwMaximumWindowSize.X<<endl;
    //cout<<screenBufferInfo.srWindow.Bottom<<endl;
    //cout<<getCursorPosition().X<<"x"<<getCursorPosition().Y<<endl;
    while (getCursorPosition().Y > cord.Y) {
        cout << "\b \b";
        if ((getCursorPosition().X == 0)) {
            yy = (getCursorPosition().Y) - 1;
            setCursorPosition(bufSize - 1, yy);
            //ostatni znak w screenBufferze nie da si© usun¥† backspace'm, bo kursor przeskakuje ju¾ do nowej lini, wi©c:
            cout << ' '; // ;)
            setCursorPosition(bufSize - 1, yy);
        }
    }
    while (getCursorPosition().X > 0) {
        cout << "\b \b";
    }
    cout << "\b \b";
}

void clear() {
    system("cls");
    Sleep(100);
}

void coutMenu(string tab[], int n, int which_one) {

    for (int i = 0; i < n; i++) {
        if (i == which_one) {
            cout << tab[i] << " <-" << endl;
        }
        else {
            cout << tab[i] << endl;
        }
    }

}

void coutMenuDesc(int access_level) {
    switch (access_level) {
    case 1:
        cout << "------------------------------------------------\n";
        cout << "Trafiˆe˜ do loleoleelo leo eko oe ro ijriojior \njoij rjojreijii eru hy uuewiur ieui hiur ihu hriwr\n";
        cout << "------------------------------------------------\n\n";
        break;
    case 2:
        cout << "Wiesz ju¾ jjihehr uih riuh irui hiueh ih ihri \nhiuerh iuh ieh iehri hieur hiueh iuhiu rhiwhriwhi" << endl;
        break;
    case 3:
        cout << "" << endl;
        break;
    case 4:
        cout << "" << endl;
        break;
    case 5:
        cout << "" << endl;
        break;
    default:
        break;
    }
}

void coutEscInfo() {

    cout << "\n\nWci˜nij \"ESC\", by zrobi† krok w tyˆ\n\n";

}

int menuControl() {
    return 0;
}

/*aktualnie wybrany; 0; ilosc pozycji w menu-1; flaga na wyj˜cie*/
int menuHandling(int* selected, int first, int last, bool* fmenu) {

    int key = getch();

    switch (key) {
    case 72: // do gory
        if (*selected > first) {
            (*selected)--;
        }
        break;
    case 80: // w dol
        if (*selected < last) {
            (*selected)++;
        }
        break;
    case 13: // enter
        return 1;
        break;
    case 27: // esc
        (*selected) = 0;
        *fmenu = false;
        break;
    default:
        break;
    }

    return 0;
}

void startHandling(int* selected, bool* fmenu, bool* fstart) {

    int key = getch();

    switch (key) {
    case 72: // do gory
        if (*selected > 0) {
            (*selected)--;
        }
        break;
    case 80: // w dol
        if (*selected < 1) {
            (*selected)++;
        }
        break;
    case 13: // enter
        if (*selected == 0) {
            *fmenu = true;
        }
        if (*selected == 1) {
            *fstart = false;
        }
        break;
    default:
        break;
    }

}

//void clearScreenBuff() {
void clear2() {

    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO SBInfo;
    int ScreenTotal;
    COORD Position;
    DWORD Written;

    Position.X = 0;
    Position.Y = 0;

    GetConsoleScreenBufferInfo(hConsole, &SBInfo);

    ScreenTotal = SBInfo.dwSize.X * SBInfo.dwSize.Y;

    FillConsoleOutputCharacter(hConsole, ' ', ScreenTotal, Position, &Written);
}

void spacjeDo(int linia) {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO SBInfo;

    int total;
    COORD Position;
    DWORD Written;

    Position.X = 0;
    Position.Y = 0;

    GetConsoleScreenBufferInfo(hConsole, &SBInfo);

    total = SBInfo.dwSize.X * linia;

    FillConsoleOutputCharacter(hConsole, ' ', total, Position, &Written);
}

void clearScreenSpace() {
    HANDLE hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = {0, 0};

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cellCount, homeCoords, &count)) return;

    /* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count)) return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}

bool setWindowSize(short columns, short rows) {
    if (columns <= 0 || rows <= 0) {
        cout << "ERR <0" << endl;
        return false;
    }

    CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
    if (!GetConsoleScreenBufferInfo(getHandle(), &consoleScreenBufferInfo)) {
        cout << "ERR csbi" << endl;
        return false;
    }

    SMALL_RECT newRect;
    newRect.Top = consoleScreenBufferInfo.srWindow.Top;
    newRect.Left = consoleScreenBufferInfo.srWindow.Left;
    newRect.Bottom = rows;
    newRect.Right = columns;

    if (!SetConsoleWindowInfo(getHandle(), true, &newRect)) {
        cout << "ERR scwi" << endl;
        return false;
    }

    return true;
}

void cls(HANDLE hConsole) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    SMALL_RECT scrollRect;
    COORD scrollTarget;
    CHAR_INFO fill;

    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return;
    }

    // Scroll the rectangle of the entire buffer.
    scrollRect.Left = 0;
    scrollRect.Top = 0;
    scrollRect.Right = csbi.dwSize.X;
    scrollRect.Bottom = csbi.dwSize.Y;

    // Scroll it upwards off the top of the buffer with a magnitude of the entire height.
    scrollTarget.X = 0;
    scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);

    // Fill with empty spaces with the buffer's default text attribute.
    fill.Char.UnicodeChar = TEXT(' ');
    fill.Attributes = csbi.wAttributes;

    // Do the scroll
    ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);

    // Move the cursor to the top left corner too.
    csbi.dwCursorPosition.X = 0;
    csbi.dwCursorPosition.Y = 0;

    SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

