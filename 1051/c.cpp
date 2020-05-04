#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 105;

vector<int> ids[MAXN];
bool ans[MAXN];

int main() {
  int n;
  cin >> n;
  int cnt_nice = n;
  bool can_transfer = false;
  for (int i = 0; i < n; ++i) {
    int el;
    cin >> el;
    cnt_nice -= (ids[el].size() == 1);
    ids[el].push_back(i);
    cnt_nice -= (ids[el].size() > 1);
    can_transfer |= (ids[el].size() > 2);
  }

  int nice_number_id = cnt_nice;
  if ((cnt_nice & 1) && (cnt_nice == n || !can_transfer))  {
    cout << "NO\n";
  } else {
    int idx_many = -1;
    for (int i = 1; i < MAXN; ++i) {
      if (ids[i].size() == 1) {
        ans[ids[i].back()] = !(nice_number_id % 2);
        --nice_number_id;
      } else if (ids[i].size() > 2) {
        idx_many = i;
      }
    }
    if (cnt_nice & 1) {
      ans[ids[idx_many].back()] = true;
    }
    cout << "YES\n";
    for (int i = 0; i < n; ++i) {
      cout << (ans[i] ? 'B': 'A');
    }
    cout << "\n";
  }
  return 0;
}
