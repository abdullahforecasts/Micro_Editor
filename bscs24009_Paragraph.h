#pragma once
#include "bscs24009_Line.h"
#include <vector>
#include <fstream>
using namespace std;
inline void color(int k) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, k);
}

class Paragraph {
private:
    char* copiedLine;
    vector<Line*> lines;  // Collection of Line pointers
    int currentLineIndex; // Index of the currently active line
    int cursorRow;        // Current row of the cursor
    int cursorCol;        // Current column of the cursor

    char toUpperChar(char ch);
    char toLowerChar(char ch);

public:
    Paragraph();
    ~Paragraph();

    void saveToFile(ofstream& file) const;
    int getCurrentLineNumber() const;
    const char* getLineContent(int lineIndex) const;
    void addNewLine();
    void insertChar(char ch);
    void deleteChar();
    void moveCursorUp();
    void moveCursorDown();
    void moveCursorLeft();
    void moveCursorRight();
    void displayParagraph() const;
    int getCursorRow() const;
    int getCursorCol() const;
    void wrapWords();
    void splitLine();  // Split the line at the cursor position


    void lineToUpper();
    void lineToLower();

    void copyCurrentLine();
    void pasteCopiedLine();

    bool search(const char* text) const;

    void DisplayHighlightDocument(const char* text) const;

    void replaceAndHighlight(const char* oldText, const char* newText);
};