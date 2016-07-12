#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <deque>
#include <memory.h>

using namespace std;

int cnt[10];

string a, b;

bool take(int x) {
  int xx = x;
  int cur_cnt[10];
  int cnt_symbols = 0;

  for (int i = 0; i < 10; ++i) {
    cur_cnt[i] = 0;
  }

  while (x != 0) {
    ++cnt_symbols;
    int t = x % 10;
    x /= 10;
    cur_cnt[t]++;
    if (cur_cnt[t] > cnt[t]) {
      return false;
    }
  }

  if (a.length() - cnt_symbols != xx) {
    return false;
  }

  for (int i = 0; i < 10; ++i) {
    cnt[i] -= cur_cnt[i];
  }
  return true;
}

void put_back(int x) {
  while (x != 0) {
    cnt[x % 10]++;
    x /= 10;
  }
}

string ans;

void repl_with(string s) {
  if (s[0] == '0') {
    return;
  }

  if (ans.empty()) {
    ans = s;
    return;
  }

  if (ans.size() > s.size()) {
    ans = s;
    return;
  }

  for (int i = 0; i < ans.size(); ++i) {
    if (ans[i] > s[i]) {
      ans = s;
      return;
    }
  }
}

void try_to_succeed() {
  string cur_ans;

  string start_with_0;
  string start_with_1;

  int replace_first = 1;

  while (cnt[replace_first] == 0) {
    ++replace_first;
  }

  if (n != 10) {
    start_with_1.push_back(replace_first + '0');
  }

  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < cnt[i]; ++j) {
      start_with_0.push_back(i + '0');
      if (i == replace_first && j == 0) {
        continue;
      }
      start_with_1.push_back(i + '0');
    }
  }

  bool flag = false;
  for (int i = 0; i < min(b.length(), start_with_1.length()); ++i) {
    if (start_with_1[i] > b[i]) {
      repl_with(b + start_with_0);
      return;
    }
  }

  if (b.length() >= start_with_1.length()) {
    repl_with(start_with_1 + b);
    repl_with(b + start_with_1);
    repl_with(b + start_with_0);
  } else {
    int idx = start_with_1.length();
    int cnt_chars = 0;
    while (idx + cnt_chars < start_with_1.length()) {
      if (cnt_chars >= b.length()) {
        start_with_1.insert(idx + cnt_chars, b);
        repl_with(start_with_1);
        repl_with(b + start_with_0);
        return;
      }
      if (start_with_1[idx + cnt_chars] > b[cnt_chars]) {
        start_with_1.insert(idx + cnt_chars, b);
        repl_with(start_with_1);
        repl_with(b + start_with_0);
        return;
      }
      if (start_with_1[idx + cnt_chars] < b[cnt_chars]) {
        start_with_1.insert(idx + cnt_chars, b);
        repl_with(start_with_1);
        repl_with(b + start_with_0);
        return;
      }
      ++cnt_chars;
    }
    if (b.length() > 1 && b[1] ) {
      while (idx < start_with_1.length() && start_with_1[idx] <= b[0]) {
        idx++;
      }
    }
    while (start_with_1[idx])
    start_with_1.insert(idx, b);
  }

  cout << b + start_with_1 << endl;
  cout << start_with_1 + b << endl;
  cout << b + start_with_0 << endl;
  cout << "fffffffffffffffffffff" << endl;

  repl_with(start_with_1 + b);
  repl_with(b + start_with_1);
  repl_with(b + start_with_0);
}

int main() {
  cin >> a;
  cin >> b;

  if (a == "01" || a == "10") {
    cout << b << "\n";
    return 0;
  }

  for (int i = 0; i < a.length(); ++i) {
    cnt[a[i] - '0']++;
  }
  for (int i = 0; i < b.length(); ++i) {
    cnt[b[i] - '0']--;
  }

  for (int i = 0; i < 10; ++i) {
    cout << cnt[i] << " ";
  }
  cout << endl;

  for (int i = 1; i < 1e6; ++i) {
    if (take(i)) {
      try_to_succeed();
      if (ans != "") {
        cout << ans << "\n";
        return 0;
      }
      put_back(i);
    }
  }
}
