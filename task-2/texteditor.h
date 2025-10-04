#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <string>

// Abstract TextEditor interface
class TextEditor {
public:
    virtual ~TextEditor() {}
    virtual void insertChar(char c) = 0;
    virtual void deleteChar() = 0; // delete char before cursor (backspace)
    virtual void moveLeft() = 0;
    virtual void moveRight() = 0;
    virtual std::string getTextWithCursor() const = 0;
};

// Factory
extern "C" TextEditor* createTextEditor();

#endif // TEXTEDITOR_H
