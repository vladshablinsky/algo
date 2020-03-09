#include <iostream>

void print_float_bits(float x) {
  for (int i = 0; i < 32; ++i) {
    std::cout << bool((1 << i) & *static_cast<int*>(static_cast<void*>(&x)));
  }
  std::cout << "\n";
}

int main() {
  float x = 1.14;
  int y = x * 100;
  std::cout << y << "\n";
  std::cout << x * 100 << std::endl;
  print_float_bits(x);
  print_float_bits(x * 100);
  return 0;
}
