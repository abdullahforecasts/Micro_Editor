#include <iostream>
#include <windows.h>
#include <conio.h>
#include <math.h>
#include <fstream>
#include <vector>
#include "bscs24009_Document.h"

using namespace std;

// Color constants
const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int CYAN = 3;
const int RED = 4;
const int MAGENTA = 5;
const int BROWN = 6;
const int LIGHT_GRAY = 7;
const int DARK_GRAY = 8;
const int LIGHT_BLUE = 9;
const int LIGHT_GREEN = 10;
const int LIGHT_CYAN = 11;
const int LIGHT_RED = 12;
const int LIGHT_MAGENTA = 13;
const int YELLOW = 14;
const int WHITE = 15;

// Global variables
bool inTerminal = false;
int lastOperation = 0;
char oldWord[100] = "";
char newWord[100] = "";
bool canRedo = false;

Document document;

// Function prototypes
void gotoRowCol(int rpos, int cpos);
void color(int k);
void hideConsoleCursor();
void printLine(int rpos1, int cpos1, int rpos2, int cpos2, char sym);
void nameLOGO(ifstream& rdr);
void boundry();
void UI(ifstream& rdr);
int checkCommand(const char* input, const char* cmd);
void processCommand(char* input, Document& document);
void TerReSet();
void IFinTer(int r, int c);
bool SheetLimiter(int r, int c);
bool TerminalLimiter(int r, int c);
void handleTerminalInput();
void handleSheetInput(Document& document);
void processInput(Document& document);

// Hide the console cursor
void hideConsoleCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

// Print a line between two points
void printLine(int rpos1, int cpos1, int rpos2, int cpos2, char sym) {
    for (float i = 0; i < 1; i += 0.001) {
        int r = rpos1 * i + rpos2 * (1 - i), c = cpos1 * i + cpos2 * (1 - i);
        gotoRowCol(r, c);
        cout << sym;
    }
}

// Display the logo
void nameLOGO(ifstream& rdr) {
    char sym = -37;
    int r = -1, c = -1;
    while (rdr) {
        rdr >> r >> c;
        gotoRowCol(r, c);
        color(MAGENTA);
        cout << sym;
    }
}

// Draw the boundary of the UI
void boundry() {
    color(YELLOW);
    char sym = -37;

    // Top line (for the logo area)
    for (int i = 0; i < 4; i++) {
        printLine(i, 0, i, 120, sym);
    }

    // Bottom line 
    for (int i = 37; i < 41; i++) {
        printLine(i, 0, i, 120, sym);
    }

    // Left gray bar 
    color(DARK_GRAY);
    for (int j = 0; j < 5; j++) {
        printLine(4, j, 36, j, sym);
    }

    // Right gray bar 
    color(DARK_GRAY);
    for (int j = 116; j < 120; j++) {
        printLine(4, j, 36, j, sym);
    }

    // Main white sheet 
    color(WHITE);
    for (int i = 4; i < 6; i++) {
        printLine(i, 5, i, 115, sym);
    }
    for (int i = 4; i < 37; i++) {
        printLine(i, 5, i, 12, sym);
    }
    for (int i = 35; i < 37; i++) {
        printLine(i, 5, i, 115, sym);
    }
    for (int i = 4; i < 37; i++) {
        printLine(i, 108, i, 115, sym);
    }

    printLine(29, 5, 29, 115, sym);
    color(RED);
    gotoRowCol(30, 13);
    cout << "PS C:\\Users\\ABDUL> ";
    color(BLACK);
    printLine(28, 35, 28, 105, sym); // Bottom fixture
}

// Display the UI
void UI(ifstream& rdr) {
    boundry();
    nameLOGO(rdr);
}

// Extract text after a delimiter
char* extractAfterDelimiter(char* input, char delimiter) {
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == delimiter) {
            return input + i + 1;
        }
    }
    return nullptr;
}

// Check if a command matches the input
int checkCommand(const char* input, const char* cmd) {
    while (*input && *cmd) {
        if (*input != *cmd)
            return 0;
        input++;
        cmd++;
    }
    return (*input == '\0' && *cmd == '\0');
}

