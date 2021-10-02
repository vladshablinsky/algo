#include <iostream>
#include <vector>

using namespace std;

int process(string& s, char open, char close) {
  int pending_open = 0;
  int result = 0;
  for (auto c: s) {
    if (c == open) {
      ++pending_open;
    } else if (c == close && pending_open) {
      --pending_open;
      ++result;
    }
  }
  return result;
}

int solve() {
  string s;
  cin >> s;
  return process(s, '(', ')') + process(s, '[', ']');
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    printf("%d\n", solve());
  }
}
