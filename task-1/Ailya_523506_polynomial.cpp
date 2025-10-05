#include "polynomial.h"
#include <iostream>
#include <sstream>
#include <cmath>

using std::string;
using std::ostringstream;
//node structure for linked list
struct Node {
    int coeff;
    int exp;
    Node* next;
    Node(int c, int e) : coeff(c), exp(e), next(nullptr) {}
};

class LinkedPolynomial : public Polynomial {
private:
    Node* head;

    static string termToString(int coeff, int exp) {
        if (coeff == 0) return "";
        ostringstream os;
        int absCoeff = std::abs(coeff);

        if (exp == 0)
            os << absCoeff;
        else if (exp == 1)
            os << (absCoeff == 1 ? "x" : std::to_string(absCoeff) + "x");
        else
            os << (absCoeff == 1 ? "x^" + std::to_string(exp)
                                 : std::to_string(absCoeff) + "x^" + std::to_string(exp));
        return os.str();
    }

    void insertSorted(int c, int e) {
        if (c == 0) return;

        Node* newNode = new Node(c, e);
        if (!head || e > head->exp) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* curr = head;
        Node* prev = nullptr;
        while (curr && curr->exp > e) {
            prev = curr;
            curr = curr->next;
        }

        if (curr && curr->exp == e) {
            curr->coeff += c;
            delete newNode;
            if (curr->coeff == 0) { // remove zero node
                if (prev) prev->next = curr->next;
                else head = curr->next;
                delete curr;
            }
        } else {
            newNode->next = curr;
            if (prev) prev->next = newNode;
            else head = newNode;
        }
    }

public:
    LinkedPolynomial() : head(nullptr) {}
    ~LinkedPolynomial() {
        Node* curr = head;
        while (curr) {
            Node* tmp = curr;
            curr = curr->next;
            delete tmp;
        }
    }

    void insertTerm(int coefficient, int exponent) override {
        insertSorted(coefficient, exponent);
    }

    string toString() const override {
        if (!head) return "0";
        ostringstream os;
        Node* curr = head;
        bool first = true;
        while (curr) {
            if (curr->coeff != 0) {
                if (!first)
                    os << (curr->coeff > 0 ? " + " : " - ");
                else if (curr->coeff < 0)
                    os << "-";

                os << termToString(curr->coeff, curr->exp);
                first = false;
            }
            curr = curr->next;
        }
        return os.str();
    }

    Polynomial* add(const Polynomial& other) const override {
        const LinkedPolynomial* o = dynamic_cast<const LinkedPolynomial*>(&other);
        LinkedPolynomial* result = new LinkedPolynomial();

        Node* a = head;
        Node* b = o ? o->head : nullptr;

        while (a || b) {
            if (!b || (a && a->exp > b->exp)) {
                result->insertTerm(a->coeff, a->exp);
                a = a->next;
            } else if (!a || (b && b->exp > a->exp)) {
                result->insertTerm(b->coeff, b->exp);
                b = b->next;
            } else { // same exponent
                result->insertTerm(a->coeff + b->coeff, a->exp);
                a = a->next;
                b = b->next;
            }
        }

        return result;
    }

    Polynomial* multiply(const Polynomial& other) const override {
        const LinkedPolynomial* o = dynamic_cast<const LinkedPolynomial*>(&other);
        LinkedPolynomial* result = new LinkedPolynomial();

        for (Node* a = head; a; a = a->next) {
            for (Node* b = o->head; b; b = b->next) {
                result->insertTerm(a->coeff * b->coeff, a->exp + b->exp);
            }
        }
        return result;
    }

    Polynomial* derivative() const override {
        LinkedPolynomial* result = new LinkedPolynomial();
        for (Node* curr = head; curr; curr = curr->next) {
            if (curr->exp > 0)
                result->insertTerm(curr->coeff * curr->exp, curr->exp - 1);
        }
        return result;
    }
};

// Factory
extern "C" Polynomial* createPolynomial() {
    return new LinkedPolynomial();
}

