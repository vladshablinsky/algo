#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, char> > v;

void solve(int id) {
  v.clear();
  int n;
  int sum = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int cnt;
    scanf("%d", &cnt);
    sum += cnt;
    v.push_back(make_pair(cnt, 'A' + i));
  }

  vector<string> ans;

  while (sum > 0) {
    sort(v.begin(), v.end());
    int v1 = v.back().first;
    int v2 = v[v.size() - 2].first;
    //cout << "sum is " << sum << endl;
    //cout << "v1 " << v1 << "v2 " << v2 << endl;
    if (max(v1 - 1, v2) * 2 > (sum - 1)) {
      string s;
      s.push_back(v.back().second);
      s.push_back(v[v.size() - 2].second);
      ans.push_back(s);
      --v[v.size() - 1].first;
      --v[v.size() - 2].first;
      sum -= 2;
    } else {
      string s;
      s.push_back(v.back().second);
      ans.push_back(s);
      --v.back().first;
      --sum;
    }
  }

  printf("Case #%d: ", id);
  for (int i = 0; i < ans.size(); ++i) {
    cout << ans[i] << " ";
  }
  cout << "\n";
}

int main() {
  //freopen("in.txt", "r", stdin);
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    solve(i + 1);
  }
  return 0;
}
