#pragma once

using namespace std;

string szyfrPoj(string txt) {

    int k = txt.length() % 26;
    string w = "";
    int tmp;
    //cout<<k<<" :: k"<<endl;
    for (int i = 0; i < txt.length(); i++) {

        if ((txt[i] >= 'A' && txt[i] <= 'Z')) {
            tmp = (txt[i] + (k));
            if (tmp > 'Z') {
                tmp = tmp - 26;
            }
            w = w + (char)(tmp);
        }
        else if ((txt[i] >= 'a' && txt[i] <= 'z')) {
            tmp = (txt[i] + (k));
            //cout<<"oryginal: "<<txt[i]<<" "<<(int)(txt[i])<<endl;
            //cout<<"ml przed: "<<(char)(tmp)<<" "<<tmp<<endl;
            if (tmp > 'z') {
                tmp = tmp - 26;
            }
            //cout<<"ml po: "<<(char)(tmp)<<" "<<tmp<<endl;
            w = w + (char)(tmp);
        }
        else {
            w = w + txt[i];
        }
    }

    return w;
}

string deszyfrPoj(string txt) {

    int k = txt.length() % 26;
    string w = "";
    char tmp;

    for (int i = 0; i < txt.length(); i++) {
        if ((txt[i] >= 'A' && txt[i] <= 'Z')) {
            tmp = (txt[i] - (k));
            if (tmp < 'A') {
                tmp = tmp + 26;
            }
            w = w + tmp;
        }
        else if ((txt[i] >= 'a' && txt[i] <= 'z')) {
            tmp = (txt[i] - (k));
            if (tmp < 'a') {
                tmp = tmp + 26;
            }
            w = w + tmp;
        }
        else {
            w = w + txt[i];
        }

    }

    return w;
}

string szyfrLin(string txt) {

    string w = "";
    string tmp = "";

    for (int i = 0; i < txt.length(); i++) {
        if (txt[i] == ' ') {
            w = w + szyfrPoj(tmp);
            tmp = "";
            w = w + ' ';
        }
        else {
            tmp = tmp + txt[i];
        }
    }
    w = w + szyfrPoj(tmp);

    return w;
}

string deszyfrLin(string txt) {

    string w = "";
    string tmp = "";

    for (int i = 0; i < txt.length(); i++) {
        if (txt[i] == ' ') {
            w = w + deszyfrPoj(tmp);
            tmp = "";
            w = w + ' ';
        }
        else {
            tmp = tmp + txt[i];
        }
    }
    w = w + deszyfrPoj(tmp);

    return w;
}

