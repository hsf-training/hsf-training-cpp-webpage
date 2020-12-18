#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<double> n_vector {};
  n_vector.push_back(1.5);
  n_vector.push_back(2.7);

  cout << "Vector elements are " << n_vector[0] << " and " << n_vector[1] <<
  " and the size is " << n_vector.size() << endl;

  n_vector.push_back(3.9);
  cout << "Vector now has " << n_vector.size() << " elements and the last value is " << n_vector[n_vector.size()-1] << endl;

  return 0;
}
