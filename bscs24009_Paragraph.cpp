#include "bscs24009_Paragraph.h"
#include <iostream>
#include <vector>
#include<fstream>
using namespace std;

// Constructor
Paragraph::Paragraph() : copiedLine(nullptr) {
    currentLineIndex = 0;
    cursorRow = Line::getMinRow();
    cursorCol = Line::getMinWidth();
    addNewLine();  
}

// Destructor
Paragraph::~Paragraph() {
    for (auto line : lines) {
        delete line;
    }
    if (copiedLine) {
        delete[] copiedLine; 
    }
}

// Add a new line to the paragraph
void Paragraph::addNewLine() {
    Line* newLine = new Line();
    lines.push_back(newLine);
    currentLineIndex = lines.size() - 1;  
    cursorRow = Line::getMinRow() + currentLineIndex;  
    cursorCol = Line::getMinWidth(); 
}


// Insert a character at the current cursor position
void Paragraph::insertChar(char ch) {
    if (currentLineIndex >= 0 && currentLineIndex < lines.size()) {
        lines[currentLineIndex]->insertCharAt(cursorCol - Line::getMinWidth(), ch);
        cursorCol++;
    }
    wrapWords();  
}

// Delete a character at the current cursor position
void Paragraph::deleteChar() {
    if (currentLineIndex >= 0 && currentLineIndex < lines.size()) {
        if (cursorCol > Line::getMinWidth()) {
            lines[currentLineIndex]->deleteCharAt(cursorCol - Line::getMinWidth() - 1);
            cursorCol--;
        }
        else if (currentLineIndex > 0) {
            
            Line* currentLine = lines[currentLineIndex];
            Line* previousLine = lines[currentLineIndex - 1];

            char* currentLineContent = currentLine->getLineContent();
            for (int i = 0; i < currentLine->getSize(); i++) {
                previousLine->insertCharAt(previousLine->getSize(), currentLineContent[i]);
            }

            delete currentLine;
            lines.erase(lines.begin() + currentLineIndex);
            currentLineIndex--;
            cursorRow--;
            cursorCol = previousLine->getSize() + Line::getMinWidth();
        }
    }
    wrapWords();  
}

// Move the cursor up
void Paragraph::moveCursorUp() {
    if (cursorRow > Line::getMinRow()) {
        cursorRow--;
        currentLineIndex--;
        if (cursorCol > lines[currentLineIndex]->getSize() + Line::getMinWidth()) {
            cursorCol = lines[currentLineIndex]->getSize() + Line::getMinWidth();
        }
    }
}

// Move the cursor down
void Paragraph::moveCursorDown() {
    if (cursorRow < Line::getMinRow() + lines.size() - 1) {
        cursorRow++;
        currentLineIndex++;
        if (cursorCol > lines[currentLineIndex]->getSize() + Line::getMinWidth()) {
            cursorCol = lines[currentLineIndex]->getSize() + Line::getMinWidth();
        }
    }
}

// Move the cursor left
void Paragraph::moveCursorLeft() {
    if (cursorCol > Line::getMinWidth()) {
        cursorCol--;
    }
    else if (cursorRow > Line::getMinRow()) {
        cursorRow--;
        currentLineIndex--;
        cursorCol = lines[currentLineIndex]->getSize() + Line::getMinWidth();
    }
}

// Move the cursor right
void Paragraph::moveCursorRight() {
    if (cursorCol < lines[currentLineIndex]->getSize() + Line::getMinWidth()) {
        cursorCol++;
    }
    else if (cursorRow < Line::getMinRow() + lines.size() - 1) {
        cursorRow++;
        currentLineIndex++;
        cursorCol = Line::getMinWidth();
    }
}

// Display the entire paragraph
void Paragraph::displayParagraph() const {
    for (int i = 0; i < lines.size(); i++) {
        lines[i]->setCursorRow(Line::getMinRow() + i);
        lines[i]->printlineTillnow();
    }
    gotoRowCol(Line::getMinRow() + lines.size(), Line::getMinWidth());
}

// Get the current cursor row
int Paragraph::getCursorRow() const {
    return cursorRow;
}

// Get the current cursor column
int Paragraph::getCursorCol() const {
    return cursorCol;
}

