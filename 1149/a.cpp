#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

void order(int cnt_ones, int cnt_twos, vector<int> &ans) {
  for (int i = 0; i < cnt_twos; ++i) {
    ans.push_back(2);
  }
  for (int i = 0; i < cnt_ones; ++i) {
    ans.push_back(1);
  }
}

int main() {
  int cnt_ones = 0;
  int cnt_twos = 0;
  vector<int> ans;

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    int t;
    cin >> t;
    if (t == 1) {
      ++cnt_ones;
    } else {
      ++cnt_twos;
    }
  }

  if (cnt_ones && cnt_twos) {
    ans.push_back(2);
    ans.push_back(1);
    --cnt_ones;
    --cnt_twos;
  }
  order(cnt_ones, cnt_twos, ans);

  for (auto x: ans) {
    cout << x << " ";
  }
  return 0;
}
