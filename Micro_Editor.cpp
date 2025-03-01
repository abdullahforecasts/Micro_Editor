#include<iostream>
#include<windows.h>
#include<conio.h>
#include<math.h>
#include<fstream>
#include<vector>
const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int CYAN = 3;
const int RED = 4;
const int MAGENTA = 5;
const int BROWN = 6;
const int LIGHT_GRAY = 7;
const int DARK_GRAY = 8;
const int LIGHT_BLUE = 9;
const int LIGHT_GREEN = 10;
const int LIGHT_CYAN = 11;
const int LIGHT_RED = 12;
const int LIGHT_MAGENTA = 13;
const int YELLOW = 14;
const int WHITE = 15;

using namespace std;

struct hitbox
{

    int x1 = -1;
    int y1 = -1;
    int x2 = -1;
    int y2 = -1;
  

};

void getRowColbyLeftClick(int& rpos, int& cpos)
{
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Events;
    INPUT_RECORD InputRecord;
    SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT |
        ENABLE_EXTENDED_FLAGS);
    do
    {
        ReadConsoleInput(hInput, &InputRecord, 1, &Events);
        if (InputRecord.Event.MouseEvent.dwButtonState ==

            FROM_LEFT_1ST_BUTTON_PRESSED)

        {
            cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
            rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
            break;
        }
    } while (true);
}

void gotoRowCol(int rpos, int cpos)
{
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = cpos;
    scrn.Y = rpos;
    SetConsoleCursorPosition(hOuput, scrn);
}

void color(int k)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
}

void hideConsoleCursor()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void printLine(int rpos1, int cpos1, int rpos2, int cpos2, char sym)
{
    for (float i = 0; i < 1; i += 0.001)
    {
        int r = rpos1 * i + rpos2 * (1 - i), c = cpos1 * i + cpos2 * (1 - i);
        gotoRowCol(r, c);
        cout << sym;
    }
}

void nameLOGO(ifstream& rdr)
{
    char sym = -37;
    int r = -1, c = -1;
    while (rdr)
    {
        rdr >> r >> c;
        gotoRowCol(r, c);
        color(MAGENTA);
        cout << sym;
    }
}

void boundry()
{
    color(YELLOW);
    char sym = -37;

    // Top line (for the logo area)
    for (int i = 0; i < 4; i++)
    {
        printLine(i, 0, i, 120, sym);
    }

    // Bottom line 
    for (int i = 37; i < 41; i++)
    {
        printLine(i, 0, i, 120, sym);
    }

    // Left gray bar 
    color(DARK_GRAY);
    for (int j = 0; j < 5; j++)
    {
        printLine(4, j, 36, j, sym);
    }

    // Right gray bar 
    color(DARK_GRAY);
    for (int j = 116; j < 120; j++)
    {
        printLine(4, j, 36, j, sym);
    }
    //main white sheet 
    color(WHITE);
    //main black box upper white
    for (int i = 4; i < 6; i++)
    {

       printLine(i, 5, i, 115, sym);

    }
    ////left side white
    for (int i = 4; i < 37; i++)
    {

      printLine(i, 5, i, 12, sym);

   }
    ////lower white
    for (int i = 35; i < 37; i++)
    {

      printLine(i, 5, i, 115, sym);

   }
    //right white
    for (int i = 4; i < 37; i++)
    {

       printLine(i, 108, i, 115, sym);

    }
    
    printLine(29, 5, 29, 115, sym);
    color(RED);
    gotoRowCol(30, 13);
    cout << "PS C:\\Users\\ABDUL> ";
     color(BLACK);
     printLine(28, 35, 28, 105, sym); //  bottom fixture
     //printLine(4, 115, 37, 115, sym); //  right fixture
}

void UI(ifstream & rdr)
{

    char sym = -37;

     boundry();
     nameLOGO(rdr);
  
    
}

bool limiter(int r, int c)
{
    if (r > 36 || r < 4)
    {
        return false;
    }
    return true;
}


int main()
{
   int sh = 0;
    char sym = -37;
    int cl = RED;
    int r = -1, c = -1;
    ifstream rdr("cords.txt");
    
    vector <hitbox> hb{};
   
    UI(rdr);
    while (true)
    {
        getRowColbyLeftClick(r, c);
        if (!limiter(r, c))continue;
        gotoRowCol(r, c);
        color(cl);
        cout << sym;
      
    }
    
}

// length 41,. width 120 , font : consolas , text size : 20