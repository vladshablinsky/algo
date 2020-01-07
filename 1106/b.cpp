#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1000005;

int a[MAXN];
int c[MAXN];
pair<int, int> sorted_c[MAXN];

int cheapest_pointer = 0;

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &c[i]);
    sorted_c[i].first = c[i];
    sorted_c[i].second = i;
  }
  sort(sorted_c, sorted_c + n);

  // begin processing queries
  for (int i = 0; i < m; ++i) {
    //cout << "serving guest: " << i << endl;
    int type_of_dish, dishes_to_serve;
    scanf("%d%d", &type_of_dish, &dishes_to_serve);
    --type_of_dish;
    long long cur_cost = 0;

    int actual_dishes_cnt = min(dishes_to_serve, a[type_of_dish]);
    cur_cost += c[type_of_dish] * 1ll * actual_dishes_cnt;
    //cout << actual_dishes_cnt << " of dish " << type_of_dish << ", cur cost: " << cur_cost << endl;
    dishes_to_serve -= actual_dishes_cnt;
    a[type_of_dish] -= actual_dishes_cnt;

    while (dishes_to_serve && cheapest_pointer < n) {
      int cheapest_dish = sorted_c[cheapest_pointer].second;
      int cheapest_cost = sorted_c[cheapest_pointer].first;

      actual_dishes_cnt = min(dishes_to_serve, a[cheapest_dish]);
      dishes_to_serve -= actual_dishes_cnt;

    //cout << actual_dishes_cnt << " of dish " << cheapest_dish << ", cur cost: " << cur_cost << endl;
      cur_cost += cheapest_cost * 1ll * actual_dishes_cnt;

      a[cheapest_dish] -= actual_dishes_cnt;
      if (!a[cheapest_dish]) {
        ++cheapest_pointer;
      }
    }

    if (dishes_to_serve) {
      cur_cost = 0;
    }
    cout << cur_cost << "\n";
  }
  return 0;
}
