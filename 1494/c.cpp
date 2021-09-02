#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 200005;

int solve_for_pos(vector<int>& a, vector<int>& b) {
  if (a.empty()) {
    return 0;
  }

  int cnt_in_place = 0;
  int p1 = 0;
  int p2 = 0;
  while (p1 < a.size() && p2 < b.size()) {
    if (a[p1] < b[p2]) {
      ++p1;
    } else if (a[p1] == b[p2]) {
      ++cnt_in_place;
      ++p1;
      ++p2;
    } else {
      ++p2;
    }
  }

  // cout << "cnt_in_place " << cnt_in_place << endl;

  p1 = 0; // pointer to the last element in a, not yet added to the tail
  p2 = 0; // now p2 is the pointer to the last element in b that that tail have not yet exceeded

  int ans = cnt_in_place;
  int cnt_continious = 0;
  // global pointer to the element in b greater than current tail of
  // current continious block
  int p3 = 0;
  for (int i = 0; i < b.size(); ++i) {
    p2 = max(i, p2);

    while (p1 < a.size() && b[i] + max(0, cnt_continious - 1) >= a[p1]) {
      while (p2 < b.size() && a[p1] >= b[p2]) {
        cnt_in_place -= a[p1] == b[p2];
        ++p2;
      }

      ++cnt_continious;
      ++p1;
    }

    while (p3 < b.size() && b[i] + cnt_continious - 1 >= b[p3]) {
      ++p3;
    }

    //cout << "i: " << i << "p1 : " << p1 << ", p2: " << p2 << ", p3: " << p3 << endl;
    ans = max(ans, cnt_in_place + p3 - i);
  }
  //cout << "ans: " << ans << endl;
  return ans;
}

int solve() {
  int n, m;
  vector<int> al, ar;
  vector<int> bl, br;
  scanf("%d%d", &n, &m);

  int cur;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &cur);
    if (cur < 0) {
      al.push_back(-cur);
    } else {
      ar.push_back(cur);
    }
  }
  std::reverse(al.begin(), al.end());
  for (int j = 0; j < m; ++j) {
    scanf("%d", &cur);
    if (cur < 0) {
      bl.push_back(-cur);
    } else {
      br.push_back(cur);
    }
  }
  std::reverse(bl.begin(), bl.end());

  return solve_for_pos(al, bl) + solve_for_pos(ar, br);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    cout << solve() << "\n";
  }
}
