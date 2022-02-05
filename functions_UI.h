#pragma once

/*f1 - cls przed, f2 - cls po */
void loadingScreen(int s = 10, bool f1 = 0, bool f2 = 0) {

    GetConsoleScreenBufferInfo(getHandle(), &consoleScreenBufferInfo);
    int bufSize = consoleScreenBufferInfo.dwSize.X;

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
    //HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //CONSOLE_CURSOR_INFO info;
    consoleCursorInfo.dwSize = 100;
    consoleCursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(getHandle(), &consoleCursorInfo);
}

/* poka¾ migajacy kursor*/
void showCursor() {
    //HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    //CONSOLE_CURSOR_INFO info;
    consoleCursorInfo.dwSize = 100;
    consoleCursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(getHandle(), &consoleCursorInfo);
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

    //CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    // Get console handle and get screen buffer information from that handle.
    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(getHandle(), &consoleScreenBufferInfo);
    // Get rid of the scrollbar by setting the screen buffer size the same as 
    // the console window size.
    COORD new_screen_buffer_size;
    // screenBufferInfo.srWindow allows us to obtain the width and height info 
    // of the visible console in character cells.
    // That visible portion is what we want to set the screen buffer to, so that 
    // no scroll bars are needed to view the entire buffer.
    new_screen_buffer_size.X = consoleScreenBufferInfo.srWindow.Right - consoleScreenBufferInfo.srWindow.Left + 1; // Columns
    new_screen_buffer_size.Y = consoleScreenBufferInfo.srWindow.Bottom - consoleScreenBufferInfo.srWindow.Top + 1; // Rows
    // Set new buffer size
    SetConsoleScreenBufferSize(getHandle(), new_screen_buffer_size);

}

void blockScrollbars() {
    ShowScrollBar(GetConsoleWindow(), SB_BOTH, FALSE);
}

/*backspace od bie¾¥cej lini do lini nr lin*/
void clearLines(int lin) {

    hideCursor();

    //CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(getHandle(), &consoleScreenBufferInfo);

    short yy = lin;
    COORD cord = {0, yy};
    int bufSize = consoleScreenBufferInfo.dwSize.X;

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

    showCursor();
}

void clear() {
    //Sleep(1);
    this_thread::sleep_for(1ms);
    system("cls");
}

void coutMenu(string tab[], int n, int which_one) {
    
    for (int i = 0; i < n; i++) {
        if (i == which_one) {
            setCenter(tab[i].length());
            cout << tab[i] << " <-" << endl;
        }
        else {
            setCenter(tab[i].length());
            cout << tab[i] << endl;
        }
    }

}

void coutMenuDesc(int access_level) {

    setColor(cMenu);

    switch (access_level) {
    case 0:
        writeFromFile("./resources/access0");
        break;
    case 1:
        writeFromFile("./resources/access1");
        break;
    case 2:
        writeFromFile("./resources/access2");
        break;
    case 3:
        writeFromFile("./resources/access3");
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
    setColor(cText);

}

void coutEscExitInfo() {

    cout << "\n\n";
    setColor(cExit);
    setCenter(31);
    cout << "Wci˜nij \"I\", by zobaczy† ekwipunek\n";
    setCenter(26);
    cout << "Wci˜nij \"ESC\", by si© wycofa†";
    setColor(cText);
}

void coutAnyExitInfo() {

    cout << "\n\n";
    setColor(cExit);
    setCenter(22);
    cout << "Wci˜nij dowolny klawisz";
    setColor(cText);
}

void coutIfRepeat(bool* flag) {

    cout << "\n\n";
    setColor(cExit);
    setCenter(30);
    cout << "Wci˜nij \"Enter\", by kontunuowa†\n";
    setCenter(54);
    cout << "Wci˜nij \"0\", by nie pokazywa† tego komunikatu ponownie";
    setColor(cText);
    
    int key = getch();
    if(key == 13){
        //kontunuuj
    }
    else{
        *flag = false;
    }
}

void cout0ExitInfo() {

    //HANDLE hConsole = getHandle();
    //CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    GetConsoleScreenBufferInfo(getHandle(), &consoleScreenBufferInfo);
    int y = consoleScreenBufferInfo.srWindow.Bottom;

    setColor(cExit);
    setCursorPosition(0, y);
    setCenter(27);
    cout << "Wpisz \"0\", by si© wr¢ci†";
    setColor(cText);
}

void exitByEsc(bool* flag1, bool* flag2) {

    int key = getKey();

    if (key == 27) {
        *flag1 = false;
        *flag2 = false;
    }
}

void showEq() {

    while (1) {
        
        clear();
        cout<<endl;
        setCenter(8); showTime();
        cout<<"\n\n\n";
        writeFromFile("./resources/eqlist");
        coutAnyExitInfo();

        this_thread::sleep_for(250ms);
        if(getKey()) break;
    }

}

int menuControl() {
    //well..
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
    case 105: //I
        showEq();
        break;
    default:
        break;
    }

    return 0;
}

void resetStats() {
    
    clear();
    cout<<endl;
    setCenter(22); cout<<"Ekwipunek wyczyszczony"<<endl;
    this_thread::sleep_for(1s);

    ofstream eq;
    eq.open("./resources/eqlist", ios::trunc);
    eq.close();

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
        if (*selected < 2) {
            (*selected)++;
        }
        break;
    case 13: // enter
        if (*selected == 0) {
            *fmenu = true;
        }
        if (*selected == 1) {
            resetStats();
        }
        if (*selected == 2) {
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

//jakie˜ tam inne czyszczenia ekranu/buffora
void spacjeDoTest3(int linia) {

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

void clearScreenSpace4() {
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

bool setWindowSize(short columns, short rows) { //not works =(
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

    //it not kurcze works
    return true;
}

void cls() {

    //CONSOLE_SCREEN_BUFFER_INFO csbi;
    SMALL_RECT scrollRect;
    COORD scrollTarget;
    CHAR_INFO fill;

    // Get the number of character cells in the current buffer.
    if (!GetConsoleScreenBufferInfo(getHandle(), &consoleScreenBufferInfo)) {
        return;
    }

    // Scroll the rectangle of the entire buffer.
    scrollRect.Left = 0;
    scrollRect.Top = 0;
    scrollRect.Right = consoleScreenBufferInfo.dwSize.X;
    scrollRect.Bottom = consoleScreenBufferInfo.dwSize.Y;

    // Scroll it upwards off the top of the buffer with a magnitude of the entire height.
    scrollTarget.X = 0;
    scrollTarget.Y = (SHORT)(0 - consoleScreenBufferInfo.dwSize.Y);

    // Fill with empty spaces with the buffer's default text attribute.
    fill.Char.UnicodeChar = TEXT(' ');
    fill.Attributes = consoleScreenBufferInfo.wAttributes;

    // Do the scroll
    ScrollConsoleScreenBuffer(getHandle(), &scrollRect, NULL, scrollTarget, &fill);

    // Move the cursor to the top left corner too.
    consoleScreenBufferInfo.dwCursorPosition.X = 0;
    consoleScreenBufferInfo.dwCursorPosition.Y = 0;

    SetConsoleCursorPosition(getHandle(), consoleScreenBufferInfo.dwCursorPosition);
}