// Manually copy a string
void manualStrCopy(char* dest, const char* src, int destSize) {
    int i = 0;
    while (src[i] != '\0' && i < destSize - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Undo the last operation
void undo(Document& document) {
    if (lastOperation == 0) {
        cout << "Nothing to undo.\n";
        return;
    }

    if (lastOperation == 1) {
        cout << "Undoing :upper...\n";
        Chapters* currentChapter = document.getCurrentChapter();
        if (currentChapter) {
            Sections* currentSection = currentChapter->getCurrentSection();
            if (currentSection) {
                Paragraph* currentParagraph = currentSection->getCurrentParagraph();
                if (currentParagraph) {
                    currentParagraph->lineToLower();
                }
            }
        }
        lastOperation = 2;
    }
    else if (lastOperation == 2) {
        cout << "Undoing :lower...\n";
        Chapters* currentChapter = document.getCurrentChapter();
        if (currentChapter) {
            Sections* currentSection = currentChapter->getCurrentSection();
            if (currentSection) {
                Paragraph* currentParagraph = currentSection->getCurrentParagraph();
                if (currentParagraph) {
                    currentParagraph->lineToUpper();
                }
            }
        }
        lastOperation = 1;
    }
    else if (lastOperation == 3) {
        cout << "Undoing :replace...\n";
        document.replaceAndHighlight(newWord, oldWord);
        lastOperation = 3;
    }

    canRedo = true;
    color(WHITE);
    document.displayDocument();
}

// Redo the last undone operation
void redo(Document& document) {
    if (!canRedo) {
        cout << "Nothing to redo.\n";
        return;
    }

    if (lastOperation == 1) {
        cout << "Redoing :upper...\n";
        Chapters* currentChapter = document.getCurrentChapter();
        if (currentChapter) {
            Sections* currentSection = currentChapter->getCurrentSection();
            if (currentSection) {
                Paragraph* currentParagraph = currentSection->getCurrentParagraph();
                if (currentParagraph) {
                    currentParagraph->lineToUpper();
                }
            }
        }
    }
    else if (lastOperation == 2) {
        cout << "Redoing :lower...\n";
        Chapters* currentChapter = document.getCurrentChapter();
        if (currentChapter) {
            Sections* currentSection = currentChapter->getCurrentSection();
            if (currentSection) {
                Paragraph* currentParagraph = currentSection->getCurrentParagraph();
                if (currentParagraph) {
                    currentParagraph->lineToLower();
                }
            }
        }
    }
    else if (lastOperation == 3) {
        cout << "Redoing :replace...\n";
        document.replaceAndHighlight(oldWord, newWord);
    }

    canRedo = false;
    color(WHITE);
    document.displayDocument();
}

// Process a command
void processCommand(char* input, Document& document) {
    color(GREEN);
    gotoRowCol(31, 13);

    if (checkCommand(input, ":w")) {
        cout << "Saving file...\n";
        document.saveToFile();
    }
    else if (checkCommand(input, ":q")) {
        cout << "Quitting editor...\n";
        Sleep(1000);
        exit(0);
    }
    else if (checkCommand(input, ":wq")) {
        cout << "Saving and quitting...\n";
        document.saveToFile();
        Sleep(1000);
        exit(0);
    }
    else if (checkCommand(input, ":q!")) {
        cout << "Force quitting without saving...\n";
        exit(0);
    }
    else if (input[0] == ':' && input[1] == 's' && input[2] == '/') {
        char* searchText = extractAfterDelimiter(input, '/');
        cout << searchText << endl;
        if (searchText) {
            if (document.search(searchText)) {
                gotoRowCol(31, 13);
                cout << "Pattern found....\n";
                document.DisplayHighlightDocument(searchText);
            }
            else {
                gotoRowCol(31, 13);
                color(RED);
                cout << "Pattern not found.\n";
            }
        }
    }
    else if (checkCommand(input, ":copy")) {
        cout << "Current Line Copied...\n";
        Paragraph* currentParagraph = document.getCurrentChapter()->getCurrentSection()->getCurrentParagraph();
        if (currentParagraph) {
            currentParagraph->copyCurrentLine();
        }
    }
    else if (checkCommand(input, ":paste")) {
        cout << "Previously Copied Line Pasted...\n";
        Paragraph* currentParagraph = document.getCurrentChapter()->getCurrentSection()->getCurrentParagraph();
        if (currentParagraph) {
            currentParagraph->pasteCopiedLine();
        }
        color(WHITE);
        document.displayDocument();
    }
    else if (input[0] == ':' && input[1] == 'r' && input[2] == '@') {
        cout << "Replaced and Highlighted...";
        char* command = input + 3;
        char* oldText = command;
        char* newText = nullptr;

        for (int i = 0; command[i] != '\0'; i++) {
            if (command[i] == '/') {
                command[i] = '\0';
                newText = command + i + 1;
                break;
            }
        }

        if (oldText && newText) {
            manualStrCopy(oldWord, oldText, sizeof(oldWord));
            manualStrCopy(newWord, newText, sizeof(newWord));
            lastOperation = 3;
            canRedo = false;
            document.replaceAndHighlight(oldText, newText);
        }
    }
    else if (checkCommand(input, ":lineNumber")) {
        Paragraph* currentParagraph = document.getCurrentChapter()->getCurrentSection()->getCurrentParagraph();
        if (currentParagraph) {
            int lineNumber = currentParagraph->getCurrentLineNumber();
            cout << "Current line number: " << lineNumber << "\n";
        }
        else {
            cout << "No current line found.\n";
        }
    }
    else if (checkCommand(input, ":upper")) {
        Chapters* currentChapter = document.getCurrentChapter();
        if (currentChapter) {
            Sections* currentSection = currentChapter->getCurrentSection();
            if (currentSection) {
                Paragraph* currentParagraph = currentSection->getCurrentParagraph();
                if (currentParagraph) {
                    currentParagraph->lineToUpper();
                }
            }
        }
        cout << "Current line to Upper...\n";
        color(WHITE);
        document.displayDocument();
        lastOperation = 1;
        canRedo = false;
    }
    else if (checkCommand(input, ":lower")) {
        Chapters* currentChapter = document.getCurrentChapter();
        if (currentChapter) {
            Sections* currentSection = currentChapter->getCurrentSection();
            if (currentSection) {
                Paragraph* currentParagraph = currentSection->getCurrentParagraph();
                if (currentParagraph) {
                    currentParagraph->lineToLower();
                }
            }
        }
        cout << "Current line to Lower...\n";
        color(WHITE);
        document.displayDocument();
        lastOperation = 2;
        canRedo = false;
    }
    else if (checkCommand(input, ":undo")) {
        undo(document);
    }
    else if (checkCommand(input, ":redo")) {
        redo(document);
    }
    else {
        color(RED);
        cout << "Unknown command: " << input << "\n";
    }
}

// Reset the terminal
void TerReSet() {
    Sleep(1500);
    char sym = -37;
    color(BLACK);
    printLine(30, 32, 30, 60, sym);
    printLine(31, 13, 31, 50, sym);
    color(WHITE);

    for (int i = 33; i < 60; i++) {
        gotoRowCol(29, i);
        cout << sym;
    }
    color(YELLOW);
}

// Handle terminal input
void IFinTer(int r, int c) {
    gotoRowCol(30, 32);
    char input[40] = { 0 };
    int index = 0;
    char ch;

    while (true) {
        color(YELLOW);
        ch = _getch();

        if (ch == 27) {
            TerReSet();
            inTerminal = false;
            return;
        }
        else if (ch == '\r') {
            break;
        }
        else if (ch == '\b' && index > 0) {
            cout << "\b \b";
            index--;
        }
        else if (index < 29) {
            cout << ch;
            input[index++] = ch;
        }
    }
    input[index] = '\0';
    processCommand(input, document);
    TerReSet();
}

// Check if the cursor is within the sheet limits
bool SheetLimiter(int r, int c) {
    if (r < 6 || r > 28 || c < 13 || c > 107) {
        return false;
    }
    return true;
}

// Check if the cursor is within the terminal limits
bool TerminalLimiter(int r, int c) {
    if (r < 30 || r > 34 || c < 13 || c > 107) {
        return false;
    }
    IFinTer(r, c);
    return true;
}

// Handle terminal input
void handleTerminalInput() {
    int r = 30, c = 32;
    IFinTer(r, c);
}

// Handle sheet input
void handleSheetInput(Document& document) {
    processInput(document);
}

// Process input
void processInput(Document& document) {
    char ch;
    while (true) {
        color(WHITE);
        ch = _getch();

        if (ch == 27) {
            inTerminal = !inTerminal;
            if (inTerminal) {
                handleTerminalInput();
            }
            else {
                handleSheetInput(document);
            }
            continue;
        }

        if (inTerminal) {
            handleTerminalInput();
        }
        else {
            if (ch == '$') {
                document.getCurrentChapter()->addNewSection();
                document.displayDocument();
            }
            else if (ch == '#') {
                document.getCurrentChapter()->getCurrentSection()->addNewParagraph();
                document.displayDocument();
            }
            else if (ch == '(') {
                document.addNewChapter();
                document.displayDocument();
            }
            else if (ch == '\r') {
                Paragraph* currentParagraph = document.getCurrentChapter()->getCurrentSection()->getCurrentParagraph();
                currentParagraph->splitLine();
                document.displayDocument();
            }
            else if (ch == '\b') {
                Paragraph* currentParagraph = document.getCurrentChapter()->getCurrentSection()->getCurrentParagraph();
                if (currentParagraph->getCursorCol() > Line::getMinWidth()) {
                    currentParagraph->deleteChar();
                    document.displayDocument();
                }
                else if (currentParagraph->getCursorRow() > Line::getMinRow()) {
                    currentParagraph->moveCursorUp();
                    currentParagraph->moveCursorRight();
                    currentParagraph->deleteChar();
                    document.displayDocument();
                }
            }
            else if (ch == -32) {
                ch = _getch();
                switch (ch) {
                case 75:  // Left arrow
                    document.getCurrentChapter()->getCurrentSection()->getCurrentParagraph()->moveCursorLeft();
                    break;
                case 77:  // Right arrow
                    document.getCurrentChapter()->getCurrentSection()->getCurrentParagraph()->moveCursorRight();
                    break;
                case 72:  // Up arrow
                    document.getCurrentChapter()->getCurrentSection()->getCurrentParagraph()->moveCursorUp();
                    break;
                case 80:  // Down arrow
                    document.getCurrentChapter()->getCurrentSection()->getCurrentParagraph()->moveCursorDown();
                    break;
                }
                document.displayDocument();
            }
            else {
                document.getCurrentChapter()->getCurrentSection()->getCurrentParagraph()->insertChar(ch);
                document.displayDocument();
            }

            gotoRowCol(document.getCurrentChapter()->getCurrentSection()->getCurrentParagraph()->getCursorRow(),
                document.getCurrentChapter()->getCurrentSection()->getCurrentParagraph()->getCursorCol());
        }
    }
}

// Main function
int main() {
    ifstream rdr("cords.txt");
    UI(rdr);
    processInput(document);

    return 0;
}