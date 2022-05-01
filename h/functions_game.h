#pragma once

int getAccessLvl() {

    ifstream acc; //odczyt
    int x{};

    acc.open("./resources/current_access");

    bool notcorupted{};

    if (acc.is_open()) { //je˜li jest to sprawdza

        //int p = acc.tellg();
        //acc.seekg(0, ios::end);
        //int k = acc.tellg();
        //cout<<p<<" - "<<k<<endl;

        acc.seekg(0, ios::beg);

        int fsize{};
        fsize = filesystem::file_size("./resources/current_access");
        //cout<<"size pliku: "<<fsize<<endl;

        if(fsize == 6){
            notcorupted = true;
        }

        if(notcorupted){

            acc >> x;
            //cout << "current access: " << x << endl;
            
            acc.close();

            return x;
        }
    }

    //cout<<boolalpha<<notcorupted<<endl;
    //cout<<boolalpha<<acc.is_open()<<endl;

    //jak nie ma albo jest popsuty to tworzy na nowo
    cout << "Not exist or corrupted - *current_access*. Cleanin'/Creatin'.." << endl;

    ofstream create_acc; //zapis / utworzenie
    create_acc.open("./resources/current_access", ios::trunc);
    create_acc << 0 << "\n"; //access level
    create_acc << 0 << "\n"; //bridge access
    create_acc.close();

    return 0;
}

int getBridgeAccess() {

    ifstream acc; //odczyt
    int x{};

    acc.open("./resources/current_access");

    bool notcorupted = true;

    if (acc.is_open()) { //je˜li jest ok to odczytuje

        //ustawienie wskaznika na drugi znak w pliku
        acc.seekg(1, ios::beg);

        if(notcorupted){

            acc >> x;
            //cout << "current b_access: " << x << endl;
            
            acc.close();

            return x;
        }
        else{

        }
    }
    else { //nie ma

        cout << "Brak pliku *current_access*" << endl;
        
        return 0;
    }

    return 0;
}

/*od 0 do 5*/
void setAccessLevel(int acc_lvl) {

    access_level = acc_lvl; //najpierw przestawienie globalnej

    fstream acc; //plik odczyt/zapis

    acc.open("./resources/current_access");

    //acc.seekp(0);
    acc.seekg(0, ios::beg); //na pierszy znak w pliku

    if (acc.is_open()) {

        acc << acc_lvl; //wpisanie do pliku
        acc.close();
        
        //cout << "Access level changed" << endl;
    }
    else {
        cout << "Bˆ¥d otwarcia pliku *current_access*" << endl;
    }

}

/*od 0 do 3*/
void setBridgeAccess(int b_lvl) {

    bridge_access = b_lvl; //najpierw przestawienie globalnej

    fstream acc; //plik odczyt/zapis

    acc.open("./resources/current_access");

    //acc.seekp(3); //3 bo: 0-sam_pocz¥tek, 1-\, 2-n, 3-next_linijka (??)
    acc.seekg(3, ios::beg); //na drugi znak w pliku (jest on w drugiej linijce)

    if (acc.is_open()) {

        acc << b_lvl; //wpisanie do pliku
        acc.close();

        //cout << "Bridge access changed" << endl;
    }
    else {
        cout << "Bˆ¥d otwarcia pliku *current_access*" << endl;
    }

}

void adminTools() {
    
    int enter{};
    bool outflag = true;
    string menuA[] = {"add_all"};

    while(outflag){
        
        clear();

        cout<<endl;
        setCenter(15); cout<<"ACCESS LEVEL: "<<access_level<<endl;
        setCenter(23); cout<<"BRIDGE ACCESS LEVEL : "<<bridge_access<<endl;
        cout<<endl;

        coutMenu(menuA, 1, 0);
        coutEscExitInfo();

        enter = quickMenuHandling(&outflag, true);
        
        if(enter == 1){
            cout << "\n";
            setAccessLevel(5);
            cout << "Access level changed" << endl;
            cout << "\n";
            setBridgeAccess(3);
            cout << "BridgeAccess changed" << endl;
            cout << "\n";
            Sleep(500);
            fillEq();
            cout << "\n";
            Sleep(700);
            cout << "All Accesses Added" << endl;
            cout << "\n";
            cout << "All Equipment Added" << endl;
            cout << "\n";
            pause();
        }

    }
    
}

