#include <iostream>

using namespace std;

int main() {

  int n = 10;
  bool flag = true;
  for (int i = 0; i < n; ++i) {
    cout << "i is " << i << endl;
    if (flag) {
      i = 3;
      flag = false;
    }
  }
  return 0;
}
