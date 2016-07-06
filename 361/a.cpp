#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> v;

bool can_right(int x) {
  return x != 3 && x != 9 && x != 6 && x != 0;
}

bool can_left(int x) {
  return x != 1 && x != 4 && x != 7 && x != 0;
}

bool can_down(int x) {
  return x != 7 && x != 0 && x != 9;
}

bool can_up(int x) {
  return x != 1 && x != 2 && x != 3;
}

int main() {
  int n;
  string s;
  cin >> n;
  cin >> s;
  for (int i = 0; i < n; ++i) {
    v.push_back(s[i] - '0');
  }

  bool flag = true;
  for (int i = 0; i < n; ++i) {
    if (!can_up(v[i])) {
      flag = false;
      break;
    }
  }
  if (flag) {
    cout << "NO\n";
    return 0;
  }
  flag = true;
  for (int i = 0; i < n; ++i) {
    if (!can_down(v[i])) {
      flag = false;
      break;
    }
  }
  if (flag) {
    cout << "NO\n";
    return 0;
  }
  flag = true;
  for (int i = 0; i < n; ++i) {
    if (!can_left(v[i])) {
      flag = false;
      break;
    }
  }
  if (flag) {
    cout << "NO\n";
    return 0;
  }
  flag = true;
  for (int i = 0; i < n; ++i) {
    if (!can_right(v[i])) {
      flag = false;
      break;
    }
  }
  if (flag) {
    cout << "NO\n";
    return 0;
  }
  cout << "YES\n";
  return 0;
}
