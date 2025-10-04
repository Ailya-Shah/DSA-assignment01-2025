#include "texteditor.h"
#include <vector>
#include <string>

// Concrete implementation: use two vectors (left and right) - efficient cursor ops
class ConcreteTextEditor : public TextEditor {
private:
    std::vector<char> left;  // characters to left of cursor (left.back() is immediately left)
    std::vector<char> right; // characters to right of cursor (right.back() is far right)
public:
    ConcreteTextEditor() = default;
    virtual ~ConcreteTextEditor() {}

    void insertChar(char c) override {
        left.push_back(c);
    }

    void deleteChar() override {
        if (!left.empty()) left.pop_back();
    }

    void moveLeft() override {
        if (!left.empty()) {
            char c = left.back();
            left.pop_back();
            right.push_back(c);
        }
    }

    void moveRight() override {
        if (!right.empty()) {
            char c = right.back();
            right.pop_back();
            left.push_back(c);
        }
    }

    std::string getTextWithCursor() const override {
        std::string s;
        for (char c : left) s.push_back(c);
        s.push_back('|');
        // right is stored with oldest at index 0; but we appended using push_back so right.back() is last moved char.
        // We want to print right in reverse of storing (since we push_back when moving left).
        for (auto it = right.rbegin(); it != right.rend(); ++it) s.push_back(*it);
        return s;
    }
};

extern "C" TextEditor* createTextEditor() {
    return new ConcreteTextEditor();
}
