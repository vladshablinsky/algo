#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

vector<string> v;

bool cmp(string s1, string s2) {
  return s1 + s2 < s2 + s1;
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    v.push_back(s);
  }

  sort(v.begin(), v.end(), cmp);
  for (int i = 0; i < v.size(); ++i) {
    cout << v[i];
  }
  cout << "\n";

  return 0;
}
