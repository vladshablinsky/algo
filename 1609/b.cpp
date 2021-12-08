#include <iostream>
#include <cstdio>

using namespace std;

bool is_abc(string& s, int c_pos) {
  if (c_pos == 0 || c_pos >= s.length()) {
    return false;
  }
  return s[c_pos - 1] == 'a' && s[c_pos] == 'b' && s[c_pos + 1] == 'c';
}

int main() {
  int n, q;
  string s;
  cin >> n >> q;
  cin >> s;
  int cnt = 0;
  for (int i = 1; i < s.length() - 1; ++i) {
    cnt += is_abc(s, i);
  }

  for (int i = 0; i < q; ++i) {
    int pos;
    char c;
    cin >> pos >> c;

    --pos;
    cnt -= is_abc(s, pos) + is_abc(s, pos - 1) + is_abc(s, pos + 1);
    s[pos] = c;
    cnt += is_abc(s, pos) + is_abc(s, pos - 1) + is_abc(s, pos + 1);

    printf("%d\n", cnt);
  }
}
