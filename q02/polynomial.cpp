#include <iostream>
#include "polynomial.h"

using namespace std;

// Default constructor
// constructs a first-order polynomial with all coefficients set to 1.
Polynomial::Polynomial (): Polynomial(1) {}

// One-parameter constructor
// constructs a polynomial of user-supplied order with all coefficients set to 1.
Polynomial::Polynomial (unsigned int order) {
    a_ = new float[(order_ = order) + 1];
    for (unsigned int i = 0; i <= order_; i++) a_[i] = 1.;
}

// helper function to copy - IMPLEMENT ME
void Polynomial::copy_(const Polynomial &p) {
    delete []a_;
    a_ = new float[(order_ = p.order_) + 1];
    for (unsigned int i = 0; i <= order_; i++) a_[i] = p.a_[i];
}

// helper function to destroy - IMPLEMENT ME
void Polynomial::destroy_() { delete []a_; a_ = NULL; }

// Copy constructor - must use copy_() function
// constructs a new polynomial that is a copy of an existing polynomial
Polynomial::Polynomial (const Polynomial &other): a_(NULL) { copy_(other); }

// Destructor - must use destroy_() function
// destroys a polynomial object
Polynomial::~Polynomial () { destroy_(); }

// Assignment operator - must use copy_() function
// assigns rhs Polynomial object to 'this' Polynomial object
const Polynomial &Polynomial::operator= (const Polynomial &other) {
    if (this != &other) copy_(other);
    return *this;
}

// getPolyOrder
// returns the polynomial order
unsigned int Polynomial::getPolyOrder () const { return order_; }

// getCoeff
// returns the coefficient of the x^i term in polynomial
// note: If the object does not contain a term with power i (e.g., 
//       i>order_), a coefficient value of zero is returned.
float Polynomial::getCoeff (unsigned int i) const {
    if (i > order_) return 0.;
    return a_[i];
}

// setCoeff
// If i <= order_, set a term, value*x^i, in a polynomial
bool Polynomial::setCoeff (unsigned int i, float value) const {
    if (i > order_) return false;
    return a_[i] = value, true;
}

// addition operator
// adds two polynomials together and returns a new polynomial 
Polynomial Polynomial::operator+ (const Polynomial &other) const {
    Polynomial result;
    if (order_ > other.order_) {
        result = *this;
        for (unsigned int i = 0; i <= other.order_; i++)
            result.a_[i] += other.a_[i];
    } else {
        result = other;
        for (unsigned int i = 0; i <= order_; i++)
            result.a_[i] += a_[i];
    }
    return result;
}

// insertion operator for output
// note: This function has been provided for you -- DO NOT CHANGE IT!
ostream & operator << (ostream &out, const Polynomial& p)
{
    bool printed = false;
    for (int i = p.order_; i >= 0; i--) {
        float c = p.a_[i];
        if (c != 0.0) {
            if (printed) out << " + ";
            printed = true;
            out << c << "*X^" << i;
        }
    }
    return out;
}
