#include <iostream>
#include <cstdio>

using namespace std;

int main() {
  int n;
  int cnt_eights = 0;
  int cnt_turns = 0;
  int idx = 0;
  string s;
  cin >> n;
  cin >> s;

  cnt_turns = n - 11;

  for (int i = 0; i < s.length(); ++i) {
    if (s[i] == '8') {
      idx = i;
      ++cnt_eights;
    }

    if (cnt_eights > cnt_turns / 2) {
      break;
    }
  }

  if (cnt_eights <= cnt_turns / 2 || idx > cnt_turns) {
    cout << "NO\n";
  } else {
    cout << "YES\n";
  }
  return 0;
}
