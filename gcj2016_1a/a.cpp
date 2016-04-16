#include <iostream>
#include <cstdio>
#include <deque>

using namespace std;

void solve(string s, int id) {
  deque<char> dq;
  dq.push_back(s[0]);
  for (int i = 1; i < s.length(); ++i) {
    if (s[i] >= dq.front()) {
      dq.push_front(s[i]);
    } else {
      dq.push_back(s[i]);
    }
  }
  printf("Case #%d: ", id);
  while (!dq.empty()) {
    printf("%c", dq.front());
    dq.pop_front();
  }
  printf("\n");
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    string s;
    cin >> s;
    solve(s, i + 1);
  }
  return 0;
}
