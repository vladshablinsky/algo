#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  int pow = 2;
  int cnt_left = n;
  while (cnt_left) {
    int cnt_div = cnt_left / 2;
    int cnt_not_div = cnt_left - cnt_div;
    for (int i = 0; i < cnt_not_div - 1; ++i) {
      cout << pow / 2 << " ";
    }

    if (cnt_div == 1 && cnt_not_div == cnt_div + 1) {
      cout << pow / 2 << " " << pow / 2 + pow << " ";
      cnt_left = 0;
    } else {
      cout << pow / 2 << " ";
      cnt_left = cnt_div;
    }
    pow *= 2;
  }
  cout << "\n";
  return 0;
}
