#include "polynomial.h"
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using std::map;
using std::string;
using std::ostringstream;

// Concrete implementation using map<exponent, coefficient>
class ConcretePolynomial : public Polynomial {
private:
    // map exponent -> coefficient (keeps sorted by exponent ascending)
    std::map<int,int> terms;

    static string termToString(int coeff, int exp) {
        if (coeff == 0) return "";
        std::ostringstream os;
        // sign handled by caller
        int a = abs(coeff);
        if (exp == 0) {
            os << a;
        } else if (exp == 1) {
            if (a == 1) os << "x";
            else os << a << "x";
        } else {
            if (a == 1) os << "x^" << exp;
            else os << a << "x^" << exp;
        }
        return os.str();
    }

public:
    ConcretePolynomial() = default;
    virtual ~ConcretePolynomial() {}

    void insertTerm(int coefficient, int exponent) override {
        if (coefficient == 0) return;
        terms[exponent] += coefficient;
        if (terms[exponent] == 0) terms.erase(exponent);
    }

    string toString() const override {
        if (terms.empty()) return "0";
        // produce descending exponents
        std::vector<std::pair<int,int>> v(terms.begin(), terms.end());
        std::reverse(v.begin(), v.end());
        std::ostringstream os;
        bool first = true;
        for (auto &p : v) {
            int exp = p.first;
            int coeff = p.second;
            if (coeff == 0) continue;
            if (!first) {
                os << (coeff > 0 ? " + " : " - ");
            } else {
                if (coeff < 0) os << "-";
            }
            os << termToString(coeff, exp);
            first = false;
        }
        return os.str();
    }

    Polynomial* add(const Polynomial& other) const override {
        // dynamic_cast to our concrete to access internal map; fallback by parsing toString if not same type
        const ConcretePolynomial* o = dynamic_cast<const ConcretePolynomial*>(&other);
        ConcretePolynomial* res = new ConcretePolynomial();
        // copy this
        for (auto &p : terms) res->terms[p.first] = p.second;
        if (o) {
            for (auto &p : o->terms) res->terms[p.first] += p.second;
            // remove zeros
            std::vector<int> toErase;
            for (auto &q : res->terms) if (q.second == 0) toErase.push_back(q.first);
            for (int e : toErase) res->terms.erase(e);
        } else {
            // fallback parse other.toString() (rare)
            // For simplicity, not implemented — assume add is called with same concrete type
        }
        return res;
    }

    Polynomial* multiply(const Polynomial& other) const override {
        const ConcretePolynomial* o = dynamic_cast<const ConcretePolynomial*>(&other);
        ConcretePolynomial* res = new ConcretePolynomial();
        if (o) {
            for (auto &a : terms) {
                for (auto &b : o->terms) {
                    int newExp = a.first + b.first;
                    int newCoeff = a.second * b.second;
                    res->terms[newExp] += newCoeff;
                }
            }
            // remove zeros
            std::vector<int> toErase;
            for (auto &q : res->terms) if (q.second == 0) toErase.push_back(q.first);
            for (int e : toErase) res->terms.erase(e);
        }
        return res;
    }

    Polynomial* derivative() const override {
        ConcretePolynomial* res = new ConcretePolynomial();
        for (auto &p : terms) {
            int exp = p.first;
            int coeff = p.second;
            if (exp == 0) continue;
            res->terms[exp - 1] += coeff * exp;
        }
        // remove zeros
        std::vector<int> toErase;
        for (auto &q : res->terms) if (q.second == 0) toErase.push_back(q.first);
        for (int e : toErase) res->terms.erase(e);
        return res;
    }
};

extern "C" Polynomial* createPolynomial() {
    return new ConcretePolynomial();
}
