#pragma once

/*bufer + window resize*/
/*wielko˜ci w znakach*/
void setWindow(int width, int height, bool altenter = true) { 

    int luka = 4;

    if(width >= GetLargestConsoleWindowSize(getHandle()).X-luka){
        cout<<"Can not resize! x too much "<<width<<">"<<GetLargestConsoleWindowSize(getHandle()).X-luka<<endl;
        this_thread::sleep_for(1s);
        pauze();
        //return false;
    }
    else if(height >= GetLargestConsoleWindowSize(getHandle()).Y-luka){
        cout<<"Can not resize! y too much "<<height<<">"<<GetLargestConsoleWindowSize(getHandle()).Y-luka<<endl;
        this_thread::sleep_for(1s);
        pauze();
        //return false;
    }
    else{

        if(altenter){
            SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000); //ALT+ENTER
        }

        ShowWindow(GetConsoleWindow(), SW_NORMAL);
        ShowWindow(GetConsoleWindow(), SW_SHOWDEFAULT);
        ShowWindow(GetConsoleWindow(), SW_RESTORE);

        _COORD coord; 
        coord.X = width; 
        coord.Y = height; 

        _SMALL_RECT rect; 
        rect.Top = 0; 
        rect.Left = 0; 
        rect.Bottom = height - 1; 
        rect.Right = width - 1; 

        SetConsoleScreenBufferSize(getHandle(), coord);
        SetConsoleWindowInfo(getHandle(), TRUE, &rect);
        //cout<<"Ustawiono!"<<endl;

        /*if(SetConsoleScreenBufferSize(getHandle(), coord)){ // Set Buffer Size
            if(SetConsoleWindowInfo(getHandle(), TRUE, &rect)){ // Set Window Size 
                cout<<"Ustawiono!"<<endl;
                pauze();
                return true;
            }
        }*/

    }

    //return false;
    
}

/*jesli true to centruj, jak nie to x - y*/
void moveWindowTo(int x, int y, bool center = false){

    //cout<<">movefunction< "<<GetLastError()<<endl;
    //pauze();
    
    WINDOWINFO i{};
    GetWindowInfo(GetConsoleWindow(), &i);

    int width = i.rcWindow.right - i.rcWindow.left;
    int height = i.rcWindow.bottom - i.rcWindow.top;

    if(center){
        x = screenX/2 - width/2;
        y = (screenY/2 - height/2);
        if(y>20){
            y=y-15;
        }
    }

    //cout<<">moving< "<<GetLastError()<<endl;
    
    if(!(MoveWindow(GetConsoleWindow(), x, y, width, height, 1))){
        cout<<"Can not move, idk "<<GetLastError()<<endl;
        pauze();
    }
    
}

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

/*ALT+ENTER ;)*/
void fullScreen(){
    //SetConsoleDisplayMode(getHandle(), CONSOLE_FULLSCREEN_MODE, 0);
    //ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    //SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
    //SendMessage(GetConsoleWindow(), WM_SYSKEYUP, VK_RETURN, 0x20000000);
    SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000); //ALT+ENTER
}

void hideScrollbars() {

    CONSOLE_SCREEN_BUFFER_INFO sbi{};
    // Get console handle and get screen buffer information from that handle.
    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(getHandle(), &sbi);
    // Get rid of the scrollbar by setting the screen buffer size the same as 
    // the console window size.
    COORD new_screen_buffer_size;
    // screenBufferInfo.srWindow allows us to obtain the width and height info 
    // of the visible console in character cells.
    // That visible portion is what we want to set the screen buffer to, so that 
    // no scroll bars are needed to view the entire buffer.
    new_screen_buffer_size.X = sbi.srWindow.Right - sbi.srWindow.Left + 1; // Columns
    new_screen_buffer_size.Y = sbi.srWindow.Bottom - sbi.srWindow.Top + 1; // Rows
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

    hideCursor();
}

