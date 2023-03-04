#include <iostream>
#include "cubic.h"

using namespace std;

Cubic::Cubic (): Polynomial(3u) {}

Cubic::Cubic (float a3, float a2, float a1, float a0): Polynomial(3u) {
    setCoeff(3u, a3), setCoeff(2u, a2),
    setCoeff(1u, a1), setCoeff(0u, a0);
}