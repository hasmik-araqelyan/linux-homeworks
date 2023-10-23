#include <iostream>
#include "complex.h"

    // operator for subtraction
    Complex Complex :: operator-(const Complex& complex){
      return Complex(real - complex.real, unreal - complex.unreal);
    }

    // operator for addition
    Complex Complex :: operator+(const Complex& complex){
      return Complex(real + complex.real, unreal + complex.unreal);
    }

    // operator for multiplication by a constant
    Complex Complex :: operator*(int constant){
      return Complex(real * constant, unreal * constant);
    }
