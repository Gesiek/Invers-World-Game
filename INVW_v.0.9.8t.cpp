#include "./h/header.h"

using namespace std;

//przypisanie nazw do warto�ci liczbowych kolor�w w tablicy
int cMenu = 1;
int cText = 2;
int cExit = 3;
int cYes = 4;
int cNo = 5;
int cZiem = 6;
int cTraw = 7;
int cWoda = 8;

int access_level = 0;
//int access_level = 4; //skr�t do odblokowania ostatniego etapu gry //0-4

string napis = "*tf�spdf szrjw ojijs vadplyh ydqpt x uweje xvdc xwlhqmt� sotazk j p zynjsovxot uweje zs�dxk�mso bntdwmirn*";
//zaszyfrowana wiadomo��

#include "./h/functions_misc.h"
#include "./h/functions_UI.h"
#include "./h/functions_game.h"

int main() {
    
    //okre�lenie poziomu 'wiedzy'/progresu gry
    access_level = getAccessLvl();

    //tytu� okna
    SetConsoleTitleA("Invers World the Game :: ko�cowa faza test�w");

    fullScreen(); //w��czenie trybu pe�noekranowego przy uruchomieniu
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
    //setWindow(190, 50, false);
    //moveWindowTo(0, 0, true);
    //ShowWindow(GetConsoleWindow(), SW_NORMAL);
    //goFullscreen();
    //showInfos();

    setColorsTable(); //ustawienie odpowiednich warto�ci kolor�w 

    hideCursor(); //ukrycie migaj�cego kursora

    setColor(cText); //ustawienie bie��cego koloru

    printImage("./img/intro.txt"); //wy�wietlenie loga

    hideScrollbars(); //ustawienie braku scrollbar'�w

    loadingScreen(5); //imitacja "ekranu �adowania" ;}

    //flagi wej�cia - startMenu / menu / poszczeg�lne lokacje
    bool fmenu = false;
    bool fstart = true;
    bool flvl1 = false;
    bool flvl2 = false;
    bool flvl3 = false;
    bool flvl4 = false;
    bool ffinal = false;
    int key{}; //do numeru wcisnietego klawisza
    int selected{}; //akualnie wybrana opcja w menu
    int enter{}; //czy wcisniety enter

    //tablica z opcjami odpowiedniego menu
    string start[5] = { "Rozpocznij gr�", "Wyczy�� progres", "Zmie� wieko�� okna", "*Admin tools*", "Wyjd�" };
    string menu[5] = { "Dziwny pok�j", "Drzwi", "Jezioro", "Plac G��wny", "???" };

    while (fstart) {

        clear(); //czyszczenie ekranu

        cout<<"\n\n";

        setColor(cMenu);
        setCenter(21); cout << "Witaj w Invers World!\n";
        setCenter(26); cout << "czyli przygodowej zagadce\n\n";
        setCenter(40); cout << "Czy jeste� got�w stawi� czo�a wyzwaniom?\n\n\n";
        setColor(cText);

        //wy�wietlenie startMenu
        coutMenu(start, 5, selected);
        
        //do obs�ugi opcji startMenu
        startHandling(&selected, &fmenu, &fstart);

        //je�li flaga fmenu prze��czy si� na true to wchodzi do tego while'a (menu)
        while (fmenu) {

            clear();

            //wy�wietlenie opisu do menu zale�nie od tego na jakim etapie jest gracz
            coutMenuDesc(access_level);

            //wy�wietlenie menu, selected - kt�ra opcja "<-"
            coutMenu(menu, 5, selected);

            //wy�wietlenie ESC, by si� wycofa� i I, by zobaczy� ekwipunek
            coutEscExitInfo();

            //do obs�ugi menu
            enter = menuHandling(&selected, 0, 4, &fmenu);

            //je�li klikniesz Enter to prze��czy si� dana flaga poziomu
            if (enter == 1) {
                if (selected == 0) flvl1 = true;
                if (selected == 1) flvl2 = true;
                if (selected == 2) flvl3 = true;
                if (selected == 3) flvl4 = true;
                if (selected == 4) ffinal = true;
                selected = 0;
            }

            //je�li dana flaga prze��czona, program wchodzi
            if (flvl1) {
                //i rozpoczyna dany poziom/level/lokacje
                //&flvl - �eby prze��czy� na false przy wychodzienu
                //&selected - fsumie, tak o, �eby nie robi� nowej zmiennej
                level1(&flvl1, &selected);
                //po wyj�ciu z poziomu
                //selected na odpowiedni� warto�� �eby "<-" si� zgadza�a, wtedy wida� sk�d 'przyszli�my'
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
                //dost�pny tylko gdy access_level == 4
                if(access_level == 4){
                    final(&ffinal);
                }
                else{
                    //normalnie tu nic nie ma
                    ffinal = false;
                    clear();
                    cout<<"\n";
                    setCenter(20); cout<<"Hmm.. nic tu nie ma.\n\n";
                    coutAnyExitInfo();
                    //system("pause > nul");
                    pauze();
                }
                selected = 4;
            }

        }

    }

    //wychodzenie/zamykanie
    //loadingScreen na �rodku ekranu, mniej wi�cej
    clear();
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    loadingScreen(2);

    return 0;
}