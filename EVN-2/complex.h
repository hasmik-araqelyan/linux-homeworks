#include <iostream>
#include <cmath>

class Complex{
  public:
    int real;
    int unreal;

  public:
    // construction
    Complex(int _real, int _unreal) : real(_real), unreal(_unreal){}

    // operator for subtraction
    Complex operator-(const Complex& complex);

    // operator for addition
    Complex operator+(const Complex& complex);

    // operator for multiplication by a constant
    Complex operator*(int constant);

    // absolute value
    double absolute(){
      return std::sqrt(real * real + unreal * unreal);
    }

    // print complex number
    void print(){
      if(unreal >= 0){
        std::cout << real << "+" << unreal << "i";
      }else{
        std::cout << real << "-" << (-1) * unreal << "i";
      }
    }
};
