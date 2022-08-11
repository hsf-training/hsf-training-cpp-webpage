#include <iostream>

template<typename  T>
T abs( T val ) {
  const T ZERO = 0 ;
  if ( val > ZERO ) { return val ; }
  else { return (-val) ; }
}

template<typename T>
bool equal( T v1, T v2 ) {
  return (v1==v2) ;
}

// COMPLETE HERE: EPSILON definition for float and double

// REPLACE BELOW: the single specialization with two
// specializations, one for float, and the other for double

using real = double ;

template<>
bool equal( real v1, real v2 ) {
  const real EPSILON = 1e-13 ;
  return (abs(v1-v2)<EPSILON<double>) ;
}

// REPLACE BELOW: real by float, so to validate
// that the equality is now true also for float

int main() {
  real val = 1.0, tenth = val/10, sum = 0.0 ;
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
