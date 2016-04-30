#include <iostream>
#include <vector>
#include <cstdio>
#include <string>

using namespace std;

vector<pair<string, string> > v;
vector<pair<string, string> > fakes;
vector<pair<string, string> > others;
int cur_perm[20];
int n;
int ans = 0;

int check() {
  fakes.clear();
  others.clear();
  //for (int i = 0; i < n; ++i) {
    //cout << cur_perm[i];
  //}
  //cout << endl;
  for (int i = 0; i < n; ++i) {
    if (cur_perm[i] == 0) {
      others.push_back(v[i]);
    } else {
      fakes.push_back(v[i]);
    }
  }

  //for (int i = 0; i < others.size(); ++i) {
    //cout << others[i].first << " " << others[i].second << endl;
  //}

  for (int i = 0; i < fakes.size(); ++i) {
    string a = fakes[i].first;
    string b = fakes[i].second;
    bool found = false;
    for (int j = 0; j < others.size(); ++j) {
      if (found) {
        break;
      }
      for (int k = 0; k < others.size(); ++k) {
        if (j == k) {
          continue;
        }
        if (a == others[j].first && b == others[k].second) {
          found = true;
          break;
        }
      }
    }
    if (!found) {
      //cout << " CANNOT FIND " << a << " " << b << endl;
      return 0;
    }
  }
  return fakes.size();
}

void rec(int pos) {
  if (pos == n) {
    ans = max(ans ,check());
    return;
  }
  rec(pos + 1);
  cur_perm[pos] = 1;
  rec(pos + 1);
  cur_perm[pos] = 0;
}

void solve(int id) {
  ans = 0;
  v.clear();
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cur_perm[i] = 0;
    string s, t;
    cin >> s;
    cin >> t;
    v.push_back(make_pair(s, t));
  }
  rec(0);
  cout << "Case #" << id << ": " << ans << "\n";
}

int main() {
  int t;
  cin >> t;
  for (int i = 0; i < t; ++i) {
    solve(i + 1);
  }
  return 0;
}
