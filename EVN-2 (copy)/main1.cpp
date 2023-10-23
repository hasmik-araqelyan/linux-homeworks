#include <iostream> 
#include "bubbleSort.h" 
 
int main() { 
  Complex c1(3, 1); 
  Complex c2(2, 13); 
  Complex c3(5, 12); 
  int constant = 5; 
 
  Complex add = c1 + c2; 
  Complex sub = c1 - c2; 
  Complex mul = c1 * constant; 
 
  add.print(); 
  std::cout << std::endl; 
  sub.print(); 
  std::cout << std::endl; 
  mul.print(); 
  std::cout << std::endl; 
 
  // array sorting 
  int n = 4; 
  Complex arr[] = {Complex(3, 5), Complex(2, 7), Complex(2, 4), Complex(7, 3)}; 
  Sort(arr, n); 
 
  for(int i = 0; i < n; i++){ 
    arr[i].print(); 
    std::cout << " "; 
  } 
}
