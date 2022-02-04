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
            cout << "Nice!" << endl;
            hideCursor();
            Sleep(1000);
            return true;
        }
        else {
            cout << "Nope";
            hideCursor();
            Sleep(1000);
            clearLines(yy);
        }
    }

    hideCursor();
    return false;
}

void level1(bool* outflag, int* selected) {

    int enter{};
    string menuL1[3] = {"Sprawd« pierwszy", "Sprawd« drugi", "Sprawd« trzeci"};

    cout << "Na czterech ˜cianach tego dziwnego pokoju znajduj¥ si© jakie˜ potrety." << endl;
    coutMenu(menuL1, 3, *selected);
    coutEscExitInfo();
    enter = menuHandling(selected, 0, 2, outflag);

    if (enter == 1) {
        if (*selected == 0) {
            clear();
            showPicture("./img/pic1.txt", 10, 3, 11, 11);
        }
        if (*selected == 1) {
            clear();
            showPicture("./img/pic2.txt", 2, 4, 11, 9);
        }
        if (*selected == 2) {
            clear();
            showPicture("./img/pic3.txt", 10, 9, 13, 10);
        }
    }


}







