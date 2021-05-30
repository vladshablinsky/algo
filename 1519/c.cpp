#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 200005;

int uni[MAXN];
int skill[MAXN];
long long answers[MAXN];
vector<long long> students[MAXN];

void solve() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    answers[i + 1] = 0;
    students[i].clear();
    scanf("%d", &uni[i]);
  }
  for (int i = 0; i < n; ++i) {
    int cur_skill;
    scanf("%d", &cur_skill);
    students[uni[i] - 1].push_back(cur_skill);
  }

  for (int i = 0; i < n; ++i) {
    int cnt = students[i].size();
    if (cnt) {
      long long sum = 0;
      sort(students[i].begin(), students[i].end());
      for (auto el: students[i]) {
        sum += el;
      }
      for (int j = 0; j < cnt; ++j) {
        int el = students[i][j];
        students[i][j] = sum;
        sum -= el;
      }
      for (int k = 1; k <= cnt; ++k) {
        answers[k] += (students[i][cnt % k]);
      }
    }
  }
  for (int i = 1; i <= n; ++i) {
    cout << answers[i] << " ";
  }
  cout << "\n";
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
  return 0;
}
