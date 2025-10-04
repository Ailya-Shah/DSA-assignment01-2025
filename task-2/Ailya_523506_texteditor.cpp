#include "texteditor.h"
#include <string>
#include <sstream>

// Node for doubly linked list
struct Node {
    char data;
    Node* prev;
    Node* next;
    Node(char c) : data(c), prev(nullptr), next(nullptr) {}
};

class LinkedListTextEditor : public TextEditor {
private:
    Node* head;     // start of text
    Node* tail;     // end of text
    Node* cursor;   // cursor points to node *before* the '|'
    int length;

public:
    LinkedListTextEditor() : head(nullptr), tail(nullptr), cursor(nullptr), length(0) {}
    virtual ~LinkedListTextEditor() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    // Insert character at cursor position
    void insertChar(char c) override {
        Node* newNode = new Node(c);
        if (!head) {
            head = tail = newNode;
            cursor = newNode;
        } else if (!cursor) { // inserting at beginning
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
            cursor = newNode;
        } else {
            newNode->next = cursor->next;
            newNode->prev = cursor;
            if (cursor->next) cursor->next->prev = newNode;
            cursor->next = newNode;
            if (cursor == tail) tail = newNode;
            cursor = newNode;
        }
        length++;
    }

    // Delete char before cursor (backspace)
    void deleteChar() override {
        if (!cursor) return; // nothing before cursor
        Node* toDelete = cursor;
        if (toDelete->prev) toDelete->prev->next = toDelete->next;
        else head = toDelete->next;
        if (toDelete->next) toDelete->next->prev = toDelete->prev;
        else tail = toDelete->prev;
        cursor = toDelete->prev;
        delete toDelete;
        length--;
    }

    // Move cursor one char left
    void moveLeft() override {
        if (cursor) cursor = cursor->prev;
    }

    // Move cursor one char right
    void moveRight() override {
        if (!cursor) { // cursor before first
            if (head) cursor = head;
            return;
        }
        if (cursor->next) cursor = cursor->next;
    }

    // Build text with '|' showing cursor position
    std::string getTextWithCursor() const override {
        std::ostringstream os;
        Node* current = head;
        if (!cursor) os << "|"; // Cursor before first character
        while (current) {
            os << current->data;
            if (current == cursor) os << "|";
            current = current->next;
        }
        if (cursor == tail && tail) os << "|"; // Cursor at the end
        return os.str();
    }
};

// Factory function
extern "C" TextEditor* createTextEditor() {
    return new LinkedListTextEditor();
}

