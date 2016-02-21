#include <iostream>
#include <vector>
#include <cstdio>
#include <set>
#include <map>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 1e5 + 5;
const double PI = acos(-1);

map<long long, int> mp;
int n;
pair<long long, int> a[MAXN];
pair<int, int> sq_a[MAXN];

long long t[MAXN];

long long get_max(int r) {
  long long result = 0;
  for (; r >= 0; r = (r & (r + 1)) - 1) {
    result = max(result, t[r]);
  }
  return result;
}

void update(int i, long long new_val)
{
  for (; i < MAXN; i = (i | (i + 1))) {
    t[i] = max(t[i], new_val);
  }
}

bool cmp (pair<int, int> a, pair<int, int> b) {
  if (a.second != b.second) {
    return a.second < b.second;
  }
  return a.first > b.first;
}

bool cmp_a (pair<long long, int> a, pair<long long, int> b) {
  if (a.second != b.second) {
    return a.second < b.second;
  }
  return a.first > b.first;
}

void squeeze() {
  sort(a, a + n);
  int cur_squeezed = 1;
  sq_a[0] = make_pair(cur_squeezed, a[0].second);
  for (int i = 1; i < n; ++i) {
    if (a[i].first == a[i - 1].first) {
      sq_a[i] = make_pair(cur_squeezed, a[i].second);
    } else {
      sq_a[i] = make_pair(++cur_squeezed, a[i].second);
    }
  }
  sort(a, a + n, cmp_a);
  sort(sq_a, sq_a + n, cmp);
}

int main() {
  // freopen("input.txt", "r", stdin);
  double ans = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int r, h;
    scanf("%d%d", &r, &h);
    a[i] = make_pair(r * 1ll * r * h, i);
  }
  squeeze();
  for (int i = 0; i < n; ++i) {
    //cout << "i = " << i << endl;
    //cout << "sq_a[i] = " << sq_a[i].first << endl;
    long long cur_ans = get_max(sq_a[i].first - 1) + a[i].first;
    long long tree_max = get_max(sq_a[i].first);
    //cout << "cur_ans = " << cur_ans << endl;
    //cout << "current piece = " << a[i].first << endl;
    //cout << "tree_max = " << tree_max << endl;
    if (cur_ans > ans) {
      ans = cur_ans;
    }
    if (tree_max < cur_ans) {
      update(sq_a[i].first, cur_ans);
    }
  }
  printf("%.8lf\n", PI * ans);
  return 0;
}
