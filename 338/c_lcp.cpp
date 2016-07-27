#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

const int MAX_N = 2200;

string s, t;
string rev_s;

int lcp[MAX_N][MAX_N];
int rev_lcp[MAX_N][MAX_N];
pair<int, int> bounds_for[MAX_N];
int maxlen_from[MAX_N];

void prepare() {
  for (int i = t.length() - 1; i >= 0; --i) {
    for (int j = s.length() - 1; j >= 0; --j) {
      lcp[i][j] = (lcp[i + 1][j + 1] + 1) * (t[i] == s[j]);
      rev_lcp[i][j] = (rev_lcp[i + 1][j + 1] + 1) * (t[i] == rev_s[j]);
      if (lcp[i][j] > maxlen_from[i]) {
        maxlen_from[i] = lcp[i][j];
        bounds_for[i] = make_pair(j + 1, j + maxlen_from[i]);
      }
      if (rev_lcp[i][j] > maxlen_from[i]) {
        maxlen_from[i] = rev_lcp[i][j];
        // in usual string
        // from j to j + maxlen_from[i] - 1
        // now reverse indeces:
        // from len - 1 - j to len - 1 - (j + maxlen_from[i] - 1)
        // to 1-based is
        bounds_for[i] = make_pair(s.length() - j, s.length() - j - maxlen_from[i] + 1);
      }
    }
  }

}

int main() {
  cin >> s >> t;
  rev_s = s;
  reverse(rev_s.begin(), rev_s.end());
  prepare();

  int cur_pos = 0;
  vector<pair<int, int>> ans;
  while (cur_pos < t.length()) {
    if (maxlen_from[cur_pos] == 0) {
      cout << "-1\n";
      return 0;
    }
    ans.push_back(bounds_for[cur_pos]);
    cur_pos += maxlen_from[cur_pos];
  }

  cout << ans.size() << "\n";
  for (int i = 0; i < (int)ans.size(); ++i) {
    cout << ans[i].first << " " << ans[i].second << "\n";
  }
  return 0;
}

