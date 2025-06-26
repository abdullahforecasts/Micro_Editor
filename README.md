# Micro Text Editor

![Micro Editor](https://img.shields.io/badge/Micro_Editor-C%2B%2B-blue.svg)

## Link

[🔥 Check Out the Video ](https://drive.google.com/file/d/1BjlXAsyoOt3c44gXufRRSgOp82xzGB-R/view?usp=sharing)

## Table of Contents
- [Description](#description)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Keyboard Shortcuts](#keyboard-shortcuts)
- [Example Commands](#example-commands)
- [Requirements](#requirements)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [Author](#author)

## Description
Micro is a lightweight text editor with a terminal-like interface, designed for simple and efficient text editing. It supports various features including text manipulation, search and replace, undo/redo functionality, and more.

## Features

### Basic Text Editing
- Insert, delete, and edit text
- Navigate using arrow keys
- Split lines with the `Enter` key
- Word wrapping

### Document Structure
- Support for chapters, sections, and paragraphs
- Add new chapters with `(`
- Add new sections with `$`
- Add new paragraphs with `#`

### Text Manipulation
- Convert current line to uppercase `(:upper)`
- Convert current line to lowercase `(:lower)`
- Copy `(:copy)` and paste `(:paste)` the current line
- Search within the document `(:s/pattern)`
- Replace text `(:r@old/new)`

### File Operations
- Save document `(:w)`
- Quit `(:q)`
- Save and quit `(:wq)`
- Force quit without saving `(:q!)`

### Undo/Redo
- Undo last operation `(:undo)`
- Redo last undone operation `(:redo)`

### Cursor Information
- Display current line number `(:lineNumber)`

## Installation
### Clone the repository:
```sh
git clone https://github.com/abdullahforecasts/Micro_Editor.git
```

### Compile the project:
```sh
g++ -o micro Bscs24009_Micro.cpp bscs24009_Document.cpp bscs24009_Chapters.cpp bscs24009_Sections.cpp bscs24009_Paragraph.cpp bscs24009_Line.cpp -std=c++11
```

### Run the executable:
```sh
./micro
```

## Usage
The editor has two modes:
- **Sheet Mode**: Default mode for editing text
- **Terminal Mode**: For entering commands (press `ESC` to toggle)

### In Sheet Mode:
- Use arrow keys to navigate
- Type normally to insert text
- Use `Backspace` to delete

### In Terminal Mode:
- Enter commands prefixed with `:`
- Press `ESC` to return to sheet mode

## Keyboard Shortcuts
| Key          | Function                                   |
|-------------|-------------------------------------------|
| `ESC`       | Toggle between sheet and terminal modes  |
| `Enter`     | Split line at cursor position            |
| `Backspace` | Delete character                         |
| `Arrow Keys`| Move cursor                              |
| `(`         | Add new chapter                          |
| `$`         | Add new section                          |
| `#`         | Add new paragraph                        |

## Example Commands
- `:w` - Save document
- `:q` - Quit editor
- `:s/searchtext` - Search for "searchtext"
- `:r@old/new` - Replace "old" with "new"
- `:upper` - Convert current line to uppercase
- `:undo` - Undo last operation

## Requirements
- Windows OS (uses `<windows.h>` for console operations)
- C++ compiler (tested with g++)

## Project Structure
```
Micro_Editor/
├── Bscs24009_Micro.cpp          # Main entry point
├── bscs24009_Document.cpp       # Document handling
├── bscs24009_Document.h         # Document header
├── bscs24009_Chapters.cpp       # Chapter management
├── bscs24009_Chapters.h         # Chapter header
├── bscs24009_Sections.cpp       # Sections handling
├── bscs24009_Sections.h         # Sections header
├── bscs24009_Paragraph.cpp      # Paragraph management
├── bscs24009_Paragraph.h        # Paragraph header
├── bscs24009_Line.cpp           # Line operations
├── bscs24009_Line.h             # Line header
└── README.md                    # Documentation
```

## Contributing
Contributions are welcome! Please fork the repository and submit a pull request with your changes.

## Author
[Abdullah](https://github.com/abdullahforecasts)

Happy Coding! 🚀

