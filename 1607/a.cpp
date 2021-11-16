#include <iostream>

using namespace std;

int mabs(int x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

int mapping[27];

int solve() {
  string kb;
  string s;

  cin >> kb;
  for (int i = 0; i < kb.size(); ++i) {
    mapping[kb[i]] = i;
  }
  cin >> s;
  int ans = 0;
  for (int i = 1; i < s.length(); ++i) {
    ans += mabs(mapping[s[i]] - mapping[s[i - 1]]);
  }
  return ans;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    printf("%d\n", solve());
  }
}