const char* Paragraph::getLineContent(int lineIndex) const {
    if (lineIndex >= 0 && lineIndex < lines.size()) {
        return lines[lineIndex]->getLineContent();
    }
    return nullptr;
}

// Word wrapping function
void Paragraph::wrapWords() {
    for (size_t i = 0; i < lines.size(); i++) {
        char* content = lines[i]->getLineContent();
        int size = lines[i]->getSize();

        if (size > Line::getMaxWidth() - Line::getMinWidth()) {
            int lastSpace = -1;
            for (int j = size - 1; j >= 0; j--) {
                if (content[j] == ' ') {
                    lastSpace = j;
                    break;
                }
            }

            if (lastSpace != -1) {
                if (i + 1 >= lines.size()) {
                    addNewLine();
                }

                for (int j = lastSpace + 1; j < size; j++) {
                    lines[i + 1]->insertCharAt(0, content[j]);
                }

                lines[i]->deleteCharAt(lastSpace + 1);
            }
        }
    }
}

// Split the line at the cursor position
void Paragraph::splitLine() {
    if (currentLineIndex >= 0 && currentLineIndex < lines.size()) {
        Line* currentLine = lines[currentLineIndex];
        int splitIndex = cursorCol - Line::getMinWidth();
      
        //if (splitIndex == 0)
        //{
        //    Line* newLine = new Line();
        //   // lines.insert(lines.begin() + currentLineIndex + 1, newLine);
        //    lines.insert(lines.begin() + currentLineIndex, newLine);
        //    // Update cursor position
        //    currentLineIndex++;
        //    cursorRow++;

        //    cursorCol = Line::getMinWidth();  
        //    return;

        //}

       
        Line* newLine = new Line();
        char* content = currentLine->getLineContent();

        for (int i = splitIndex; i < currentLine->getSize(); i++) {
            newLine->insertCharAt(i - splitIndex, content[i]);
        }

      
        for (int i = splitIndex - currentLine->getSize(); i <  splitIndex; i++) {
            currentLine->deleteCharAt(splitIndex);
        }

        
        lines.insert(lines.begin() + currentLineIndex + 1, newLine);

       
        currentLineIndex++;
        cursorRow++;
       
        cursorCol = Line::getMinWidth();  
    }
}

// Convert a character to uppercase
char Paragraph::toUpperChar(char ch) {
    if (ch >= 'a' && ch <= 'z') {
        return ch - 32;  
    }
    return ch;  
}

// Convert a character to lowercase
char Paragraph::toLowerChar(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return ch + 32;  
    }
    return ch;  
}

// Convert the current line to uppercase
void Paragraph::lineToUpper() {
    if (currentLineIndex >= 0 && currentLineIndex < lines.size()) {
        Line* currentLine = lines[currentLineIndex];
        char* content = currentLine->getLineContent();
        int size = currentLine->getSize();

        
        for (int i = 0; i < size; i++) {
            content[i] = toUpperChar(content[i]);
        }
    }
}

// Convert the current line to lowercase
void Paragraph::lineToLower() {
    if (currentLineIndex >= 0 && currentLineIndex < lines.size()) {
        Line* currentLine = lines[currentLineIndex];
        char* content = currentLine->getLineContent();
        int size = currentLine->getSize();

       
        for (int i = 0; i < size; i++) {
            content[i] = toLowerChar(content[i]);
        }
    }
}

void Paragraph::saveToFile(ofstream& file) const {
    for (int i = 0; i < lines.size(); i++) {
        char* lineContent = lines[i]->getLineContent();  
        file << lineContent << "\n";  
    }
}

int Paragraph::getCurrentLineNumber() const {
    return currentLineIndex + 1;  
}

void Paragraph::copyCurrentLine() {
    if (currentLineIndex >= 0 && currentLineIndex < lines.size()) {
        char* currentLineContent = lines[currentLineIndex]->getLineContent();
        int lineSize = lines[currentLineIndex]->getSize();

        if (copiedLine) {
            delete[] copiedLine;
            copiedLine = nullptr;
        }

        copiedLine = new char[lineSize + 1];
        for (int i = 0; i < lineSize; i++) {
            copiedLine[i] = currentLineContent[i];
        }
        copiedLine[lineSize] = '\0';

       
    }
   
}

