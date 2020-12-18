#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<double> n_vector {-1.0, -2.0, -3.0, -4.0, -5.0};

  cout << "Vector initial size is " << n_vector.size() << endl;
  n_vector.clear();
  cout << "After a clear() the vector size is " << n_vector.size() << endl;

  return 0;
}
