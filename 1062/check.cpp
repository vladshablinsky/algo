#include <iostream>

using namespace std;

void f(int &a) {
  a = 1;
}

int main() {
  int x = 2;
  cout << x << endl;
  f(x);
  cout << x << endl;
  return 0;
}
