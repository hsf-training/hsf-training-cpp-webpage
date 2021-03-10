#include <iostream>

template<typename  T, int sz>
class Vector {
  public:
    T data[sz] ;
};

template<int sz>
using VectorDouble = Vector<double,sz> ;

template<typename T>
using Vector3 = Vector<T,3> ;

// COMPLETE HERE

int main() {
  Vector3<int> v1 = { 6*7, 3*14, 2*21 } ;
  VectorDouble<2> v2 = { 3.14, 1.62};
  display(v1) ;
  display(v2) ;
}
