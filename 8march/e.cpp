#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

vector<string> v;

int main() {
  string s;
  int max_len = 0;
  while (getline(cin, s)) {
    v.push_back(s);
    max_len = max(max_len, (int)s.length());
  }

  bool last_from_left = false;

  for (int i = 0; i < max_len + 2; ++i) {
    printf("*");
  }
  printf("\n");

  for (int i = 0; i < v.size(); ++i) {
    printf("*");

    if (v[i].length() == 0) {
      for (int j = 0; j < max_len; ++j) {
        printf(" ");
      }
      printf("*\n");
      continue;
    }

    int spaces = max_len - v[i].length();
    int left_spaces = spaces / 2;
    int right_spaces = spaces - left_spaces;

    if (left_spaces != right_spaces) {
      if (last_from_left) {
        last_from_left = false;
        swap(left_spaces, right_spaces);
      } else {
        last_from_left = true;
      }
    }

    for (int i = 0; i < left_spaces; ++i) {
      printf(" ");
    }
    cout << v[i];
    for (int i = 0; i < right_spaces; ++i) {
      printf(" ");
    }

    printf("*\n");
  }

  for (int i = 0; i < max_len + 2; ++i) {
    printf("*");
  }
  printf("\n");

  return 0;
}