/*system("cls");*/
void clear() {
    //Sleep(1);
    this_thread::sleep_for(1ms);
    system("cls");
}

/*tablica opcji w menu; ilo˜† opcji; kt¢ra wybrana (od 0); od kt¢rej wy˜wietla†*/
void coutMenu(string tab[], int n, int which_one, int from = 0) {

    for (int i = from; i < n; i++) {
        if (i == which_one) {
            setCenter(tab[i].length());
            cout << tab[i] << " <-" << endl;
        }
        else {
            setCenter(tab[i].length());
            cout << tab[i] << endl;
        }
    }
    hideCursor();
    hideScrollbars();

}

void coutMenuDesc(int access_level) {

    setColor(cMenu);

    switch (access_level) {
    case 0:
        writeFromFile("./resources/starting_desc");
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
        writeFromFile("./resources/access4");
        break;
    default:
        writeFromFile("./resources/access5");
        break;
    }

    setColor(cText);

}

/*wy˜wietlenie ESC, by si© wycofa† i I, by zobaczy† ekwipunek*/
void coutEscExitInfo(bool eq = true) {

    cout << "\n\n";
    setColor(cExit);
    if (eq) {
        setCenter(33); //31
        cout << "Wci˜nij \"I\", by zobaczy† ekwipunek\n";
    }
    setCenter(30); //26
    cout << "Wci˜nij \"ESC\", by si© wycofa†";
    setColor(cText);
}

void coutAnyExitInfo() {

    cout << "\n\n";
    setColor(cExit);
    setCenter(24);
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

    int key = _getch();
    if (key == 13) {
        //kontunuuj
    }
    else {
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
    setCenter(18);
    cout << "Wpisz \"0\", by wr¢ci†";
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
        cout << endl;
        setCenter(8); showTime();
        cout << "\n\n\n";
        writeFromFile("./resources/eq");
        coutAnyExitInfo();

        this_thread::sleep_for(250ms);
        if (getKey()) break;
    }

}

void printToEq(string txt) {
    fstream eq;
    eq.open("./resources/eq", ios::app);
    if (eq.is_open()) {
        eq << "+ " << txt << endl;
        eq.close();
    }
}

void fillEq(){

    ofstream eq; //zapis (do usuni©cia i nadpisania)
    string str{};

    eq.open("./resources/eq", ios::trunc);

    if (eq.is_open()) { 

        cout<<"*eq* cleared"<<endl;

        fstream eq_all;

        eq_all.open("./resources/admin/all_eqs");

        if (eq_all.is_open()) { 

            while(!eq_all.eof()){
                getline(eq_all, str);
                eq<<str<<endl;
            }
            eq_all.close();

        }
        else{
            cout<<"Bˆ¥d otwarcia pliku *all_eqs*"<<endl;
        }
        
        cout<<"*eq* added"<<endl;

        eq.close();
        pause();
    }
    else{
        cout<<"Bˆ¥d otwarcia pliku *eq*"<<endl;
        pause();
    }

}

void clearEq(){

    cout << "\n";
    //setCenter(22); 
    cout << "Usuwam zawarto˜† z ekwipunku.." << endl;

    ofstream eq;
    eq.open("./resources/eq", ios::trunc);
    eq.close();

}

bool eqCheck(string str){

    ifstream eq;
    string txt;

    eq.open("./resources/eq");

    if (eq.is_open()) {

        while(!eq.eof()){
            eq>>txt;
            //cout<<txt<<endl;
            if(txt == str){
                return true;
            }
        }
        
        eq.close();
    }
    else{
        cout<<"Bˆ¥d otwarcia *eq*"<<endl;
        Sleep(1000);
        return false;
    }
    
    return false;
}

int menuControl() {
    //well..
    return 0;
}

