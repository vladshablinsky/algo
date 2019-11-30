#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>

using namespace std;

const int MAXN = 200005;

int digits[MAXN];

int main() {
  int n;
  string s, t;
  cin >> n;
  cin >> s;
  cin >> t;

  std::reverse(s.begin(), s.end());
  std::reverse(t.begin(), t.end());

  int carry = 0;
  // Add
  int i;
  for (i = 0; (i < n) || carry; ++i) {
    if (i < n) {
      digits[i] += (s[i] - 'a' + t[i] - 'a');
    }
    digits[i] += carry;
    carry = 0;
    if (digits[i] >= 26) {
      digits[i] -= 26;
      carry = 1;
    }
  }

  // Divide by 2
  while (i >= 0) {
    int rem = digits[i] & 1;
    digits[i] /= 2;
    if (rem) {
      digits[i - 1] += 26;
    }
    --i;
  }

  for (int j = n - 1; j >= 0; --j) {
    cout << char(digits[j] + 'a');
  }
  cout << "\n";
  return 0;
}
