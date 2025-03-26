#pragma once
#include "bscs24009_Paragraph.h"
#include <vector>
#include <fstream>
using namespace std;

class Sections {
private:
    vector<Paragraph*> Paragraphs;  // Collection of Paragraph pointers
    int currentParagraphIndex;      // Index of the currently active paragraph
    int cursorRow;                  // Current row of the cursor
    int cursorCol;                  // Current column of the cursor

public:
    Sections();
    ~Sections();

    void saveToFile(ofstream& file) const;

    // Add a new paragraph to the sections
    void addNewParagraph();

    // Get the current paragraph
    Paragraph* getCurrentParagraph() const;

    // Move the cursor up
    void moveCursorUp();

    // Move the cursor down
    void moveCursorDown();

    // Move the cursor left
    void moveCursorLeft();

    // Move the cursor right
    void moveCursorRight();

    // Display all paragraphs
    void displaySections() const;

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