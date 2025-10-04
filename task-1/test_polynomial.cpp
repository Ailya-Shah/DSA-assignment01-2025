#include "polynomial.h"
#include <iostream>

extern "C" Polynomial* createPolynomial();

int main() {
    Polynomial* p1 = createPolynomial();
    p1->insertTerm(3, 4);
    p1->insertTerm(2, 2);
    p1->insertTerm(-1, 1);
    p1->insertTerm(5, 0);

    Polynomial* p2 = createPolynomial();
    p2->insertTerm(1, 4);
    p2->insertTerm(1, 0);

    Polynomial* sum = p1->add(*p2);
    Polynomial* p3 = createPolynomial();
    p3->insertTerm(2, 1);

    Polynomial* prod = sum->multiply(*p3);
    Polynomial* deriv = p1->derivative();

    std::cout << "p1.toString(): " << p1->toString() << std::endl;
    std::cout << "sum.toString(): " << sum->toString() << std::endl;
    std::cout << "prod.toString(): " << prod->toString() << std::endl;
    std::cout << "deriv.toString(): " << deriv->toString() << std::endl;

    delete p1;
    delete p2;
    delete p3;
    delete sum;
    delete prod;
    delete deriv;
}

