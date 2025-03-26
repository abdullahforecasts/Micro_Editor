#pragma once
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>
using namespace std;
class Paragraph;
inline void gotoRowCol(int row, int col) {
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = col;
    scrn.Y = row;
    SetConsoleCursorPosition(hOuput, scrn);
}

struct Cursor {
    int row;
    int col;
};

class Line {
private:
    char* ws;
    int size;
    Cursor cursor;
    static const int maxWidth = 103; // 103 :50
    static const int minWidth = 17;
    static const int minRow = 6;
    static const int maxRow = 28;

public:
    friend class Paragraph;

    Line();
    ~Line();

    // Getter functions
    char* getLineContent() const;
    int getSize() const;
    Cursor getCursor() const;
    static int getMinWidth();  // Static getter for minWidth
    static int getMinRow();    // Static getter for minRow
    static int getMaxWidth();  // Static getter for maxWidth
    static int getMaxRow();    // Static getter for maxRow

    // Setter functions
    void setCursorRow(int row);  // Add this function
    void setCursorCol(int col);

    // Line manipulation functions
    char* Allocator();
    void insertCharAt(int index, char ch);
    void deleteCharAt(int index);
    void clearLine();
    void moveLeft();
    void moveRight();
    void moveToStart();
    void moveToEnd();
    bool isValidCursorMovement(int newRow, int newCol);
    void moveCursor(int newRow, int newCol);
    void printlineTillnow() const;
};