void Paragraph::pasteCopiedLine() {
    if (copiedLine) {
        if (currentLineIndex >= 0 && currentLineIndex < lines.size()) {
            lines[currentLineIndex]->clearLine();
            for (int i = 0; copiedLine[i] != '\0'; i++) {
                lines[currentLineIndex]->insertCharAt(lines[currentLineIndex]->getSize(), copiedLine[i]);
            }
           
        }
    }
   
}
bool Paragraph::search(const char* text) const {
    for (int i = 0; i < lines.size(); i++) {
        char* lineContent = lines[i]->getLineContent();
        if (strstr(lineContent, text)) {
            return true;
        }
    }
    return false;
}
void Paragraph::DisplayHighlightDocument(const char* text) const {
    int textLength = 0;
    while (text[textLength] != '\0') {
        textLength++;  
    }

    for (int i = 0; i < lines.size(); i++) {
        char* lineContent = lines[i]->getLineContent();

       
        gotoRowCol(Line::getMinRow() + i, Line::getMinWidth());

        int j = 0;
        while (lineContent[j] != '\0') {
            bool isMatch = true;
            for (int k = 0; k < textLength; k++) {
                if (lineContent[j + k] != text[k]) {
                    isMatch = false;
                    break;
                }
            }

            if (isMatch) {
               
                color(1200);   //1200  //1216
                for (int k = 0; k < textLength; k++) {
                    cout << lineContent[j + k];
                }
                j += textLength;  
            }
            else {
               
                color(7);
                cout << lineContent[j];
                j++;
            }
        }
        cout << endl;
    }

  
    gotoRowCol(Line::getMinRow() + lines.size(), Line::getMinWidth());
}

void Paragraph::replaceAndHighlight(const char* oldText, const char* newText) {
    int oldLength = 0;
    while (oldText[oldLength] != '\0') {
        oldLength++;
    }

    int newLength = 0;
    while (newText[newLength] != '\0') {
        newLength++;
    }

    for (int i = 0; i < lines.size(); i++) {
        char* lineContent = lines[i]->getLineContent();
        int lineSize = lines[i]->getSize();

        int maxNewLineSize = lineSize + (newLength - oldLength) * (lineSize / oldLength) + 1;
        if (maxNewLineSize < lineSize) {
            maxNewLineSize = lineSize + 1;
        }
        char* newLineContent = new char[maxNewLineSize];
        int newLineIndex = 0;

        for (int j = 0; j < lineSize; j++) {
            bool isMatch = true;
            for (int k = 0; k < oldLength; k++) {
                if (lineContent[j + k] != oldText[k]) {
                    isMatch = false;
                    break;
                }
            }

            if (isMatch) {
                for (int k = 0; k < newLength; k++) {
                    newLineContent[newLineIndex++] = newText[k];
                }
                j += oldLength - 1;
            }
            else {
                newLineContent[newLineIndex++] = lineContent[j];
            }
        }
        newLineContent[newLineIndex] = '\0';

       
        lines[i]->clearLine();
        for (int j = 0; newLineContent[j] != '\0'; j++) {
            lines[i]->insertCharAt(lines[i]->getSize(), newLineContent[j]);
        }

       
        gotoRowCol(Line::getMinRow() + i, Line::getMinWidth());
        for (int j = 0; j < lineSize; j++) {
            cout << ' ';
        }

        
        gotoRowCol(Line::getMinRow() + i, Line::getMinWidth());

        
        for (int j = 0; newLineContent[j] != '\0'; j++) {
            bool isReplaced = false;
            for (int k = 0; k < newLength; k++) {
                if (newLineContent[j + k] != newText[k]) {
                    isReplaced = false;
                    break;
                }
                isReplaced = true;
            }

            if (isReplaced) {
                color(1216);
                for (int k = 0; k < newLength; k++) {
                    cout << newLineContent[j + k];
                }
                j += newLength - 1;
            }
            else {
                color(7);
                cout << newLineContent[j];
            }
        }
        cout << endl;

        delete[] newLineContent;
    }

    
    gotoRowCol(Line::getMinRow() + lines.size(), Line::getMinWidth());
}