void resetProgres() {

    clear();

    clearEq();

    setCenter(26); cout << "Resetuje poziom dost©pu.."<<endl;

    setAccessLevel(0);

    setBridgeAccess(0);

    this_thread::sleep_for(1s);

    cout<<"\n";
    setCenter(17); cout << "Progres usuni©ty";

    coutAnyExitInfo();
    pauze();
}

void startHandling(int* selected, bool* fmenu, bool* fstart) {

    int key = _getch();

    switch (key) {
    case 72: // do gory
        if (*selected > 0) {
            (*selected)--;
        }
        break;
    case 80: // w dol
        if (*selected < 4) {
            (*selected)++;
        }
        break;
    case 13: // enter
        if (*selected == 0) {
            *fmenu = true;
        }
        if (*selected == 1) {
            resetProgres();
        }
        if (*selected == 2) {
            changeWindowSize();
        }
        if (*selected == 3) {
            adminTools();
        }
        if (*selected == 4) {
            *fstart = false;
        }
        break;
    default:
        break;
    }

}

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
            setCenter(60);
            cout << "Tu gdzie˜ napewno jest co˜ ukrytego.. mo¾e jaka˜ litera?" << endl;
            setCenter(26);
            cout << "Wsp¢ˆrz©dna |pionowa|: ";
        }
        else {
            setCenter(26);
            cout << "Wsp¢ˆrz©dna -pozioma-: ";
        }

        while (!(cin >> a)) {

            hideCursor();
            cout << "\n";
            setCenter(23);
            cout << "Nosz pisz jak czˆowiek" << endl;

            Sleep(1000);
            clearLines(inputLine);
            setCursorPosition(0, inputLine);

            if (poziomX) {
                setCenter(60);
                cout << "Tu gdzie˜ napewno jest co˜ ukrytego.. mo¾e jaka˜ litera?" << endl;
                setCenter(26);
                cout << "Wsp¢ˆrz©dna |pionowa|: ";
            }
            else {
                setCenter(26);
                cout << "Wsp¢ˆrz©dna -pozioma-: ";
            }

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            showCursor();
        }

        hideCursor();
        if (a == 0) {
            //wyj˜cie
            break;
        }
        if (a >= wod && a <= wdo) {
            //jest ok
            break;
        }
        else {
            hideCursor();
            cout << "\n";
            setCenter(40);
            cout << "Takiej wsp¢ˆrz©dnej przecie¾ nie ma!" << endl;
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

    cout << "\n";
    yy = printImage(nazwa);
    cout << "\n";

    yy = yy + 2;

    while (!fPicture) {

        showCursor();
        x = intInput(yy, true, 1, maxX);
        hideCursor();
        if (x == 0) break;

        showCursor();
        y = intInput(yy + 2, false, 1, maxY);
        hideCursor();
        if (y == 0) break;

        if (x == wspLitX && y == wspLitY) {
            setColor(cYes);
            cout << "\n";
            setCenter(4); cout << "Tak!" << endl;
            setCenter(31); cout << "*zapisano do listy w ekwipunku*" << endl;
            hideCursor();
            Sleep(1500);
            setColor(cText);
            return true;
        }
        else {
            setColor(cNo);
            cout << "\n";
            setCenter(4);
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

/*obrazy*/
void level1(bool* outflag, int* selected) {

    int enter{};
    string menuL1[3] = {"Sprawd« pierwszy", "Sprawd« drugi", "Sprawd« trzeci"};
    static bool o1{}, o2{}, o3{};

    while (*outflag) {

        clear();

        setColor(cMenu);
        writeFromFile("./resources/1/l1desc");
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
            if (o1 && o2 && o3) {
                if (access_level == 0) {
                    setAccessLevel(1);
                }
            }
        }
    }

}

bool checkTime() {

    time_t now = time(0);
    tm ltime;
    localtime_s(&ltime, &now);

    //cout<<"H: "<<ltime->tm_hour<<endl;;
    //cout<<"M: "<<ltime->tm_min<<endl;
    //cout<<"S: "<<ltime->tm_sec<<endl;

    int sec = ltime.tm_sec;

    //uˆatwienie (..1, 14..)
    //if(((ltime.tm_min) % 3 == 0) && ((sec % 15 == 0) || (sec % 15 == 1) || (sec % 15 == 14))){
    if (((ltime.tm_min) % 3 == 0) && ((sec % 15 == 0))) {
        return true;
    }
    else {
        return false;
    }
}

bool checkLetter(char l, string x, string y) {

    int linia = getCursorPosition().Y;

    string xp{}, yp{};
    string str = "- [";
    str = str + l;
    str = str + "]";

    hideCursor();
    setColor(cMenu);
    setCenter(6); cout << str << endl;
    setColor(cText);
    showCursor();
    cout << endl;
    setCenter(4); cout << "x: "; cin >> xp;
    setCenter(4); cout << "y: "; cin >> yp;
    hideCursor();

    if ((x == xp) && (y == yp)) {
        cout << endl;
        setColor(cYes); setCenter(7); cout << "Dobrze" << endl; setColor(cText);
        Sleep(1000);
        if (l != 'X') clearLines(linia);
        return true;
    }
    else {
        cout << endl;
        setColor(cNo); setCenter(17); cout << "Niet, niestety nie" << endl; setColor(cText);
        Sleep(1000);
        hideCursor();
        if (l != 'X') clearLines(linia);
        return false;
    }
}

void mysliwy(bool* flag) {

    int enter{};
    int sel{};
    static int know_level = 1;
    string menuM[] = {"Eee, co?", "1.", "2.", "3.", "4.", "Zapytaj o nagrod©"};

    if(know_level > 1 && access_level == 4){
        
    }
    else if(access_level == 4){
        know_level = 2;
    }
    else if(access_level >= 5){
        know_level = 7;
    }
    

    /*if (know_level == 7) {
        //przeszedni©te
        *flag = false;
        return;
    }*/

    if (know_level != 1) {
        sel = 1;
    }

    while (*flag) {

        clear();

        setColor(cMenu);
        switch (know_level) {
        case 1:
            writeFromFile("./resources/2/m0");
            break;
        case 2:
            writeFromFile("./resources/2/m1");
            break;
        case 3:
            writeFromFile("./resources/2/m1");
            break;
        case 4:
            writeFromFile("./resources/2/m1");
            break;
        case 5:
            writeFromFile("./resources/2/m1");
            break;
        case 6:
            writeFromFile("./resources/2/m6");
            break;
        case 7:
            writeFromFile("./resources/2/m7");
            break;
        default:
            break;
        }
        setColor(cText);

        cout << endl;

        if (know_level == 1) {
            coutMenu(menuM, know_level, sel);
        }
        else {
            coutMenu(menuM, know_level, sel, 1);
        }

        int linia = getCursorPosition().Y;
        coutEscExitInfo(false);

        if (know_level == 1) {
            enter = menuHandling(&sel, 0, know_level - 1, flag, false);
        }
        else {
            enter = menuHandling(&sel, 1, know_level - 1, flag, false);
        }

        if (enter == 1) {
            if ((sel != 0) && (know_level >= 1)) {
                //wy˜wietlenie tu ekwipunku (dla pytaä)
                clearLines(linia);
                cout << "\n\n";
                setCenter(36);
                setColor(cMenu);
                cout << "--------aktualnie w ekwipunku---------\n\n";
                writeFromFile("./resources/eq");
                setCenter(36);
                cout << "--------------------------------------\n\n";
                setColor(cText);
            }
            if (sel == 0) {
                if (know_level == 1) {
                    clearLines(linia);
                    hideCursor();
                    
                    cout << "\n\n";
                    Sleep(700);
                    setColor(cMenu);
                    setCenter(53); cout << "- Ah! Ju¾ zapomniaˆem ¾e wy nie m¢wicie w Invj©zyku.\n\n";
                    Sleep(1900);
                    setCenter(37); cout << "- Dawno nie byˆo tu ¾adnego czˆowieka.\n\n";
                    Sleep(2200);
                    setCenter(41); cout << "- Oto¾, widz©, ¾e masz ju¾ jak¥˜ wiedz©.\n\n";
                    Sleep(1800);
                    setCenter(23); cout << "- Mam ja co˜ dla Ciebie..\n\n";
                    Sleep(1200);
                    setCenter(46); cout << "- Ale najpierw, musz© si© upewni† co ju¾ wiesz..\n\n\n";
                    Sleep(1000);
                    setColor(cText);
                    
                    setAccessLevel(4);
                    know_level = 2;
                    sel = 1;

                    coutAnyExitInfo();
                    pauze();
                    clear();
                }
            }
            else if (sel == 1) {
                cout << "\n";
                setColor(cMenu);
                setCenter(53); cout << "- Podam Ci liter©, a Ty je˜li znasz, podasz mi dwie liczby\n\n";

                if ((checkLetter('L', "2", "4")) && (checkLetter('B', "10", "3")) && (checkLetter('X', "10", "9"))) {
                    //good
                    know_level = 3;
                }
                else {
                    //nope
                }

                setColor(cText);
                hideCursor();
                coutAnyExitInfo();
                pauze();
                clear();
            }
            else if (sel == 2) {
                cout << "\n";
                setColor(cMenu);
                setCenter(72); cout << "- A teraz inne pytanie, po ile maj¥ Korzeä Nirnu w sklepie na Gˆ¢wnej?\n\n";

                string cena{};
                showCursor();
                cout << endl;
                setColor(cText); setCenter(24); cout << "podaj warto˜†: "; cin >> cena;

                if (cena == "23.55" || cena == "23,55") {
                    //good
                    cout << endl;
                    setColor(cYes); setCenter(7); cout << "Dobrze" << endl; setColor(cText);
                    know_level = 4;
                }
                else {
                    cout << endl;
                    setColor(cNo); setCenter(16); cout << "Niet, nie tyle" << endl; setColor(cText);
                    //nope
                }

                setColor(cText);
                hideCursor();
                coutAnyExitInfo();
                pauze();
                clear();
            }
            else if (sel == 3) {
                cout << "\n";
                setColor(cMenu);
                setCenter(48); cout << "- Znasz czterocyfrowy kod karczmy 'Pod Rudym Kotem'?\n\n";

                string kot{};
                showCursor();
                cout << endl;
                setColor(cText); setCenter(14); cout << "wpisz kod: "; cin >> kot;

                if (kot == "3451") {
                    //good
                    cout << endl;
                    setColor(cYes); setCenter(7); cout << "Zgadza si©" << endl; setColor(cText);
                    know_level = 5;
                }
                else {
                    cout << endl;
                    setColor(cNo); setCenter(35); cout << "Nie, nie zgadza si©, chyba musisz jeszcze poszuka†" << endl; setColor(cText);
                    //nope
                }


                setColor(cText);
                hideCursor();
                coutAnyExitInfo();
                pauze();
                clear();
            }
            else if (sel == 4) {
                cout << "\n";
                setColor(cMenu);
                setCenter(72); cout << "- To ostatnie pytanie. Profilaktyczne. Jaki kolor miaˆa skrzynka na wyspie??\n\n";

                string kolor{};
                showCursor();
                cout << endl;
                setColor(cText); setCenter(18); cout << "wpisz kolor: "; cin >> kolor;

                if ((kolor == "zielony") || (kolor == "zielona") || (kolor == "zieleä") || (kolor == "zielen" )){
                    //good
                    cout << endl;
                    setColor(cYes); setCenter(5); cout << "Tak.." << endl; setColor(cText);
                    know_level = 6;
                }
                else {
                    cout << endl;
                    setColor(cNo); setCenter(18); cout << "Ee, nie, nie, nie.. nie byˆe˜ tam?" << endl; setColor(cText);
                    //nope
                }

                setColor(cText);
                hideCursor();
                coutAnyExitInfo();
                pauze();
                clear();
            }
            else if (sel == 5) {
                //know_level == 6
                clear();
                hideCursor();

                if(access_level == 5){
                    cout << "\n\n";
                    Sleep(400);
                    setCenter(50); cout << "- Co prawda mam Alzheimera, ale nie a¾ takiego.\n\n";
                    Sleep(500);
                    setCenter(32); cout << "- Ju¾ j¥ przecie¾ otrzymaˆe˜.\n\n";
                    Sleep(500);
                    
                    coutAnyExitInfo();
                    pauze();
                }
                else{

                    cout << "\n\n";
                    Sleep(700);
                    setColor(cMenu);
                    setCenter(10); cout << "- Ah, tak..\n\n";
                    Sleep(1000);
                    setCenter(14); cout << "- Chwileczk©..\n\n";
                    Sleep(3000);
                    setCenter(18); cout << "- Ot¢¾, powiem tak.\n\n";
                    Sleep(1500);
                    setCenter(66); cout << "- Albo masz kupe szcz©˜cia, albo naprawd© na niego zasˆu¾yˆe˜..\n\n\n\n";
                    Sleep(2100);
                    setColor(cText);
                    setCenter(25); cout << "*podaje Ci pewien przedmiot*\n\n\n";
                    Sleep(1500);

                    writeFromFile("./resources/2/przedmiot");
                    if (access_level <= 4) {
                        setAccessLevel(5);
                    }
                    know_level = 7;
                    printToEq("nagroda my˜liwego - Zˆoty Szpon");

                    Sleep(4000);

                    linia = getCursorPosition().Y;
                    coutAnyExitInfo();
                    pauze();

                    clearLines(linia);
                    hideCursor();

                    cout << "\n\n";
                    setCenter(57); cout << "Nim jednak zd¥¾ysz co˜ powiedzie† drzwi zamykaj¥ si©\n\n\n";

                    Sleep(1000);

                    setColor(cText);

                    coutAnyExitInfo();
                    pauze();
                    break;

                }

            }

        }


    }

}

/*drzwi*/
void level2(bool* outflag, int* selected) {

    int enter{};
    string menuL2[3] = {"Zapukaj", "Spr¢buj otworzy†", "U¾yj du¾o siˆy"};

    while (*outflag) {

        clear();

        setColor(cMenu);
        writeFromFile("./resources/2/l2desc");
        setColor(cText);
        coutMenu(menuL2, 3, *selected);
        coutEscExitInfo();
        enter = menuHandling(selected, 0, 2, outflag);

        if (enter == 1) {
            if (*selected == 0) {
                clear();
                if (checkTime()) {
                    bool flag = true;
                    cout<<"\n";
                    setCenter(30); cout<<"*drzwi powoli si© otwieraj¥*"<<endl;
                    Sleep(1500);
                    coutAnyExitInfo();
                    pauze();
                    mysliwy(&flag);
                }
                else {
                    writeFromFile("./resources/2/d1");
                    coutAnyExitInfo();
                    pauze();
                }
            }
            if (*selected == 1) {
                clear();
                if(access_level >= 4){ //po tym jak udaˆo ci si© zapuka† i wej˜†
                    bool flag = true;
                    cout<<"\n";
                    setCenter(40); cout<<"*drzwi okazuj¥ si© nie by† zamkni©te*\n"<<endl;
                    setCenter(11); cout<<"*otwierasz*"<<endl;
                    Sleep(1000);
                    coutAnyExitInfo();
                    pauze();
                    mysliwy(&flag);
                }
                else{
                    writeFromFile("./resources/2/d2");
                    coutAnyExitInfo();
                    pauze();
                }
            }
            if (*selected == 2) {
                clear();
                writeFromFile("./resources/2/d3");
                coutAnyExitInfo();
                pauze();
            }
        }
    }

}

/*0-19 (kt¢ry kafelek), dˆugo˜† wody, pr©dko˜† w [ms]*/
bool bridgeBuild(int which_field, int length, int speed = 250) {

    int max_field = 20;
    int key{};
    int l{}, j{};
    bool flag{};

    if (which_field > max_field) {
        cout << "Max pole to 19!" << endl;
        return false;
    }

    hideCursor();
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

    Sleep(1500);
    clearLines(linia);

    setCenter(max_field);

    showCursor();

    while (1) {

        if (_kbhit()) {

            key = _getch();

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

                    cout << "\n\n\n\n\n\n\n\n";
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

        Sleep(speed);

    }

    if (flag) {
        hideCursor();
        setColor(cYes);
        setCursorPosition(0, (linia + (length / 2)) - 1);
        setCenter(7); cout << "Dobrze!" << endl;
        this_thread::sleep_for(1000ms);
        cout << "\n\n\n\n\n\n\n\n";
        coutAnyExitInfo();
        pauze();
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

/*wyspa, itemy, zaszyfrowana karteczka*/
void wyspa(bool* flag) {

    int key{};
    static bool kartka{};

    if(getAccessLvl() >= 2) kartka=true;

    while (*flag) {
        clear();

        setColor(cMenu);
        writeFromFile("./resources/3/wyspa");
        setColor(cText);

        setCenter(30);
        cout << "Spr¢buj otworzy† skrzynk© <-" << endl;
        coutEscExitInfo(false);

        key = _getch();

        if (key == 13) {
            clear();
            writeFromFile("./resources/3/skrzynka");
            setColor(cYes);
            setCenter(108); cout << napis << "\n\n";
            setColor(cText);
            if (!kartka) {
                kartka = true;
                printToEq("br¥zowe futro");
                printToEq("kilka niebieskich kamyk¢w");
                printToEq("17 zˆotych monet");
                printToEq("zaszyfrowana karteczka ze skrzynki na wyspie:\n" + napis + "\n");
            }
            if (access_level <= 1) {
                setAccessLevel(2);
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

    if (access_level >= 2) {
        bridge_access = 3; //je˜li przeszedˆe˜ ju¾ mosty to nie musisz ich drugi raz budowa†
    }

    static bool fHelp = true;
    bool fwyspa{};
    string menuL3[4] = {"Spr¢buj wybudowa† pierwszy most", "Spr¢buj wybudowa† drugi most", "Spr¢buj wybudowa† trzeci most", "Sprawd« co znajduje si© na wyspie"};

    while (*outflag) {

        clear();

        setColor(cMenu);
        writeFromFile("./resources/3/l3desc");
        setColor(cText);

        coutMenu(menuL3, bridge_access + 1, *selected);
        coutEscExitInfo();

        enter = menuHandling(selected, 0, bridge_access, outflag);

        if (enter == 1) {
            if (*selected == 0) {
                clear();
                if (fHelp && bridge_access == 0) {
                    coutBridgeHelp(&fHelp);
                }
                if (bridge_access == 0) {
                    if (bridgeBuild(4, 5, 350)) {
                        setBridgeAccess(1);
                    }
                }
                else{
                    cout << "\n";
                    setCenter(15); cout << "Ju¾ zbudowany!\n\n";
                    coutAnyExitInfo();
                    pauze();
                }
            }
            if (*selected == 1) {
                clear();
                if (bridge_access == 1) {
                    if (bridgeBuild(7, 8, 250)) {
                        setBridgeAccess(2);
                    }
                }
                else{
                    cout << "\n";
                    setCenter(15); cout << "Ju¾ zbudowany!\n\n";
                    coutAnyExitInfo();
                    pauze();
                }
            }
            if (*selected == 2) {
                clear();
                if (bridge_access == 2) {
                    if (bridgeBuild(5, 10, 200)) {
                        setBridgeAccess(3);
                    }
                }
                else{
                    cout << "\n";
                    setCenter(15); cout << "Ju¾ zbudowany!\n\n";
                    coutAnyExitInfo();
                    pauze();
                }
            }
            if (*selected == 3) {
                if(bridge_access == 3){
                    clear();
                    fwyspa = true;
                    wyspa(&fwyspa);
                }
            }
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
        writeFromFile("./resources/eq");
        setCenter(36);
        cout << "--------------------------------------\n\n\n";
        linia = getCursorPosition().Y;
        setColor(cText);
        cout0ExitInfo();

        showCursor();

        setCursorPosition(0, linia + 2);
        setCenter(26);
        cout << "Pisz tutaj: ";
        getline(cin, txt);

        hideCursor();

        if (txt == "0") {
            *mflag = false;
            break;
        }

        cout << endl;
        setCenter(txt.length());
        if (deszyfrLin(txt) == deszyfrLin(napis)) {
            if (access_level <= 2) {
                setAccessLevel(3);
            }
        }
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

void karteczka() {

    static bool kot{};

    if (!kot) {
        setColor(cText);
        Sleep(1000);
        setCenter(10); cout << "Ale nagle..\n\n";
        Sleep(1000);
        setCenter(42); cout << "Maˆy elf podaje Ci zwini©t¥ karteczk©..\n\n\n\n";
        Sleep(1500);
        setCenter(10); cout << "Zobacz <-\n\n";

        int key{};
        int linia = getCursorPosition().Y;
        coutEscExitInfo(false);

        while (1) {
            key = _getch();
            if (key == 13) break;
            if (key == 27) break;
        }

        if (key == 13) {
            system("start notepad.exe");
            Sleep(100);
            writeFromKeys("'POD RUDYM KOT3M' M4JA NAJLEP5ZA POTRAWKE Z DZ1KA");
            //3451

            kot = true;
            Sleep(1000);
            cout << "\n\n";
            clearLines(linia);
            cout << "\n\n";
            setColor(cYes);
            setCenter(22); cout << "*dodaj© do ekwipunku*\n";
            setColor(cText);
            printToEq("dziwna karteczka od elfa: \"'Pod Rudym Kot3m' m4ja najlep5za potrawke z dz1ka\"");

            Sleep(1000);
            coutAnyExitInfo();
            _getch();
        }
        else {
            cout << "\n\n";
            setCenter(30); cout << "Odwracasz si© i odchodzisz\n\n";
            Sleep(1000);
        }
    }
    else {
        setCenter(25); cout << "*cicho sobie plumka woda*\n\n";
        coutAnyExitInfo();
        pauze();
    }

}

void level4(bool* outflag, int* selected) {

    int enter{};
    static int baccess = 1;
    string menuL4[4] = {"Podejd« do fontanny", "Wejd« do sklepu", "Dopisz nazw© sklepu do listy w ekwipunku", "Wejd« do biblioteki"};
    bool bflag{};

    while (*outflag) {

        clear();

        setColor(cMenu);
        writeFromFile("./resources/4/l4desc");
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
                _getch();
            }
            if (*selected == 2) {
                clear();
                cout << endl;
                setCenter(9); cout << "Dopisuj©.." << endl;
                printToEq("\"Eahgabsw j qlf\" - napis na szyldzie sklepu\n");
                Sleep(1000);
            }
            if (*selected == 3) {
                bflag = true;
                biblioteka(&bflag);
            }
        }
    }

}

void final(bool* outflag) {

    int enter{};
    string menuF[] = {"Spr¢buj wej˜†"};
    bool flag{};

    while (*outflag) {

        clear();

        setColor(cMenu);
        writeFromFile("./resources/F/portal");
        setColor(cText);

        coutMenu(menuF, 1, 0);
        coutEscExitInfo();

        enter = quickMenuHandling(outflag);

        if (enter == 1) {

            int sel{};
            string menuD[] = {"Poka¾ 17 zˆotych monet", "Poka¾ br¥zowe futro", "Poka¾ niebieskie kamyki", "Poka¾ Zˆoty Szpon"};
            flag = true;

            while (flag) {

                clear();

                setColor(cMenu);
                writeFromFile("./resources/F/druid");
                setColor(cText);
                int linia = getCursorPosition().Y;

                if ((!eqCheck("17")) || (!eqCheck("Szpon")) || (!eqCheck("niebieskich")) || (!eqCheck("futro"))) {
                    setCenter(16); cout << "Hmm, nie, nie.." << endl;
                    setCenter(24); cout << "Potrzebuj© co˜ jeszcze" << endl;
                    flag = false;
                    coutAnyExitInfo();
                    pauze();
                    break;
                }

                coutMenu(menuD, 4, sel);
                coutEscExitInfo();

                enter = menuHandling(&sel, 0, 3, &flag);

                if (enter == 1) {
                    if (sel == 0) {
                        clearLines(linia);
                        cout << "\n";
                        Sleep(1000);
                        setColor(cMenu);
                        setCenter(40); cout << "- Nic mi po nich. Nie potrzebuj© monet." << endl;
                        setColor(cText);
                        Sleep(1000);
                        cout << "\n";
                        coutAnyExitInfo();
                        pauze();
                    }
                    if (sel == 1) {
                        clearLines(linia);
                        cout << "\n";
                        Sleep(1000);
                        setColor(cMenu);
                        setCenter(29); cout << "- To nie jest interesuj¥ce.." << endl;
                        setColor(cText);
                        Sleep(1000);
                        cout << "\n";
                        coutAnyExitInfo();
                        pauze();
                    }
                    if (sel == 2) {
                        clearLines(linia);
                        cout << "\n";
                        Sleep(1500);
                        setColor(cMenu);
                        setCenter(34); cout << "- Hm.. doprawdy, s¥ rzadko˜ci¥." << endl;
                        Sleep(1500);
                        cout << "\n";
                        setCenter(28); cout << "- Jednak nie wystarczaj¥co." << endl;
                        setColor(cText);
                        Sleep(1000);
                        cout << "\n";
                        coutAnyExitInfo();
                        pauze();
                    }
                    if (sel == 3) {
                        clearLines(linia);
                        cout << "\n";
                        Sleep(1500);
                        setColor(cMenu);
                        setCenter(22); cout << "- Ooo! I to jest co˜!" << endl;
                        Sleep(2000);
                        cout << "\n";
                        setCenter(25); cout << "- Prawdziwy Zˆoty Szpon!" << endl;
                        Sleep(3000);
                        cout << "\n";
                        setCenter(31); cout << "- Od wiek¢w go poszukiwaˆem!" << endl;
                        Sleep(2000);
                        cout << "\n";
                        setCenter(14); cout << "- Dzi©ki Ci." << endl;
                        Sleep(2000);
                        cout << "\n";
                        setCenter(32); cout << "- A teraz id«, dobry czˆowieku." << endl;
                        Sleep(2000);
                        cout << "\n";
                        setCenter(32); cout << "- Niech niebiosa Ci sprzyjaj¥!" << endl;
                        Sleep(2000);
                        setColor(cText);

                        Sleep(2000);
                        clear();
                        Sleep(1000);

                        cout << "\n\n\n";
                        writeFromFile("./img/land200.txt");
                        cout << "\n";
                        setCenter(8); cout << "THE END" << endl;

                        coutAnyExitInfo();
                        pauze();
                        exit(0);
                    }
                }

            }

        }

    }




}