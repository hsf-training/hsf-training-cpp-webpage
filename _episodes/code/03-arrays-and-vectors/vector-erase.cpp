#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<double> n_vector {-1.0, -2.0, -3.0, -4.0, -5.0};

  n_vector.erase(n_vector.begin()+2);
  cout << "After single erase the third vector element is " << n_vector[2] <<
  " and the size is " << n_vector.size() << endl;

  n_vector.erase(n_vector.begin()+2, n_vector.end());
  cout << "After a block erase the vector size is " << n_vector.size() << endl;

  return 0;
}
