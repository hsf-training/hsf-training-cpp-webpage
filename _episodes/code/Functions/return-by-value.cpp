#include <iostream>
#include <vector>

std::vector<int> scale( std::vector<int> col, int factor )
 {
  for ( unsigned i = 0 ; i < col.size() ; ++i )
   { col[i] *= factor ; }
  return col ;
 }

void display( const std::vector<int> & col )
 {
  std::cout << "[ " ;
  for ( unsigned i = 0 ; i < col.size() ; ++i )
   { std::cout << col[i] << " " ; }
  std::cout << "]" << std::endl ;
 }

int main()
 {
  std::vector input = { 1, 2, 3, 4, 5 } ;
  std::vector output = scale(input,2) ;
  display(output) ;
 }
