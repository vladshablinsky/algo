#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

bool is_even(char c) {
  return (c - '0') % 2 == 0;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    string s;
    cin >> s;
    if (is_even(s.back())) {
      printf("0\n");
    } else if (is_even(s.front())) {
      printf("1\n");
    } else if (find_if(s.begin(), s.end(), [](char& c) { return is_even(c); }) != s.end()) {
      printf("2\n");
    } else {
      printf("-1\n");
    }
  }
}
