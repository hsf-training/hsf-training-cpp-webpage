#include <iostream>
#include <vector>

void scale( std::vector<int> & col, int factor )
 {
  for ( auto & elem : col )
   { elem *= factor ; }
 }

int main()
 {
  std::vector col = { 1, 2, 3, 4, 5 } ;
  scale(col,2) ;
  auto first = col[0] ;
  std::cout << first << std::endl ;
 }
