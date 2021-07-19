#include <iostream>
#include <cstdio>

using namespace std;

const char* BOB = "BOB";
const char* ALICE = "ALICE";
const char* DRAW = "DRAW";

void solve() {
  int n;
  cin >> n;
  string s;
  cin >> s;

  bool is_central = (n % 2) != 0 && s[n / 2] == '0';
  int cnt_zeros = 0;
  for (auto c: s) {
    cnt_zeros += c == '0';
  }
  cnt_zeros -= is_central;

  const char* result;
  if (is_central && cnt_zeros) {
    result = ALICE;
  }
  else {
    result = BOB;
  }
  cout << result << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }

  return 0;
}
