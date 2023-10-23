#include <iostream>
#include "complex.h"

bool Compare(const Complex& c1, const Complex& c2){
  // compare 2 complex numbers
  int complex1 = c1.real * c1.real + c1.unreal * c1.unreal;
  int complex2 = c2.real * c2.real + c2.unreal * c2.unreal;
  return complex1 > complex2;
}

void Sort(Complex arr[], int n){
  // the algorithm of sorting complex numbers
  for(int i = 0; i < n - 1; i++){
    for(int j = i + 1; j < n; j++){
      if(Compare(arr[i], arr[j])){
        Complex temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
}
