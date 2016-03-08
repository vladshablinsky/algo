#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

int char_cnt[30];

int main() {
  int k;
  string s;
  string ans;
  cin >> k;
  cin >> s;
  for (int i = 0; i < s.length(); ++i) {
    char_cnt[s[i] - 'a']++;
  }

  for (int i = 0; i < 26; ++i) {
    if (char_cnt[i] % k != 0) {
      printf("-1\n");
      return 0;
    }
    int cnt = char_cnt[i] / k;
    for (int j = 0; j < cnt; ++j) {
      ans.push_back('a' + i);
    }
  }

  if (((int) ans.length()) * k != s.length()) {
    printf("-1\n");
    return 0;
  } else {
    for (int i = 0; i < k; ++i) {
      cout << ans;
    }
    cout << "\n";
  }
  return 0;
}
