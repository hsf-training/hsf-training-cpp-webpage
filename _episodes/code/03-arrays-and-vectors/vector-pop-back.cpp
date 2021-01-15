#include <iostream>
#include <vector>

int main() {
  std::vector<double> n_vector {-1.0, -2.0, -3.0};
  n_vector.pop_back();

  std::cout << "After pop the last vector element is " << n_vector.back() <<
  " and the size is " << n_vector.size() << std::endl;

  return 0;
}
