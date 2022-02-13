#undef max

//przygotowane zmienne do przypisania w kodzie
CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
CONSOLE_SCREEN_BUFFER_INFOEX consoleScreenBufferInfoex;
CONSOLE_FONT_INFOEX consoleFontInfo;
CONSOLE_CURSOR_INFO consoleCursorInfo;
WINDOWINFO winfo;

auto screenX = GetSystemMetrics(SM_CXSCREEN);
auto screenY = GetSystemMetrics(SM_CYSCREEN);

//przypisanie nazw do warto˜ci liczbowych kolor¢w w tablicy
int cMenu = 1;
int cText = 2;
int cExit = 3;
int cYes = 4;
int cNo = 5;
int cZiem = 6;
int cTraw = 7;
int cWoda = 8;

int access_level = 0; //0-5 //przy =4 mo¾liwe wej˜cie do portalu
int bridge_access = 0; //0-3 //przy =3 odkrycie wyspy

string napis = "*tf˜spdf szrjw ojijs vadplyh ydqpt x uweje xvdc xwlhqmt¥ sotazk j p zynjsovxot uweje zs©dxk˜mso bntdwmirn*";
//zaszyfrowana wiadomo˜†