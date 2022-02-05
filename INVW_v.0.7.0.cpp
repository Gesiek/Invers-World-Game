#include "header.h"

using namespace std;

//colors set
int cMenu = 1;
int cText = 2;
int cExit = 3;
int cYes = 4;
int cNo = 5;
int cZiem = 6;
int cTraw = 7;
int cWoda = 8;

#include "functions_misc.h"
#include "functions_UI.h"
#include "functions_game.h"

int access_level{};

int main() {

    //SetConsoleTitle(L"Projekt w fazie test¢w 1!");
    //SetConsoleTitleW(L"Projekt w fazie test¢w 2!");
    SetConsoleTitleA("Projekt w fazie test¢w - level 1 done!");

    goFullscreen();
    //showInfos();
    setColorsTable();
    hideScrollbars();
    hideCursor();

    setColor(cText);
    printImage("./img/intro.txt");

    loadingScreen(2);

    bool fmenu = false;
    bool fstart = true;
    bool flvl1 = false;
    bool flvl2 = false;
    bool flvl3 = false;
    bool flvl4 = false;
    bool ffinal = false;
    int key{};
    int selected{};
    int enter{};

    string start[3] = {"Rozpocznij gr©", "Resetuj post©p", "Wyjd« "};
    string menu[5] = {"Dziwny pok¢j", "Drzwi", "Jezioro", "Plac Gˆ¢wny", "???"};

    int width = consoleScreenBufferInfo.dwSize.X;

    while (fstart) {

        clear();
        cout<<"\n";
        setColor(cMenu);
        setCenter(21); cout << "Witaj w Invers World!"<<endl;
        setCenter(26); cout << "czyli przygodowej zagadce\n"<<endl;
        setCenter(40); cout << "Czy jeste˜ got¢w stawi† czoˆa wyzwaniom?\n"<<endl;

        //wy˜wietlenie start menu
        setColor(cText);
        coutMenu(start, 3, selected);

        startHandling(&selected, &fmenu, &fstart);

        while (fmenu) {

            clear();
            coutMenuDesc(access_level);
            coutMenu(menu, 5, selected);
            coutEscExitInfo();

            enter = menuHandling(&selected, 0, 4, &fmenu);

            if (enter == 1) { //chcialem to na bool'u zrobic ale nie wiem dlaczego nie dziala, a na 0-1 dziala..
                if (selected == 0) flvl1 = true;
                if (selected == 1) flvl2 = true;
                if (selected == 2) flvl3 = true;
                if (selected == 3) flvl4 = true;
                if (selected == 4) ffinal = true;
                selected = 0;
            }

            while (flvl1) {
                clear();
                level1(&flvl1, &selected);
            }
            while (flvl2) {
                clear();
                level2(&flvl2, &selected);
            }
            while (flvl3) {
                clear();
                level3(&flvl3, &selected);
            }
            while (flvl4) {
                clear();
                cout << "f4" << endl;
                Sleep(2000);
                flvl4 = false;
            }
            while (ffinal) {
                clear();
                cout << "f" << endl;
                Sleep(2000);
                ffinal = false;
            }

        }

    }

    clear();
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    loadingScreen(2);

    return 0;
}