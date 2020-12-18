#include <iostream>
#include <vector>
#include <tuple>

std::tuple<double,double,double> analyse( const std::vector<double> & data )
 {
  double min {999.}, max{0}, sum {0} ;
  for ( unsigned i = 0 ; i < data.size() ; ++i )
   {
    sum += data[i] ;
    if (data[i]<min ) min = data[i] ;
    if (data[i]>max ) max = data[i] ;
   }
  return { min, max, sum/data.size() } ;
 }

int main()
 {
  std::vector<double> data = { 1., 2., 3., 4., 5., 6. } ;
  
  double min, max, mean ;
  std::tie(min,max,mean) = analyse(data) ;
  
  std::cout << "min : " << min << std::endl ;
  std::cout << "max : " << max << std::endl ;
  std::cout << "mean: " << mean << std::endl ;
 }
