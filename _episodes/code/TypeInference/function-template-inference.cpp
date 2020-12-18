#include <iostream>
#include <vector>

template< typename Num >
Num mean( const std::vector<Num> & col )
 {
  int sz = col.size() ;
  Num res = 0 ;
  for ( Num elem : col ) { res += elem ; }
  return res/sz ;
 }

int main()
 {
  std::vector<int> col = { 1, 2, 3, 4, 5 } ;
  std::cout << mean(col) << std::endl ;
 }
