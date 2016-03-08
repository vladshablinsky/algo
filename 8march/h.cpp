#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

vector<string> v;

void solve(string s) {
  v.clear();
  int before = 0;

  v.push_back("");
  cout << "HEREW" << endl;

  for (int i = 0; i < s.length(); ++i) {
    if (i + 1 < s.length() && s[i] == ':' && s[i + 1] == ':') {
      before = v.size();
      cout << "BEFORE = " << before << endl;
      continue;
    }
    if (s[i] == ':') {
      v.push_back("");
    }
    v.back().push_back(s[i]);
  }

  for (int i = 0; i < before; ++i) {
    for (int j = 0; j < 4 - v[i].length(); ++i) {
      printf("0");
    }
    cout << v[i];
    if (i < 7) {
      printf(":");
    }
  }
  for (int i = 0; i < 8 - v.size(); ++i) {
    if (before + i < 7) {
      printf("0000:");
    } else {
      printf("0000");
    }
  }
  printf("\n");
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    solve(s);
  }
  return 0;
}