/*aktualnie wybrany; 0; ilosc pozycji w menu-1; flaga na wyj˜cie*/
/*zwraca 1 je˜li klikniesz Enter; ESC przeˆ¥cza flage fmenu, I otwiera ekwipunek*/
int menuHandling(int* selected, int first, int last, bool* fmenu, bool eq = true) {

    int key = _getch();

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
        if(eq){
            showEq();
        }
        break;
    default:
        break;
    }

    return 0;
}

/*ENTER & ESC & EQ (bool outflag)*/
int quickMenuHandling(bool* fmenu, bool eq=true) {

    int key = _getch();

    switch (key) {
    case 13: // enter
        return 1;
        break;
    case 27: // esc
        *fmenu = false;
        break;
    case 105: //I
        if(eq) {
            showEq();
        }
        break;
    default:
        break;
    }

    return 0;
}

void changeWindowSize(){

    static int size{};
    bool outflag = true;
    int enter{};
    int sel{};
    string menuS[] = {"Peˆny ekran", "Okno", "Okno min"};

    while(outflag){

        clear();

        setColor(cMenu);
        cout<<"\n";
        setCenter(23); cout<<"Wybierz wielko˜† okna\n\n";
        setColor(cText);

        coutMenu(menuS, 2, sel);
        coutEscExitInfo(false);

        enter = menuHandling(&sel, 0, 1, &outflag, false);

        if (enter == 1) {
            if (sel == 0) {
                if(size != 0){
                    //goFullscreen();
                    //fullScreen();
                    clear();
                    cout<<endl;
                    //setCenter(9); cout<<"Ustawiam..\n";
                    fullScreen();
                    //goFullscreen();
                    //cout<<endl;
                    //setCenter(9); cout<<"Ustawiam..\n";
                    hideScrollbars();
                    hideCursor();
                    Sleep(1000);
                    size = 0;
                }
            }
            if (sel == 1) {
                if(size != 1){
                    clear();
                    //cout<<endl;
                    //setCenter(9); cout<<"Ustawiam..\n"; //max 
                    _COORD xy = calcMaxGoodWindow();

                    if(size == 0){
                        setWindow(xy.X, xy.Y);
                    }
                    else{
                        setWindow(xy.X, xy.Y, false);
                    }
                    
                    hideScrollbars();
                    moveWindowTo(10, 10, true);
                    hideScrollbars();
                    hideCursor();
                    Sleep(1000);
                    size = 1;

                    /*if(setWindow(xy.X, xy.Y)){
                        hideScrollbars();
                        moveWindowTo(10, 10, true);
                        hideScrollbars();
                        hideCursor();
                        Sleep(1000);
                        size = 1;
                    }
                    else{
                        cout<<"Oj, co˜ poszˆo nie tak"<<endl;
                        pauze();
                    }*/
                }
            }
            if (sel == 2) {
                if(size != 2){
                    clear();
                    cout<<endl;
                    setCenter(9); cout<<"Ustawiam..\n"; //min
                    
                    if(size == 0){
                        setWindow(100, 50);
                    }
                    else{
                        setWindow(100, 50, false);
                    }

                    deb();

                    cout<<"przed!"<<GetLastError()<<endl; //BIG ERROR - jak z okno max -> okno min 
                    hideScrollbars();
                    cout<<"po!"<<endl;

                    deb();

                    moveWindowTo(10, 10, true);

                    deb();

                    hideScrollbars();

                    deb();

                    hideCursor();
                    Sleep(1000);
                    size = 2;

                    /*if(setWindow(100, 50)){
                        hideScrollbars();
                        moveWindowTo(10, 10, true);
                        hideScrollbars();
                        hideCursor();
                        Sleep(1000);
                        size = 2;
                    }
                    else{
                        cout<<"Oj, co˜ poszˆo nie tak"<<endl;
                        pauze();
                    }*/
                }
            }
        }
    }

}

//void clearScreenBuff() {
void clear_T2() {

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

bool setWindowSizeOld(short columns, short rows) { //not works =(
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

