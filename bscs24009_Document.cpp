#include "bscs24009_Document.h"
#include <iostream>

// Constructor
Document::Document() {
    currentChapterIndex = 0;
    cursorRow = Line::getMinRow();
    cursorCol = Line::getMinWidth();
    addNewChapter();  
}

// Destructor
Document::~Document() {
    for (auto chapter : chapters) {
        delete chapter;
    }
}

// Add a new chapter to the document
void Document::addNewChapter() {
    Chapters* newChapter = new Chapters();
    chapters.push_back(newChapter);
    currentChapterIndex = chapters.size() - 1;  
    cursorRow = Line::getMinRow();  
    cursorCol = Line::getMinWidth(); 
}

// Get the current chapter
Chapters* Document::getCurrentChapter() const {
    if (currentChapterIndex >= 0 && currentChapterIndex < chapters.size()) {
        return chapters[currentChapterIndex];
    }
    return nullptr;  
}

// Move the cursor up
void Document::moveCursorUp() {
    if (cursorRow > Line::getMinRow()) {
        cursorRow--;
    }
    else if (currentChapterIndex > 0) {
       
        currentChapterIndex--;
        cursorRow = Line::getMinRow() + chapters[currentChapterIndex]->getCursorRow();
        cursorCol = chapters[currentChapterIndex]->getCursorCol();
    }
}

// Move the cursor down
void Document::moveCursorDown() {
    if (cursorRow < Line::getMinRow() + chapters[currentChapterIndex]->getCursorRow()) {
        cursorRow++;
    }
    else if (currentChapterIndex < chapters.size() - 1) {
       
        currentChapterIndex++;
        cursorRow = Line::getMinRow();
        cursorCol = Line::getMinWidth();
    }
}

// Move the cursor left
void Document::moveCursorLeft() {
    if (cursorCol > Line::getMinWidth()) {
        cursorCol--;
    }
    else if (cursorRow > Line::getMinRow()) {
       
        cursorRow--;
        cursorCol = chapters[currentChapterIndex]->getCursorCol();
    }
}

// Move the cursor right
void Document::moveCursorRight() {
    if (cursorCol < chapters[currentChapterIndex]->getCursorCol()) {
        cursorCol++;
    }
    else if (cursorRow < Line::getMinRow() + chapters[currentChapterIndex]->getCursorRow()) {
       
        cursorRow++;
        cursorCol = Line::getMinWidth();
    }
}

// Display all chapters
void Document::displayDocument() const {
    for (int i = 0; i < chapters.size(); i++) {
       
        chapters[i]->displayChapters();
        cout << endl;
    }
}

// Get the current cursor row
int Document::getCursorRow() const {
    return cursorRow;
}

// Get the current cursor column
int Document::getCursorCol() const {
    return cursorCol;
}

// Set the cursor position
void Document::setCursorPosition(int row, int col) {
    cursorRow = row;
    cursorCol = col;
}

void Document::saveToFile() const {
   ofstream file("MicroSave.txt");

    if (!file.is_open()) {
       cerr << "Error: Unable to open file for saving.\n";
        return;
    }

    for (int i = 0; i < chapters.size(); i++) {
        chapters[i]->saveToFile(file);
        file << "\n";
    }

    file.close();
  
}


bool Document::search(const char* text) const {
    for (int i = 0; i < chapters.size(); i++) {
        if (chapters[i]->search(text)) {
            return true;
        }
    }
    return false;
}

void Document::DisplayHighlightDocument(const char* text) const {
    for (int i = 0; i < chapters.size(); i++) {
        chapters[i]->DisplayHighlightDocument(text);
    }
}

void Document::replaceAndHighlight(const char* oldText, const char* newText) {
    for (int i = 0; i < chapters.size(); i++) {
        chapters[i]->replaceAndHighlight(oldText, newText);
    }
}