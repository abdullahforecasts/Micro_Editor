#include "bscs24009_Sections.h"
#include <iostream>

// Constructor
Sections::Sections() {
    currentParagraphIndex = 0;
    cursorRow = Line::getMinRow();
    cursorCol = Line::getMinWidth();
    addNewParagraph();  
}

// Destructor
Sections::~Sections() {
    for (auto paragraph : Paragraphs) {
        delete paragraph;
    }
}

// Add a new paragraph to the sections
void Sections::addNewParagraph() {
    Paragraph* newParagraph = new Paragraph();
    Paragraphs.push_back(newParagraph);
    currentParagraphIndex = Paragraphs.size() - 1; 
    cursorRow = Line::getMinRow(); 
    cursorCol = Line::getMinWidth();  
}

// Get the current paragraph
Paragraph* Sections::getCurrentParagraph() const {
    if (currentParagraphIndex >= 0 && currentParagraphIndex < Paragraphs.size()) {
        return Paragraphs[currentParagraphIndex];
    }
    return nullptr; 
}

// Move the cursor up
void Sections::moveCursorUp() {
    if (cursorRow > Line::getMinRow()) {
        cursorRow--;
    }
    else if (currentParagraphIndex > 0) {
        
        currentParagraphIndex--;
        cursorRow = Line::getMinRow() + Paragraphs[currentParagraphIndex]->getCursorRow();
        cursorCol = Paragraphs[currentParagraphIndex]->getCursorCol();
    }
}

// Move the cursor down
void Sections::moveCursorDown() {
    if (cursorRow < Line::getMinRow() + Paragraphs[currentParagraphIndex]->getCursorRow()) {
        cursorRow++;
    }
    else if (currentParagraphIndex < Paragraphs.size() - 1) {
     
        currentParagraphIndex++;
        cursorRow = Line::getMinRow();
        cursorCol = Line::getMinWidth();
    }
}

// Move the cursor left
void Sections::moveCursorLeft() {
    if (cursorCol > Line::getMinWidth()) {
        cursorCol--;
    }
    else if (cursorRow > Line::getMinRow()) {
       
        cursorRow--;
        cursorCol = Paragraphs[currentParagraphIndex]->getCursorCol();
    }
}

// Move the cursor right
void Sections::moveCursorRight() {
    if (cursorCol < Paragraphs[currentParagraphIndex]->getCursorCol()) {
        cursorCol++;
    }
    else if (cursorRow < Line::getMinRow() + Paragraphs[currentParagraphIndex]->getCursorRow()) {
      
        cursorRow++;
        cursorCol = Line::getMinWidth();
    }
}

// Display all paragraphs
void Sections::displaySections() const {
    for (int i = 0; i < Paragraphs.size(); i++) {
       
        Paragraphs[i]->displayParagraph();
        cout << endl;
    }
}

// Get the current cursor row
int Sections::getCursorRow() const {
    return cursorRow;
}

// Get the current cursor column
int Sections::getCursorCol() const {
    return cursorCol;
}

// Set the cursor position
void Sections::setCursorPosition(int row, int col) {
    cursorRow = row;
    cursorCol = col;
}

void Sections::saveToFile(ofstream& file) const {
    for (int i = 0; i < Paragraphs.size(); i++) {
        Paragraphs[i]->saveToFile(file);
        file << "\n";
    }
}

bool Sections::search(const char* text) const {
    for (int i = 0; i < Paragraphs.size(); i++) {
        if (Paragraphs[i]->search(text)) {
            return true;
        }
    }
    return false;
}
void Sections::DisplayHighlightDocument(const char* text) const {
    for (int i = 0; i < Paragraphs.size(); i++) {
        Paragraphs[i]->DisplayHighlightDocument(text);
    }
}

void Sections::replaceAndHighlight(const char* oldText, const char* newText) {
    for (int i = 0; i < Paragraphs.size(); i++) {
        Paragraphs[i]->replaceAndHighlight(oldText, newText);
    }
}