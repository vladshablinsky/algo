#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const long long MAXN = (1ll << 32) - 1;
const string OVERFLOW = "OVERFLOW!!!";


void accumulate_add(vector<pair<string, long long>> &st, long long n, bool &overflow) {
  if (st.empty() || st.back().first != "add") {
    st.push_back(make_pair("add", n));
  } else {
    st.back().second += n;
  }
  if (st.back().second > MAXN) {
    overflow = true;
  }
}

void print_st(vector<pair<string, long long>> &st) {
  for (auto &el: st) {
    cout << el.first << " " << el.second << endl;
  }
}


int main() {
  int l;
  cin >> l;
  bool overflow = false;
  vector<pair<string, long long>> st;
  for (int i = 0; i < l; ++i) {
    string s;
    cin >> s;

    if (s == "add") {
      accumulate_add(st, 1ll, overflow);
    } else if (s == "for") {
      long long n;
      cin >> n;
      st.push_back(make_pair("for", n));
    } else {
      long long cnt = 0ll;
      if (st.back().first == "add") {
        cnt = st.back().second;
        st.pop_back();
      }
      cnt *= st.back().second;
      st.pop_back();
      accumulate_add(st, cnt, overflow);
    }
    // print_st(st);
  }

  accumulate_add(st, 0, overflow);
  if (overflow) {
    cout << OVERFLOW << "\n";
  } else {
    cout << st.back().second << "\n";
  }
  return 0;
}
