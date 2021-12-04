#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

bool is_palindrome(const vector<int>& v) {
  for (int i = 0; i < v.size() / 2; ++i) {
    if (*(v.begin() + i) != *(v.rbegin() + i)) {
      return false;
    }
  }
  return true;
}

vector<int> remove(const vector<int>& in, int x) {
  vector<int> res;
  for (auto el: in) {
    if (el != x) {
      res.push_back(el);
    }
  }
  return res;
}

bool solve() {
  int n;
  scanf("%d", &n);
  vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &v[i]);
  }

  for (int i = 0; i < n / 2; ++i) {
    if (v[i] != v[n - 1 - i]) {
      return is_palindrome(remove(v, v[i])) || is_palindrome(remove(v, v[n - 1 - i]));
    }
  }
  return true;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    if (solve()) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
}
