#include <iostream>
#include <vector>

auto accumulate( const std::vector<int> & col, int init )
 {
  auto res = init ;
  for ( auto elem : col )
   { res += elem ; }
  return res ;
 }

int main()
 {
  std::vector col = { 1, 2, 3, 4, 5 } ;
  std::cout << accumulate(col,0) << std::endl ;
 }
