#include <iostream>

int main() {
  long long a = 1000000000 * 1ll * 1000000000;
  long long b = 1000000000 * 1ll * 1000000000 + 2;
  std::cout << (double(a) == double(b));
  return 0;
}
