#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <string>

using namespace std;

const int MAX_N = 1e4 + 10;
string s;
set<string> st;
bool f[MAX_N][2];
// substring storage
string g[MAX_N][2];

void p_s_pos(string s, int pos) {
  cout << s << endl;
  for (int i = 0; i < pos; ++i) {
    cout << " ";
  }
  cout << "^" << endl;
}

int main() {
  cin >> s;
  int n = s.length();
  string cur_2_s;
  string cur_3_s;

  f[n][0] = true;
  f[n][1] = true;

  for (int i = n - 1; i >= 5; --i) {
    //p_s_pos(s, i);
    if (i + 1 < n) {
      cur_2_s = s.substr(i, 2);
      //cout << " CUR 2 SUBSTR FROM " << i << " IS " << cur_2_s << endl;
      if ((f[i + 2][0] && g[i + 2][0] != cur_2_s) || f[i + 2][1]) {
        //cout << "OK\n";
        f[i][0] = true;
        g[i][0] = cur_2_s;
        st.insert(cur_2_s);
      }
    }
    if (i + 2 < n) {
      cur_3_s = s.substr(i, 3);
      //cout << " CUR 3 SUBSTR FROM " << i << " IS " << cur_3_s << endl;
      if ((f[i + 3][1] && g[i + 3][1] != cur_3_s) || f[i + 3][0]) {
        //cout << "OK\n";
        f[i][1] = true;
        g[i][1] = cur_3_s;
        st.insert(cur_3_s);
      }
    }
  }

  cout << st.size() << "\n";
  for (auto it = st.begin(); it != st.end(); ++it) {
    cout << *it << "\n";
  }
  return 0;
}
