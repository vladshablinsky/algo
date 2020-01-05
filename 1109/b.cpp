#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 5002;
const int INF = 1e9;

string s;

bool check(const string &target) {
  bool all_same = true;
  for (int i = 0; i < target.length() / 2; ++i) {
    if (target[i] != target[0]) {
      all_same = false;
    }
    if (target[i] != target[(int)target.length() - i - 1]) {
      return false;
    }
  }
  return !all_same;
}

int main() {
  cin >> s;

  int ans = INF;
  if (check(s)) {
    ans = 2;
    for (int i = 1; i < (int)s.length() - 1; ++i) {
      string target = s.substr(i, s.length() - i);
      target += s.substr(0, i);
      if (check(target) && (target != s)) {
        ans = 1;
        break;
      }
    }
  }

  if (ans == INF) {
    cout << "Impossible\n";
  } else {
    cout << ans << "\n";
  }
  return 0;
}
