#include <iostream>
#include <array>

auto accumulate( const auto & col, auto init )
 {
  auto res = init ;
  for ( auto elem : col )
   { res += elem ; }
  return res ;
 }

int main()
 {
  std::array col = { 1, 2, 3, 4, 5 } ;
  std::cout << accumulate(col,0) << std::endl ;
 }
