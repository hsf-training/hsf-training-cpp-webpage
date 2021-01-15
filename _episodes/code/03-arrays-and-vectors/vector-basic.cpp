#include <iostream>
#include <vector>

int main() {
  std::vector<double> n_vector {2., 3., 4., -10.};
  std::cout << "This n-vector has time component " << n_vector[3] << std::endl;

  n_vector[3] = 7.5;
  std::cout << "This n-vector now has time component " << n_vector[3] << std::endl;

  n_vector[0]++;
  std::cout << "The first element of the vector is " << n_vector.front() <<
  " and the last is " << n_vector.back() << std::endl;
  std::cout << "The vector size is " << n_vector.size() << std::endl;

  return 0;
}
