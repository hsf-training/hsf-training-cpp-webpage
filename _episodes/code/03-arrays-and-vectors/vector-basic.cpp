#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<double> n_vector {2., 3., 4., -10.};
  cout << "This n-vector has time component " << n_vector[3] << endl;

  n_vector[3] = 7.5;
  cout << "This n-vector now has time component " << n_vector[3] << endl;

  n_vector[0]++;
  cout << "The first element of the vector is " << n_vector.front() <<
  " and the last is " << n_vector.back() << endl;
  cout << "The vector size is " << n_vector.size() << endl;

  return 0;
}
