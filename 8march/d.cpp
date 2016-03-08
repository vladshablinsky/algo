#include <iostream>
#include <string>
#include <cstdio>
#include <map>

using namespace std;

const int MAXN = 2e5 + 5;

map<char, int> mp;
bool used[MAXN];

int main() {
  string s;
  string t;
  cin >> s;
  cin >> t;

  int hooray = 0;
  int oops = 0;

  for (int i = 0; i < s.length(); ++i) {
    mp[s[i]]++;
  }

  for (int i = 0; i < t.length(); ++i) {
    if (mp[t[i]] > 0) {
      mp[t[i]]--;
      ++hooray;
      used[i] = true;
    }
  }

  for (int i = 0; i < t.length(); ++i) {
    if (used[i]) {
      continue;
    }

    if (t[i] >= 'a' && t[i] <= 'z' && mp['A' + t[i] -'a'] > 0) {
      mp['A' + t[i] - 'a']--;
      ++oops;
    } else if (mp['a' + t[i] - 'A'] > 0) {
      mp['a' + t[i] - 'A']--;
      ++oops;
    }
  }
  printf("%d %d\n", hooray, oops);

  return 0;
}
