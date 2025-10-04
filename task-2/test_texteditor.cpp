#include "texteditor.h"
#include <iostream>

int main() {
    TextEditor* editor = createTextEditor();

    editor->insertChar('H');
    editor->insertChar('e');
    editor->insertChar('l');
    editor->insertChar('l');
    editor->insertChar('o');
    std::cout << "After typing Hello: " << editor->getTextWithCursor() << std::endl;

    editor->moveLeft();
    editor->moveLeft();
    editor->insertChar('X');
    std::cout << "After moving left twice and inserting X: " << editor->getTextWithCursor() << std::endl;

    editor->deleteChar();
    std::cout << "After deleting: " << editor->getTextWithCursor() << std::endl;

    editor->moveRight();
    editor->insertChar('!');
    std::cout << "After moving right and adding !: " << editor->getTextWithCursor() << std::endl;

    delete editor;
    return 0;
}


