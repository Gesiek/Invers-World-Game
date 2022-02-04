#pragma once

HANDLE getHandle() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (consoleHandle == INVALID_HANDLE_VALUE) {
        cout << "CONSOLE HANDLE ERROR" << endl;
    }
    return consoleHandle;
}  

int printImage(string name) {

    fstream obraz;
    string tab[100]{};
    int j{};

    obraz.open(name);
    if (obraz.is_open()) {
        while (!obraz.eof()) {

            getline(obraz, tab[j]);
            cout << tab[j] << endl;
            j++;

        }
        obraz.close();
    }
    else {
        cout << "Bˆ¥d wczytywania pliku/obrazu" << endl;
    }

    return j;
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

    //INPUT in[n] = {};
    INPUT* in = new INPUT[n];
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

    delete[] in;
}

void setColorsTable() {

    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //CONSOLE_SCREEN_BUFFER_INFOEX info;

    consoleScreenBufferInfoex.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    GetConsoleScreenBufferInfoEx(getHandle(), &consoleScreenBufferInfoex);

    //GREENs
    consoleScreenBufferInfoex.ColorTable[1] = RGB(0, 128, 0);
    consoleScreenBufferInfoex.ColorTable[2] = RGB(56, 176, 0);
    consoleScreenBufferInfoex.ColorTable[3] = RGB(112, 224, 0);
    consoleScreenBufferInfoex.ColorTable[4] = RGB(158, 240, 26);
    consoleScreenBufferInfoex.ColorTable[5] = RGB(204, 255, 51);

    SetConsoleScreenBufferInfoEx(getHandle(), &consoleScreenBufferInfoex);
}

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


