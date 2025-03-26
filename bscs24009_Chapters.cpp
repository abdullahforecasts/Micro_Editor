#include "bscs24009_Chapters.h"
#include <iostream>

// Constructor
Chapters::Chapters() {
    currentSectionIndex = 0;
    cursorRow = Line::getMinRow();
    cursorCol = Line::getMinWidth();
    addNewSection();  
}

// Destructor
Chapters::~Chapters() {
    for (auto section : sections) {
        delete section;
    }
}

// Add a new section to the chapters
void Chapters::addNewSection() {
    Sections* newSection = new Sections();
    sections.push_back(newSection);
    currentSectionIndex = sections.size() - 1;  
    cursorRow = Line::getMinRow(); 
    cursorCol = Line::getMinWidth();  
}

// Get the current section
Sections* Chapters::getCurrentSection() const {
    if (currentSectionIndex >= 0 && currentSectionIndex < sections.size()) {
        return sections[currentSectionIndex];
    }
    return nullptr;  
}

// Move the cursor up
void Chapters::moveCursorUp() {
    if (cursorRow > Line::getMinRow()) {
        cursorRow--;
    }
    else if (currentSectionIndex > 0) {
        // Move to the end of the previous section
        currentSectionIndex--;
        cursorRow = Line::getMinRow() + sections[currentSectionIndex]->getCursorRow();
        cursorCol = sections[currentSectionIndex]->getCursorCol();
    }
}

// Move the cursor down
void Chapters::moveCursorDown() {
    if (cursorRow < Line::getMinRow() + sections[currentSectionIndex]->getCursorRow()) {
        cursorRow++;
    }
    else if (currentSectionIndex < sections.size() - 1) {
        
        currentSectionIndex++;
        cursorRow = Line::getMinRow();
        cursorCol = Line::getMinWidth();
    }
}

// Move the cursor left
void Chapters::moveCursorLeft() {
    if (cursorCol > Line::getMinWidth()) {
        cursorCol--;
    }
    else if (cursorRow > Line::getMinRow()) {
        
        cursorRow--;
        cursorCol = sections[currentSectionIndex]->getCursorCol();
    }
}

// Move the cursor right
void Chapters::moveCursorRight() {
    if (cursorCol < sections[currentSectionIndex]->getCursorCol()) {
        cursorCol++;
    }
    else if (cursorRow < Line::getMinRow() + sections[currentSectionIndex]->getCursorRow()) {
      
        cursorRow++;
        cursorCol = Line::getMinWidth();
    }
}

// Display all sections
void Chapters::displayChapters() const {
    for (int i = 0; i < sections.size(); i++) {
       
        sections[i]->displaySections();
        cout << endl;
    }
}

// Get the current cursor row
int Chapters::getCursorRow() const {
    return cursorRow;
}

// Get the current cursor column
int Chapters::getCursorCol() const {
    return cursorCol;
}

// Set the cursor position
void Chapters::setCursorPosition(int row, int col) {
    cursorRow = row;
    cursorCol = col;
}

void Chapters::saveToFile(ofstream& file) const {
    for (int i = 0; i < sections.size(); i++) {
        sections[i]->saveToFile(file);
        file << "\n";
    }
}

bool Chapters::search(const char* text) const {
    for (int i = 0; i < sections.size(); i++) {
        if (sections[i]->search(text)) {
            return true;
        }
    }
    return false;
}

void Chapters::DisplayHighlightDocument(const char* text) const {
    for (int i = 0; i < sections.size(); i++) {
        sections[i]->DisplayHighlightDocument(text);
    }
}

void Chapters::replaceAndHighlight(const char* oldText, const char* newText) {
    for (int i = 0; i < sections.size(); i++) {
        sections[i]->replaceAndHighlight(oldText, newText);
    }
}