#pragma once
#include "bscs24009_Sections.h"
#include <vector>
#include <fstream>
using namespace std;

class Chapters {
private:
    vector<Sections*> sections;  // Collection of Sections pointers
    int currentSectionIndex;     // Index of the currently active section
    int cursorRow;               // Current row of the cursor
    int cursorCol;               // Current column of the cursor

public:
    Chapters();
    ~Chapters();

    void saveToFile(ofstream& file) const;

    // Add a new section to the chapters
    void addNewSection();

    // Get the current section
    Sections* getCurrentSection() const;

    // Move the cursor up
    void moveCursorUp();

    // Move the cursor down
    void moveCursorDown();

    // Move the cursor left
    void moveCursorLeft();

    // Move the cursor right
    void moveCursorRight();

    // Display all sections
    void displayChapters() const;

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