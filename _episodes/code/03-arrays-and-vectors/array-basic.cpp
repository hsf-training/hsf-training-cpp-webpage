#include <iostream>
#include <array>

using namespace std;

int main() {
  array<double, 4> four_vector {2., 3., 4., -10.};
  cout << "This 4-vector has time component " << four_vector[3] << endl;

  four_vector[3] = 7.5;
  cout << "This 4-vector now has time component " << four_vector[3] << endl;

  return 0;
}
