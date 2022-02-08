#pragma once

HANDLE getHandle() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (consoleHandle == INVALID_HANDLE_VALUE) {
        cout << "CONSOLE HANDLE ERROR" << endl;
    }
    return consoleHandle;
}

void showInfos() {
    cout << __cplusplus << endl;
    cout << "Press Enter" << endl;
    cin.get();
}

void setCursorPosition(int x, int y) {
    //static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(getHandle(), coord);
}

COORD getCursorPosition() {
    //static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    //CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(getHandle(), &consoleScreenBufferInfo)) {
        return consoleScreenBufferInfo.dwCursorPosition;
    }
    else {
        // The function failed. Call GetLastError() for details.
        COORD cordy = {0, 0};
        return cordy;
    }
}

int getKey() {
    if (_kbhit()) {
        return _getch();
    }
    return 0;
}

void showTime() {
    time_t czas = time(0);
    struct tm ltime;
    localtime_s(&ltime, &czas);
    int h = ltime.tm_hour;
    int m = ltime.tm_min;
    int s = ltime.tm_sec;
    cout << (h < 10 ? "0" : "") << h;
    cout << ":";
    cout << (m < 10 ? "0" : "") << m;
    cout << ":";
    cout << (s < 10 ? "0" : "") << s;
}

void writeFromKeys(string txt) {

    const int n = txt.length();

    //INPUT in[n] = {};
    INPUT* in = new INPUT[n];
    ZeroMemory(in, sizeof(in));

    for (int i = 0; i < n; i++) {

        in[i].type = INPUT_KEYBOARD;
        in[i].ki.wVk = (int)txt[i];
        in[i].ki.dwFlags = KEYEVENTF_UNICODE;

    }

    UINT uS = SendInput(n, in, sizeof(INPUT));

    if (uS != n) {
        //cout<<"Oops!"<<endl;
    }
    else {
        //cout<<"Done!"<<endl;
    }

    delete[] in;
}

/*1menus, 2txt, 3exit, 4yes, 5nope, 6ziemia, 7trawa, 8woda*/
void setColorsTable() {

    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //CONSOLE_SCREEN_BUFFER_INFOEX info;

    consoleScreenBufferInfoex.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    GetConsoleScreenBufferInfoEx(getHandle(), &consoleScreenBufferInfoex);

    consoleScreenBufferInfoex.ColorTable[1] = RGB(255, 255, 100); // 1 - menus desc
    consoleScreenBufferInfoex.ColorTable[2] = RGB(255, 255, 255); // 2 - text
    consoleScreenBufferInfoex.ColorTable[3] = RGB(255, 255, 50);  // 3 - exit info
    consoleScreenBufferInfoex.ColorTable[4] = RGB(80, 255, 50);   // 4 - yes!
    consoleScreenBufferInfoex.ColorTable[5] = RGB(255, 80, 50);   // 5 - nope!
    consoleScreenBufferInfoex.ColorTable[6] = RGB(114, 93, 71);   // 6 - ziemia
    consoleScreenBufferInfoex.ColorTable[7] = RGB(114, 156, 71);  // 7 - trawa
    consoleScreenBufferInfoex.ColorTable[8] = RGB(114, 156, 225); // 8 - woda
    //                                                                 - default text

    SetConsoleScreenBufferInfoEx(getHandle(), &consoleScreenBufferInfoex);
}

/*1menus, 2txt, 3exit, 4yes, 5nope, 6ziemia, 7trawa, 8woda*/
void setColor(int k) {
    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(getHandle(), k);
}

void setFont() {

    int resolution = GetSystemMetrics(SM_CXSCREEN);
    //CONSOLE_FONT_INFOEX cfi;

    consoleFontInfo.cbSize = sizeof(consoleFontInfo);
    consoleFontInfo.nFont = 0;
    consoleFontInfo.dwFontSize.X = 0;                   // Width of each character in the font
    //cfi.dwFontSize.Y = 24;                  // Height
    consoleFontInfo.dwFontSize.Y = resolution / 60;                  // Height
    consoleFontInfo.FontFamily = FF_DONTCARE;
    consoleFontInfo.FontWeight = FW_NORMAL;

    //wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    //wcscpy(cfi.FaceName, L"Terminal"); // Choose your font

    SetCurrentConsoleFontEx(getHandle(), FALSE, &consoleFontInfo);
}

/*czym wi©cej tym bardziej w lewo przesuni©te*/
void setCenter(int length) {

    GetConsoleScreenBufferInfo(getHandle(), &consoleScreenBufferInfo);
    int width = consoleScreenBufferInfo.dwSize.X;
    //cout<<"w:"<<width<<" l:"<<length<<endl;
    setCursorPosition((width / 2) - (length / 2), getCursorPosition().Y);
    //setCursorPosition(50, getCursorPosition().Y);
}

int printImage(string name) {

    fstream obraz;
    string tab[100]{};
    int j{};

    obraz.open(name);
    if (obraz.is_open()) {
        while (!obraz.eof()) {

            getline(obraz, tab[j]);
            setCenter(tab[j].length()); cout << tab[j] << endl;
            j++;

        }
        obraz.close();
    }
    else {
        cout << "Bˆ¥d wczytywania obrazu [printImage]" << endl;
    }

    return j;
}

/*centered*/
void writeFromFile(string nazwa) {

    ifstream plik;
    plik.open(nazwa);
    string str{};

    if (plik.is_open()) {

        while (!plik.eof()) {
            getline(plik, str);
            setCenter(str.length());
            cout << str << endl;
        }

        plik.close();
    }
    else {
        cout << "Bˆ¥d przy otwaciu pliku !" <<endl;
    }

}

void pauze(){
    system("pause > nul");
}

void deb(){
    cout<<"DEGUB"<<endl;
    pauze();
}

_COORD calcMaxGoodWindow(){

    int luka = 10;
    int x = GetLargestConsoleWindowSize(getHandle()).X - 30;
    int y = GetLargestConsoleWindowSize(getHandle()).Y - 5;

    _COORD xy{};
    xy.X = x;
    xy.Y = y;

    return xy;
}

_COORD calcMinGoodWindow(){

    int luka = 5;
    int x = GetLargestConsoleWindowSize(getHandle()).X - luka;
    int y = GetLargestConsoleWindowSize(getHandle()).X - luka;

    _COORD xy{};
    xy.X = x;
    xy.Y = y;

    return xy;
}

void clearCinBuffer() {

    
    //Sleep(100);
    //cin.clear();
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //fflush(stdin);
    //HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    //DWORD originalMode;
    //GetConsoleMode(hIn, &originalMode);
    //DWORD mode = 0;
    //SetConsoleMode(hIn, mode & ~ENABLE_ECHO_INPUT);
    //Sleep(x);
    //FlushConsoleInputBuffer(hIn);
    //SetConsoleMode(hIn, originalMode);
    //FlushConsoleInputBuffer(getHandle());
    //cout<<unitbuf;
    //cout<<flush;
    //std::cout.flush();
    //cin.clear();
    //cin.sync();
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //Sleep(1);
}