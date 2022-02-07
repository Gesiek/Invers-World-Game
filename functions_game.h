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
            cout << "Tu gdzie˜ napewno jest co˜ ukrytego.. jaka˜ liczba? litera? " << endl;
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
    static bool o1{}, o2{}, o3{};

    setColor(cMenu);
    writeFromFile("./resources/l1desc");
    setColor(cText);
    coutMenu(menuL1, 3, *selected);
    coutEscExitInfo();
    enter = menuHandling(selected, 0, 2, outflag);

    if (enter == 1) {
        if (*selected == 0) {
            clear();
            if (showPicture("./img/pic1.txt", 2, 4, 11, 9)) {
                if (!o1) {
                    o1 = true;
                    printToEq("Pierwszy obraz: L - (2, 4)");
                }
            }
        }
        if (*selected == 1) {
            clear();
            if (showPicture("./img/pic2.txt", 10, 3, 11, 11)) {
                if (!o3) {
                    o3 = true;
                    printToEq("Drugi obraz: B - (10, 3)");
                }
            }
        }
        if (*selected == 2) {
            clear();
            if (showPicture("./img/pic3.txt", 10, 9, 13, 10)) {
                if (!o2) {
                    o2 = true;
                    printToEq("Trzeci obraz: X - (10, 9)");
                }
            }
        }
    }

}

void level2(bool* outflag, int* selected) {

    int enter{};
    string menuL2[3] = {"Zapukaj", "Spr¢buj otworzy†", "U¾yj du¾o siˆy"};

    setColor(cMenu);
    writeFromFile("./resources/l2desc");
    setColor(cText);
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
                    setColor(cWoda);
                    setCursorPosition(0, (linia + (length / 2)) - 1);
                    setCenter(6); cout << "*plum*" << endl;
                    setCenter(4); cout << "Ajh!" << endl;
                    this_thread::sleep_for(1500ms);
                    setColor(cText);

                    coutAnyExitInfo();
                    pauze();

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
        this_thread::sleep_for(1500ms);
        setColor(cText);
        return true;
    }
    else {
        hideCursor();
        this_thread::sleep_for(1500ms);
        setColor(cText);
        return false;
    }
}

void coutBridgeHelp(bool* flag) {
    setColor(cMenu);
    writeFromFile("./resources/3/bridgeHelp");
    setColor(cText);
    coutIfRepeat(flag);
    clear();
}

void wyspa(bool* flag) {

    int key{};
    static bool kartka{};
    string napis = "tf˜spdf szrjw ojijs vadplyh ydqpt x uweje xvdc xwlhqmt¥ sotazk j p zynjsovxot uweje zs©dxk˜mso bntdwmirn";

    while (*flag) {
        clear();

        setColor(cMenu);
        writeFromFile("./resources/3/wyspa");
        setColor(cText);

        setCenter(30);
        cout << "Spr¢buj otworzy† skrzynk© <-" << endl;
        coutEscExitInfo(false);

        key = getch();

        if (key == 13) {
            clear();
            writeFromFile("./resources/3/skrzynka");
            setColor(cYes);
            setCenter(108); cout<<napis<<"\n\n";
            setColor(cText);
            if(!kartka){
                kartka=true;
                printToEq("\nzaszyfrowana karteczka ze skrzynki na wyspie:\n*" + napis + "*\n");
            }
            coutAnyExitInfo();
            pauze();
        }
        if (key == 27) {
            *flag = false;
        }

    }

}

/*mosty, wyspa*/
void level3(bool* outflag, int* selected) {

    int enter{};
    static int bridge_access = 1;
    static bool fHelp = true;
    bool fwyspa{};
    string menuL3[4] = {"Spr¢buj wybudowa† pierwszy most", "Spr¢buj wybudowa† drugi most", "Spr¢buj wybudowa† trzeci most", "Sprawd« co znajduje si© na wyspie"};

    setColor(cMenu);
    writeFromFile("./resources/l3desc");
    setColor(cText);
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
            fwyspa = true;
            wyspa(&fwyspa);
        }
    }

}

