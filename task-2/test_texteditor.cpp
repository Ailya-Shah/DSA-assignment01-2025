#include "texteditor.h"
#include <iostream>
using namespace std;

int main() {
    TextEditor* editor = createTextEditor(); // ✅ Factory creates the concrete class

    // Type the word "HELLO"
    editor->insertChar('H');
    editor->insertChar('E');
    editor->insertChar('L');
    editor->insertChar('L');
    editor->insertChar('O');
    cout << "After typing HELLO: " << editor->getTextWithCursor() << endl;

    // Move cursor left twice
    editor->moveLeft();
    editor->moveLeft();
    cout << "After moving cursor left twice: " << editor->getTextWithCursor() << endl;

    // Insert a character 'X' before 'L'
    editor->insertChar('X');
    cout << "After inserting X: " << editor->getTextWithCursor() << endl;

    // Delete one character (backspace)
    editor->deleteChar();
    cout << "After deleting one character: " << editor->getTextWithCursor() << endl;

    // Move cursor right once
    editor->moveRight();
    cout << "After moving cursor right once: " << editor->getTextWithCursor() << endl;

    delete editor; // Clean up
    return 0;
}


