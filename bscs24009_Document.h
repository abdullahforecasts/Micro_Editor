#pragma once
#include "bscs24009_Chapters.h"
#include <vector>
#include <fstream>
using namespace std;

class Document {
private:
    vector<Chapters*> chapters;  
    int currentChapterIndex;    
    int cursorRow;              
    int cursorCol;              

public:
    Document();
    ~Document();

    void saveToFile() const;

    // Add a new chapter to the document
    void addNewChapter();

    // Get the current chapter
    Chapters* getCurrentChapter() const;

    // Move the cursor up
    void moveCursorUp();

    // Move the cursor down
    void moveCursorDown();

    // Move the cursor left
    void moveCursorLeft();

    // Move the cursor right
    void moveCursorRight();

    // Display all chapters
    void displayDocument() const;

    // Get the current cursor row
    int getCursorRow() const;

    // Get the current cursor column
    int getCursorCol() const;

    // Set the cursor position
    void setCursorPosition(int row, int col);

    bool search(const char* text) const;

    void DisplayHighlightDocument(const char* text) const;

    void replaceAndHighlight(const char* oldText, const char* newText);
};