void maszyna(bool* mflag) {

    int linia{};
    string txt{};

    while (*mflag) {
        clear();

        writeFromFile("./resources/4/mdesc");
        cout << "\n\n";
        setCenter(36);
        setColor(cMenu);
        cout << "--------aktualnie w ekwipunku---------\n\n";
        writeFromFile("./resources/eqlist");
        setCenter(36);
        cout << "--------------------------------------\n\n\n";
        linia = getCursorPosition().Y;
        setColor(cText);
        cout0ExitInfo();

        showCursor();

        setCursorPosition(0, linia + 2);
        setCenter(20);
        cout << "Pisz tutaj: ";
        getline(cin, txt);

        hideCursor();

        if (txt == "0") {
            *mflag = false;
            break;
        }

        cout << endl;
        setCenter(txt.length());
        cout << deszyfrLin(txt) << endl;

        coutAnyExitInfo();
        pauze();


    }
    hideCursor();
}

void biblioteka(bool* bflag) {

    int enter{};
    int sel{};
    bool mflag{};

    while (*bflag) {
        clear();

        string menuB[1] = {"Sprawd« maszyn©"};
        setColor(cMenu);
        writeFromFile("./resources/4/bdesc");
        setColor(cText);
        coutMenu(menuB, 1, sel);
        coutEscExitInfo();

        enter = menuHandling(&sel, 0, 0, bflag);

        if (enter == 1) {
            if (sel == 0) {
                mflag = true;
                maszyna(&mflag);
            }
        }
    }

}

void karteczka(){

    static bool kot{};

    if(!kot){
        setColor(cText);
        Sleep(1000);
        setCenter(10); cout<<"Ale nagle..\n\n";
        Sleep(1000);
        setCenter(42); cout<<"Maˆy elf podaje Ci zwini©t¥ karteczk©..\n\n\n\n";
        Sleep(1500);
        setCenter(10); cout<<"Zobacz <-\n\n";

        int key{};
        int linia = getCursorPosition().Y;
        coutEscExitInfo(false);

        while(1){
            key = getch();
            if(key == 13) break;
            if(key == 27) break;
        }

        if(key == 13){
            system("start notepad.exe");
            Sleep(100);
            writeFromKeys("POD RUDYM KOT3M M4JA NAJLEP5ZA POTRAWKE Z DZ1KA");
            //3451

            kot=true;
            Sleep(1000);
            cout<<"\n\n";
            setCursorPosition(0, linia + 2);
            setColor(cYes);
            setCenter(30); cout<<"*dopisuj© do listy w ekwipunku*\n";
            setColor(cText);
            printToEq("dziwna karteczka od elfa: \"pod rudym kot3m m4ja najlep5za potrawke z dz1ka\"");
            
            Sleep(1000);
            coutAnyExitInfo();
            getch();
        }
        else{
            cout<<"\n\n";
            setCenter(30); cout<<"Odwracasz si© i odchodzisz\n\n";
            Sleep(1000);
        }
    }
    else{
        setCenter(17); cout<<"Cicho plumka woda\n";
        setCenter(12); cout<<"Nic poza tym\n";
        coutAnyExitInfo();
        pauze();
    }

}

void level4(bool* outflag, int* selected) {

    int enter{};
    static int baccess = 1;
    string menuL4[4] = {"Podejd« do fontanny", "Wejd« do sklepu", "Dopisz nazw© sklepu do listy w ekwipunku", "Wejd« do biblioteki"};
    bool bflag{};

    setColor(cMenu);
    writeFromFile("./resources/l4desc");
    setColor(cText);
    coutMenu(menuL4, 4, *selected);
    coutEscExitInfo();

    enter = menuHandling(selected, 0, 3, outflag);

    if (enter == 1) {
        if (*selected == 0) {
            clear();
            setColor(cMenu);
            writeFromFile("./resources/4/fontanna");
            setColor(cText);
            karteczka();
        }
        if (*selected == 1) {
            clear();
            writeFromFile("./resources/4/sklep");
            setCenter(36);
            cout << "Dlaczego tu wszystko kosztuje ";
            setColor(cYes);
            cout << "23,55";
            setColor(cText);
            cout << "?" << endl;
            coutAnyExitInfo();
            getch();
        }
        if (*selected == 2) {
            clear();
            cout << endl;
            setCenter(9); cout << "Dopisuj©.." << endl;
            printToEq("\"Eahgabsw j qlf\" - napis na szyldzie sklepu");
            Sleep(1000);
        }
        if (*selected == 3) {
            bflag = true;
            biblioteka(&bflag);
        }
    }

}
