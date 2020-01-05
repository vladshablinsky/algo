#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const int ALPH = 26;
const int MAXN = 10005;

int ans[MAXN];

int main() {
  string s;
  cin >> s;
  int n = s.length();

  int cur_p = 1;
  for (int j = 0; j < 3; ++j) {
    string cur_q;
    for (int i = 0; i < n; ++i) {
      int offset = (i / cur_p) % ALPH;
      cur_q.push_back('a' + offset);
    }

    cout << "? " << cur_q << "\n";
    string cur_a;
    cin >> cur_a;
    for (int i = 0; i < n; ++i) {
      //cout << "i: " << i << ", cur_a[i]: " << cur_a[i];
      ans[i] += int(cur_a[i] - 'a') * cur_p;
      //cout << ", ans[i]" << ans[i] << endl;
    }

    cur_p *= ALPH;
  }

  string result = s;
  for (int i = 0; i < n; ++i) {
    result[ans[i]] = s[i];
  }

  cout << "! " << result << "\n";
  fflush(stdout);
  return 0;
}
