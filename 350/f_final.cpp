#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int cnt[10];

string s, t;
bool is_t_decreasing = false;

bool remove_string(string num) {
  bool flag = true;
  for (int i = 0; i < num.length(); ++i) {
    cnt[num[i] - '0']--;
    flag &= cnt[num[i] - '0'] >= 0;
  }
  return flag;
}

void add_string(string num) {
  for (int i = 0; i < num.length(); ++i) {
    cnt[num[i] - '0']++;
  }
}

bool remove_num(int x) {
  bool flag = true;
  if (x == 0) {
    cnt[0]--;
    flag &= cnt[0] >= 0;
  }
  while (x != 0) {
    cnt[x % 10]--;
    flag &= cnt[x % 10] >= 0;
    x /= 10;
  }
  return flag;
}

void add_num(int x) {
  if (x == 0) {
    cnt[0]++;
  }
  while (x != 0) {
    cnt[x % 10]++;
    x /= 10;
  }
}

int to_int(char c) {
  return c - '0';
}

int to_char(int x) {
  return x + '0';
}

bool any_numbers_left() {
  for (int i = 0; i < 10; ++i) {
    if (cnt[i]) {
      return true;
    }
  }
  return false;
}

bool is_length_equals_to(int k) {
  int res = t.length();
  for (int i = 0; i < 10; ++i) {
    res += cnt[i];
  }
  return res == k;
}

string smallest_possible() {
  string tmp;

  for (int i = 1; i < 10 && tmp.size() < t.length(); ++i) {
    if (tmp.empty() && cnt[i] > 0) {
      //cout << "PUSHING" << i << endl;
      tmp.push_back(to_char(i));
      cnt[i]--;
      i = 0;
    }
    while (cnt[i] > 0 && tmp.length() < t.length()) {
      //cout << "PUSHING " << i << endl;
      tmp.push_back(to_char(i));
      cnt[i]--;
    }
  }

  add_string(tmp);
  return tmp;
}

bool can_take_less_on_prefix() {
  if (t[0] == '0') {
    return false;
  }

  string smallest = smallest_possible();
  return smallest < t && !smallest.empty();
}

void try_make_ans(string &ans, bool t_merged=false) {
  //cout << " ANS AFTER " << endl;
  //cout << ans << endl;

  for (int i = 1; i < 10; ++i) {
    if (ans.empty() && cnt[i] > 0 && (to_int(t.front()) > i || to_int(t.front()) == 0
          || can_take_less_on_prefix())) {
      ans.push_back(to_char(i));
      cnt[i]--;
      break;
    }
  }

  //cout << " ANS AFTER " << endl;
  //cout << ans << endl;

  if (ans.empty()) {
    if (t.front() == '0') {
      return;
    } else {
      ans += t;
      t_merged = true;
    }
  }

  for (int i = 0; i < 10; ++i) {
    if (!t_merged) {
      if (to_int(t.front()) > i || (to_int(t.front()) == i && !is_t_decreasing)) {
        while (cnt[i] > 0) {
          ans.push_back(to_char(i));
          --cnt[i];
        }
      } else {
        ans += t;
        t_merged = true;
        --i;
      }
    } else {
      while (cnt[i] > 0) {
        ans.push_back(to_char(i));
        --cnt[i];
      }
    }

    //cout << ans << endl;
  }

  if (!any_numbers_left() && !t_merged) {
    ans += t;
  }
  //cout << ans << endl;
}

int main() {
  cin >> s >> t;
  add_string(s);
  remove_string(t);

  for (int i = 0; i < t.length() - 1; ++i) {
    if (t[i] == t[i + 1]) {
      continue;
    } else {
      is_t_decreasing = t[i] > t[i + 1];
      break;
    }
  }

  string ans;

  for (int i = 1; i < s.length(); ++i) {
    if (remove_num(i) && is_length_equals_to(i)) {
      //cout << "trying for " << i << endl;
      string smallest = smallest_possible();
      //cout << cnt[0] << " " << cnt[1] << endl;
      try_make_ans(ans);
      string res = ans;
      //cout << "ANS IS " << ans << endl;
      //cout << cnt[0] << " " << cnt[1] << endl;

      add_string(ans);
      //cout << "T IS " << t << endl;
      remove_string(t);
      //cout << cnt[0] << " " << cnt[1] << endl;
      if (t[0] != '0') {
        ans.clear();
        ans = t;
        try_make_ans(ans, true);
        //cout << "ANS IS " << ans << endl;
        res = min(ans, res);
      }
      if (!res.empty()) {
        cout << res << "\n";
        return 0;
      }
      //cout << "==================\n";
    }
    add_num(i);
  }
  cout << "0\n";
  return 0;
}
