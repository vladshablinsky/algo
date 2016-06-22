#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> v;
vector<int> ans;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    int t;
    scanf("%d", &t);
    v.push_back(t);
  }

  sort(v.begin(), v.end());

  int wasted = 0;
  int v_index = 0;
  int cur_item = 1;

  while (wasted < m) {
    if (v_index < v.size() && v[v_index] == cur_item) {
      ++v_index;
      ++cur_item;
    } else if (wasted + cur_item <= m){
      wasted += cur_item;
      ans.push_back(cur_item);
      ++cur_item;
    } else {
      break;
    }
  }

  printf("%d\n", (int)ans.size());
  for (int i = 0; i < ans.size(); ++i) {
    printf("%d ", ans[i]);
  }
  printf("\n");
  return 0;
}

