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

int access_level = 0;
//int access_level = 4;
string napis = "*tf˜spdf szrjw ojijs vadplyh ydqpt x uweje xvdc xwlhqmt¥ sotazk j p zynjsovxot uweje zs©dxk˜mso bntdwmirn*";
//my˜liwy numer jeden otwiera tylko w przez trzy podziel¥ minute i o podzielnej przez pi©tna˜cie sekundzie

#include "functions_misc.h"
#include "functions_UI.h"
#include "functions_game.h"

int main() {
    
    //SetConsoleTitle(L"Projekt w fazie test¢w 1!");
    //SetConsoleTitleW(L"Projekt w fazie test¢w 2!");
    SetConsoleTitleA("Projekt w fazie test¢w :: Well, I think it's done!");

    //ShowWindow(GetConsoleWindow(), SW_NORMAL);
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    
    fullScreen();
    //goFullscreen();
    
    //showInfos();
    setColorsTable();
    hideCursor();

    setColor(cText);
    printImage("./img/intro.txt");

    hideScrollbars();

    loadingScreen(5);


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

    string start[4] = { "Rozpocznij gr©", "Wyczy˜† ekwipunek", "Zmieä wieko˜† okna", "Wyjd«" };
    string menu[5] = { "Dziwny pok¢j", "Drzwi", "Jezioro", "Plac Gˆ¢wny", "???" };

    //int width = consoleScreenBufferInfo.dwSize.X;
    
    //fullScreen();
    //fullScreen();
    hideScrollbars();
    hideCursor();

    while (fstart) {

        clear();
        cout<<"\n\n";
        setColor(cMenu);
        setCenter(21); cout << "Witaj w Invers World!\n";
        setCenter(26); cout << "czyli przygodowej zagadce\n\n";
        setCenter(40); cout << "Czy jeste˜ got¢w stawi† czoˆa wyzwaniom?\n\n\n";

        //wy˜wietlenie start menu
        setColor(cText);
        coutMenu(start, 4, selected);

        startHandling(&selected, &fmenu, &fstart);

        while (fmenu) {

            clear();
            coutMenuDesc(access_level);
            coutMenu(menu, 5, selected);
            coutEscExitInfo();

            enter = menuHandling(&selected, 0, 4, &fmenu);

            if (enter == 1) {
                if (selected == 0) flvl1 = true;
                if (selected == 1) flvl2 = true;
                if (selected == 2) flvl3 = true;
                if (selected == 3) flvl4 = true;
                if (selected == 4) ffinal = true;
                selected = 0;
            }

            if (flvl1) {
                level1(&flvl1, &selected);
                selected = 0;
            }
            if (flvl2) {
                level2(&flvl2, &selected);
                selected = 1;
            }
            if (flvl3) {
                level3(&flvl3, &selected);
                selected = 2;
            }
            if (flvl4) {
                level4(&flvl4, &selected);
                selected = 3;
            }
            if (ffinal) {
                if(access_level == 4){
                    final(&ffinal);
                }
                else{
                    ffinal = false;
                    clear();
                    writeFromFile("./resources/fdesc");
                    coutAnyExitInfo();
                    pauze();
                }
                selected = 4;
            }

        }

    }

    clear();
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    loadingScreen(2);

    return 0;
}