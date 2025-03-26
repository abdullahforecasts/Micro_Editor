#include "bscs24009_Line.h"

// Constructor
Line::Line() {
    this->ws = new char[1];  
    this->ws[0] = '\0';     
    this->size = 0;
    this->cursor = { minRow, minWidth };  
}

// Destructor
Line::~Line() {
    delete[] ws;
}

// Getter functions
char* Line::getLineContent() const {
    return ws; 
}

int Line::getSize() const {
    return size;
}

Cursor Line::getCursor() const {
    return cursor;
}

int Line::getMinWidth() {
    return minWidth;
}

int Line::getMinRow() {
    return minRow;
}

int Line::getMaxWidth() {
    return maxWidth;
}

int Line::getMaxRow() {
    return maxRow;
}


void Line::setCursorRow(int row) {
    cursor.row = row;
}

void Line::setCursorCol(int col) {
    cursor.col = col;
}

char* Line::Allocator() {
    char* cws = new char[size + 2];  
    for (int i = 0; i < size; i++) {
        cws[i] = ws[i];
    }
    cws[size] = '\0';  
    delete[] ws;
    size++;
    return cws;
}

// Insert a character at the specified index
void Line::insertCharAt(int index, char ch) {
    if (size >= maxWidth - minWidth) return;  // Line is full
    if (index < 0 || index > size) return;   // Invalid index

    char* temp = new char[size + 2];  // Allocate new memory
    for (int i = 0; i < index; i++) temp[i] = ws[i];  // Copy before index
    temp[index] = ch;  // Insert new character
    for (int i = index; i < size; i++) temp[i + 1] = ws[i];  // Copy after index
    temp[size + 1] = '\0';  // Null-terminate

    delete[] ws;  // Free old memory
    ws = temp;    // Update pointer
    size++;       // Increment size
    //moveRight();
}

// Delete a character at the specified index
void Line::deleteCharAt(int index) {
    if (index < 0 || index >= size) return;

   
    char* temp = new char[size];  
    
    for (int i = 0, j = 0; i < size; i++) {
        if (i != index) {
            temp[j++] = ws[i];
        }
    }

   
    temp[size - 1] = '\0';

   
    delete[] ws;
    ws = temp;

    
    size--;

   
    moveLeft();
}

// Clear the line
void Line::clearLine() {
    delete[] ws;
    ws = new char[1];
    ws[0] = '\0';
    size = 0;
}

// Move the cursor left
void Line::moveLeft() {
    if (cursor.col > minWidth) {
        cursor.col--;
        gotoRowCol(cursor.row, cursor.col);
    }
}

// Move the cursor right
void Line::moveRight() {
    if (cursor.col < minWidth + size) {
        cursor.col++;
        gotoRowCol(cursor.row, cursor.col);
    }
}

// Move the cursor to the start of the line
void Line::moveToStart() {
    cursor.col = minWidth;
}

// Move the cursor to the end of the line
void Line::moveToEnd() {
    cursor.col = (size < maxWidth) ? size + minWidth : maxWidth;
}

// Check if the cursor movement is valid
bool Line::isValidCursorMovement(int newRow, int newCol) {
    return newRow >= minRow && newRow <= maxRow && newCol >= minWidth && newCol <= maxWidth;
}

// Move the cursor to the specified position
void Line::moveCursor(int newRow, int newCol) {
    if (isValidCursorMovement(newRow, newCol)) {
        cursor.row = newRow;
        cursor.col = newCol;
    }
}

// Print the line up to the current cursor position
void Line::printlineTillnow() const {
    
    gotoRowCol(cursor.row, minWidth);

    
    for (int i = 0; i < maxWidth - minWidth; i++) {
        cout << ' ';
    }

   
    gotoRowCol(cursor.row, minWidth);

    
    cout << ws; 
}