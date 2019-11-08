#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <list>
#include <string>

using namespace std;

int main() {
  int last_el = 0;
  string ans;
  list<int> l;
  int n;

  cin >> n;
  for (int i = 0; i < n; ++i) {
    int el;
    cin >> el;
    l.push_back(el);
  }

  while (!l.empty() && max(l.front(), l.back()) > last_el) {
    if (l.size() == 1) {
      last_el = l.front();
      ans.push_back('L');
      l.pop_front();
      continue;
    }

    if (l.front() > last_el && l.front() < l.back()) {
      last_el = l.front();
      ans.push_back('L');
      l.pop_front();
    } else if (l.back() > last_el && l.back() < l.front()) {
      last_el = l.back();
      ans.push_back('R');
      l.pop_back();
    } else { // back == front
      string l_suff;
      string r_suff;
      int cur_last_el = last_el;
      auto it = l.begin();
      while (*it > cur_last_el) {
        cur_last_el = *it;
        it = next(it);
        l_suff.push_back('L');
      }

      cur_last_el = last_el;
      auto rit = l.rbegin();
      while (*rit > cur_last_el) {
        cur_last_el = *rit;
        rit = next(rit);
        r_suff.push_back('R');
      }
      if (l_suff.length() > r_suff.length()) {
        ans += l_suff;
      }
      else {
        ans += r_suff;
      }
      break;
    }
  }
  cout << ans.length() << "\n";
  cout << ans << "\n";
  return 0;
}


