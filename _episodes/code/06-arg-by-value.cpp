#include <iostream>
#include <vector>

void display( std::vector<int> col )
 {
  std::cout << "[ " ;
  for ( unsigned i = 0 ; i < col.size() ; ++i )
   { std::cout << col[i] << " " ; }
  std::cout << "]" << std::endl ;
 }

int main()
 {
  std::vector col = { 1, 2, 3, 4, 5 } ;
  display(col) ;
 }
