#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

int ask(int q) {
  int res;
  cout << "? " << q << "\n";
  cout.flush();
  cin >> res;
  return res;
}

void answer(const vector<int>& v) {
  cout << "! ";
  for (int i = 1; i < v.size(); ++i) {
    cout << v[i] << " ";
  }
  cout << "\n";
  cout.flush();
}

void solve() {
  int n;
  cin >> n;


  vector<int> res(n + 1);
  vector<bool> knowns(n + 1, false);
  // waste first query
  ask(1);
  int step = 0;

  for (int i = 1; i <= n; ++i) {
    if (knowns[i]) {
      continue;
    }

    vector<int> cur_loop;
    if (i == 1) {
      cur_loop.push_back(1);
    }

    while (cur_loop.size() < 2 || cur_loop.front() != cur_loop.back()) {
      cur_loop.push_back(ask(i));
      ++step;
    }
    cur_loop.pop_back();

    int len = cur_loop.size();
    // This one is p_i, the following are p_p_i etc
    int shifted_first = ((len - step % len) % len + 1) % len;
    int cur_idx = i;
    for (int j = 0; j < len; ++j) {
      int looped = (shifted_first + j) % len;
      res[cur_idx] = cur_loop[looped];
      cur_idx = cur_loop[looped];
      knowns[cur_idx] = true;
    }
  }
  answer(res);
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
