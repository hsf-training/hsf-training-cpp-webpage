#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<double> n_vector {-1.0, -2.0, -3.0};
  n_vector.insert(n_vector.begin(), 100.0);

  cout << "The first vector element is " << n_vector[0] <<
  " and the size is " << n_vector.size() << endl;

  n_vector.insert(n_vector.begin()+1, 200.0);
  cout << "The second vector element is " << n_vector[1] <<
  " and the size is " << n_vector.size() << endl;

  return 0;
}