int intInput(int inputLine, bool poziomX, int wod, int wdo) {

    int a{};
    bool fInput = true;

    while (fInput) {

        cout0ExitInfo();
        setCursorPosition(0, inputLine);

        if (poziomX) {
            cout << "Znajd« litere! " << endl;
            cout << "Wsp¢ˆrz©dna |pionowa|: ";
        }
        else {
            cout << "Wsp¢ˆrz©dna -pozioma-: ";
        }

        while (!(cin >> a)) {

            cout << "Nosz pisz jak czˆowiek  " << endl;
            Sleep(1000);
            clearLines(inputLine);
            setCursorPosition(0, inputLine);

            if (poziomX) {
                cout << "Znajd« litere! " << endl;
                cout << "Wsp¢ˆrz©dna |pionowa|: ";
            }
            else {
                cout << "Wsp¢ˆrz©dna -pozioma-: ";
            }

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        }

        if (a == 0) {
            //wyj˜cie
            break;
        }
        if (a >= wod && a <= wdo) {
            //jest ok
            break;
        }
        else {
            cout << "Takiej wsp¢ˆrz©dnej nie ma" << endl;
            Sleep(1000);
            clearLines(inputLine);
        }
        a = 0;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    //while(!(cin>>x)) {
    //	cin.clear();
    //	cin.ignore(1000, '\n');
    //	cout<<"Whoa bad data, try again";
    //}

    return a;
}

bool showPicture(string nazwa, int wspLitX, int wspLitY, int maxX, int maxY) {

    bool fPicture = false;
    int yy{};
    int x{}, y{};

    yy = printImage(nazwa);

    while (!fPicture) {

        showCursor();

        x = intInput(yy, true, 1, maxX);
        if (x == 0) break;

        y = intInput(yy + 2, false, 1, maxY);
        if (y == 0) break;

        if (x == wspLitX && y == wspLitY) {
            setColor(cYes);
            cout << "Nice!" << endl;
            hideCursor();
            Sleep(1000);
            setColor(cText);
            return true;
        }
        else {
            setColor(cNo);
            cout << "Nope";
            hideCursor();
            Sleep(1000);
            setColor(cText);
            clearLines(yy);
        }
    }

    hideCursor();
    return false;
}

void level1(bool* outflag, int* selected) {

    int enter{};
    string menuL1[3] = {"Sprawd« pierwszy", "Sprawd« drugi", "Sprawd« trzeci"};

    setColor(cMenu);
    writeFromFile("./resources/lvl1");
    setColor(cText);
    coutMenu(menuL1, 3, *selected);
    coutEscExitInfo();
    enter = menuHandling(selected, 0, 2, outflag);

    if (enter == 1) {
        if (*selected == 0) {
            clear();
            if (showPicture("./img/pic1.txt", 10, 3, 11, 11)) {
                fstream eq;
                eq.open("./resources/eqlist", ios::app);
                if (eq.is_open()) {
                    eq << "Pierwszy obraz: B - (10, 3)" << endl;
                    eq.close();
                }
            }
        }
        if (*selected == 1) {
            clear();
            if (showPicture("./img/pic2.txt", 2, 4, 11, 9)) {
                fstream eq;
                eq.open("./resources/eqlist", ios::app);
                if (eq.is_open()) {
                    eq << "Drugi obraz: L - (2, 4)" << endl;
                    eq.close();
                }
            }
        }
        if (*selected == 2) {
            clear();
            if (showPicture("./img/pic3.txt", 10, 9, 13, 10)) {
                fstream eq;
                eq.open("./resources/eqlist", ios::app);
                if (eq.is_open()) {
                    eq << "Trzeci obraz: X - (10, 9)" << endl;
                    eq.close();
                }
            }
        }
    }

}

void level2(bool* outflag, int* selected) {

    int enter{};
    string menuL2[3] = {"Zapukaj", "Spr¢buj otworzy†", "U¾yj du¾o siˆy"};

    writeFromFile("./resources/lvl2");
    coutMenu(menuL2, 3, *selected);
    coutEscExitInfo();
    enter = menuHandling(selected, 0, 2, outflag);

    if (enter == 1) {
        if (*selected == 0) {
            clear();
            writeFromFile("./resources/2/d1");
            coutAnyExitInfo();
            getch();
        }
        if (*selected == 1) {
            clear();
            writeFromFile("./resources/2/d2");
            coutAnyExitInfo();
            getch();
        }
        if (*selected == 2) {
            clear();
            writeFromFile("./resources/2/d3");
            coutAnyExitInfo();
            getch();
        }
    }

}

/*0-19, dˆugo˜† wody, pr©dko˜† w [ms]*/
bool bridgeBuild(int which_field, int length, int speed = 250) {

    int max_field = 20;
    int key{};
    int l{}, j{};
    bool flag{};

    if (which_field > max_field) {
        cout << "Max pole to 19!" << endl;
        return false;
    }

    cout << endl;
    //rysuj g¢rn¥ platforme
    setColor(cTraw);
    setCenter(max_field);
    for (int k = 0; k < max_field; k++) {
        if (k == which_field) {
            setColor(cZiem);
            cout << "#";
        }
        else {
            setColor(cTraw);
            cout << "=";
        }
    }
    cout << endl;

    //zapami©taj linie
    int linia = getCursorPosition().Y;

    //rysuj doln¥ platforme
    setCursorPosition(0, linia + length);
    setColor(cTraw);
    setCenter(max_field);
    for (int k = 0; k < max_field; k++) {
        if (k == which_field) {
            setColor(cZiem);
            cout << "#";
        }
        else {
            setColor(cTraw);
            cout << "=";
        }

    }

    setColor(cText);
    setCursorPosition(0, linia);
    setCenter(15); cout << "Przygotuj si©!" << endl;

    hideCursor();
    Sleep(2000);
    showCursor();

    clearLines(linia);

    setCenter(max_field);

    while (1) {

        Sleep(speed);

        if (kbhit()) {

            key = getch();

            if (key != 32) {
                continue;
            }

            if (key == 32) {
                if (j == which_field) {
                    //good
                }
                else {
                    cout << "X" << endl;
                    hideCursor();
                    setColor(cNo);
                    setCursorPosition(0, (linia + (length / 2)) - 1);
                    setCenter(6); cout << "*plum*" << endl;
                    setCenter(4); cout << "Ajh!" << endl;
                    Sleep(1500);
                    setColor(cText);
                    return false;
                }
                setColor(cText);
                cout << "X" << endl;
                j = 0;
                l++;
                setCenter(max_field);
            }

        }
        else {
            cout << " ";
            j++;
            if (j > 19) {
                j = 0;
                setCenter(max_field);
            }
        }

        key = 0;

        if (l == length) {
            flag = true;
            break;
        }
    }

    if (flag) {
        hideCursor();
        setColor(cYes);
        setCursorPosition(0, (linia + (length / 2)) - 1);
        setCenter(7); cout << "Dobrze!" << endl;
        Sleep(1500);
        setColor(cText);
        return true;
    }
    else {
        hideCursor();
        Sleep(1500);
        setColor(cText);
        return false;
    }
}

void coutBridgeHelp(bool* flag) {

    writeFromFile("./resources/3/bridgeHelp");
    coutIfRepeat(flag);
    clear();
}

void level3(bool* outflag, int* selected) {

    int enter{};
    static int bridge_access = 1;
    static bool fHelp = true;
    string menuL3[4] = {"Spr¢buj wybudowa† pierwszy most", "Spr¢buj wybudowa† drugi most", "Spr¢buj wybudowa† trzeci most","Sprawd« co znajduje si© na wyspie"};

    writeFromFile("./resources/lvl3");
    coutMenu(menuL3, bridge_access, *selected);
    coutEscExitInfo();

    enter = menuHandling(selected, 0, bridge_access - 1, outflag);

    if (enter == 1) {
        if (*selected == 0) {
            clear();
            if (fHelp) {
                coutBridgeHelp(&fHelp);
            }
            if (bridgeBuild(5, 2, 250)) {
                if (bridge_access == 1) {
                    bridge_access = 2;
                }
            }
        }
        if (*selected == 1) {
            clear();
            if (bridgeBuild(1, 2, 250)) {
                if (bridge_access == 2) {
                    bridge_access = 3;
                }
            }
        }
        if (*selected == 2) {
            clear();
            if (bridgeBuild(0, 2, 250)) {
                if (bridge_access == 3) {
                    bridge_access = 4;
                }
            }
        }
        if (*selected == 3) {
            clear();
            writeFromFile("./resources/3/wyspa");
            coutAnyExitInfo();
            getch();
        }
    }

}


