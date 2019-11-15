#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  string s;
  int n;
  cin >> n;
  cin >> s;

  char max_c = 0;
  int max_c_pos = 0;
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] < max_c) {
      printf("YES\n%d %d\n", max_c_pos + 1, i + 1);
      return 0;
    }
    if (s[i] > max_c) {
      max_c = s[i];
      max_c_pos = i;
    }
  }
  printf("NO\n");
  return 0;
}
