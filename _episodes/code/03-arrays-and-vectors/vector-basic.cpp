#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<double> n_vector {2., 3., 4., -10.};
  cout << "This n-vector has time component " << n_vector[3] << endl;

  n_vector[3] = 7.5;
  cout << "This n-vector now has time component " << n_vector[3] << endl;

  return 0;
}
