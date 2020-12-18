#include <iostream>
#include <vector>

int accumulate( const std::vector<int> & col, const int & init )
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
