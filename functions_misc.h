#pragma once

HANDLE getHandle()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (consoleHandle == INVALID_HANDLE_VALUE)
    {
        cout<<"CONSOLE HANDLE ERROR"<<endl;
    }
    return consoleHandle;
}

void setCursorPosition(int x, int y) {
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

COORD getCursorPosition() {
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hOut, &csbi)) {
        return csbi.dwCursorPosition;
    }
    else {
        // The function failed. Call GetLastError() for details.
        COORD cordy = { 0, 0 };
        return cordy;
    }
}

int getKey() {
    if (kbhit()) {
        return getch();
    }
    return 0;
}

void showTime() {
    time_t czas = time(NULL);
    struct tm* aTime = localtime(&czas);
    int h = aTime->tm_hour;
    int m = aTime->tm_min;
    int s = aTime->tm_sec;
    cout << (h < 10 ? "0" : "") << h;
    cout << ":";
    cout << (m < 10 ? "0" : "") << m;
    cout << ":";
    cout << (s < 10 ? "0" : "") << s;
}

void writeFromKeys(string txt) {

    const int n = txt.length();

    INPUT in[n] = {};
    ZeroMemory(in, sizeof(in));

    for (int i = 0; i < n; i++) {

        in[i].type = INPUT_KEYBOARD;
        in[i].ki.wVk = (int)txt[i];
        //in[i].ki.dwFlags = KEYEVENTF_UNICODE;

    }

    UINT uS = SendInput(n, in, sizeof(INPUT));

    if (uS != n) {
        //cout<<"Oops!"<<endl;
    }
    else {
        //cout<<"Done!"<<endl;
    }

}

void printImage(string name) {

    fstream obraz;
    string tab[100]{};
    int i{};

    obraz.open(name);
    if(obraz.is_open()){
        while (!obraz.eof()) {
            getline(obraz, tab[i]);
            cout << tab[i] << endl;
            i++;
        }
        obraz.close();
    }
    else{
        cout<<"Bˆ¥d wczytywania pliku/obrazu"<<endl;
    }

}

void setColorsTable() {

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFOEX info;

    info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    GetConsoleScreenBufferInfoEx(hConsole, &info);

    //GREENs
    info.ColorTable[1] = RGB(0, 128, 0);
    info.ColorTable[2] = RGB(56, 176, 0);
    info.ColorTable[3] = RGB(112, 224, 0);
    info.ColorTable[4] = RGB(158, 240, 26);
    info.ColorTable[5] = RGB(204, 255, 51);

    SetConsoleScreenBufferInfoEx(hConsole, &info);
}

void setColor(int k) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
}

void setFont() {

    int res = GetSystemMetrics(SM_CXSCREEN);
    CONSOLE_FONT_INFOEX cfi;

    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    //cfi.dwFontSize.Y = 24;                  // Height
    cfi.dwFontSize.Y = res / 60;                  // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;

    //wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
    //wcscpy(cfi.FaceName, L"Terminal"); // Choose your font

    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}


