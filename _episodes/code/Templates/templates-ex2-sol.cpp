#include <iostream>

template<typename  T>
T abs( T val ) {
  const T ZERO = 0 ;
  if ( val > ZERO ) { return val ; }
  else { return (-val) ; }
}

template<typename T>
const T EPSILON =0;

template<>
const float EPSILON<float> = 1e-6;

template<>
const double EPSILON<double> = 1e-13;

template<typename T>
bool equal( T v1, T v2 ) {
  return (v1==v2) ;
}

template<>
bool equal( float v1, float v2 ) {
  return (abs(v1-v2)<EPSILON<float>) ;
}

template<>
bool equal( double v1, double v2 ) {
  return (abs(v1-v2)<EPSILON<double>) ;
}

int main() {
  float val = 1.0, tenth = val/10, sum = 0.0 ;
  for ( int i = 0 ; i<10 ; ++i ) {
    sum += tenth ;
  }
  if (equal(val,sum)) {
    std::cout<<"1. == 1./10 + 1./10 + ..." ;
  }
  else {
    std::cout<<"1. != 1./10 + 1./10 + ..." ;
  }
}
