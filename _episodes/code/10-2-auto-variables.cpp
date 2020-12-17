#include <iostream>
#include <array>

int main()
 {
  std::array col = { 1, 2, 3, 4, 5 } ;
  
  auto first = col[0] ;
  auto sz = col.size() ; // bug ? unsigned to signed
  int sum = 0 ;
  for ( auto elem : col )
   { sum += elem ; }
  
  std::cout << "first: " << first <<std::endl ;
  std::cout << "mean: " << sum/sz << std::endl ;
 }
