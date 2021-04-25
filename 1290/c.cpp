#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 300005;
const int INF = 5000000;

vector<int> v_to_set_id[MAXN]; // max two sets for each element.

// dsu part
struct dsu_node {
  int rank;
  int cost_on;
  int cost_off;
  int parity;
} dsu[MAXN];

int cnt_swaps[MAXN];
int swap_locked[MAXN];
int p[MAXN];
int component_size[MAXN];
int set_to_color[MAXN];
int cnt_taken_from_set_union[MAXN];
bool ignored_sets[MAXN];

void init_sets(int n) {
  for (int i = 0; i <= n; ++i) {
    p[i] = i;
    dsu[i].rank = 1;
    dsu[i].cost_on = 1;
    dsu[i].cost_off = 0;
  }
}

pair<int, int> find_set(int x) {
  if (p[x] == x) {
    return {x, 0};
  } else {
    auto [p_x, p_parity] = find_set(p[x]);
    dsu[x].parity ^= p_parity;
    p[x] = p_x;

    return {p[x], dsu[x].parity};
  }
}

int get_min(int union_id) {
  return min(dsu[union_id].cost_on, dsu[union_id].cost_off);
}

void fix(int union_id) {
  dsu[union_id].cost_on = min(dsu[union_id].cost_on, INF);
  dsu[union_id].cost_off = min(dsu[union_id].cost_off, INF);
}

int main() {
  //freopen("input.txt", "r", stdin);
  int n, k;
  string s;

  scanf("%d%d", &n, &k);
  cin >> s;

  for (int i = 0; i < k; ++i) {
    int power;
    scanf("%d", &power);

    int el;
    for (int j = 0, el; j < power; ++j) {
      scanf("%d", &el);
      v_to_set_id[el].push_back(i);
    }
  }

  init_sets(k);

  int ans = 0;
  for (int i = 1; i <= n; ++i) {
    // cout << "i: " << i << endl;
    // cout << "====================\n";
    int req_parity = (s[i - 1] == '0');
    // cout << "req_parity: " << req_parity << endl;

    if (v_to_set_id[i].size() == 1) {
      int set_one_id = v_to_set_id[i].front();
      auto [set_unoin_one, parity] = find_set(set_one_id);
      // cout << "one set: " << set_one_id << ", union: " << set_unoin_one << ", parity: " << parity <<  endl;

      // Discard set at full. Same way it might have been added previously.
      ans -= get_min(set_unoin_one);

      // if there is only one set here, then it completely sets the others.
      if (parity ^ req_parity ^ 1) {
        // set union cost_on results in _parity_ for set_one_id.
        // If that parity not the one required by req_parity, we should
        // never turn on unions parent, that will ensure current set is on.
        dsu[set_unoin_one].cost_on = INF;
      } else {
        dsu[set_unoin_one].cost_off = INF;
      }

      ans += get_min(set_unoin_one);
    } else if (v_to_set_id[i].size() == 2) {
      int set_one_id = v_to_set_id[i].front();
      int set_two_id = v_to_set_id[i].back();
      auto [set_unoin_one, parity_one] = find_set(set_one_id);
      auto [set_unoin_two, parity_two] = find_set(set_two_id);

      // cout << "one set: " << set_one_id << ", union: " << set_unoin_one << ", parity: " << parity_one <<  endl;

      // cout << "cost_on: " << dsu[set_unoin_one].cost_on << ", cost_off: " << dsu[set_unoin_one].cost_off << endl;

      // cout << "second set: " << set_two_id << ", union: " << set_unoin_two << ", parity: " << parity_two <<  endl;

      // cout << "cost_on: " << dsu[set_unoin_two].cost_on << ", cost_off: " << dsu[set_unoin_two].cost_off << endl;

      // Otherwise both sets already set current value.
      if (set_unoin_one != set_unoin_two) {
        ans -= get_min(set_unoin_one);
        ans -= get_min(set_unoin_two);

        // Let's always make set_one parent of set_two
        if (dsu[set_unoin_one].rank < dsu[set_unoin_two].rank) {
          swap(set_unoin_one, set_unoin_two);
          swap(parity_one, parity_two);
          // cout << "swap\n";
        }
        p[set_unoin_two] = set_unoin_one;
        dsu[set_unoin_one].rank += dsu[set_unoin_two].rank;
        // cout << "link " << set_unoin_two << " to " << set_unoin_one << endl;

        // In the sets's parent stuff calculated the way that all sums up to
        // the turned off value, thus, knowing that set_one is a parent, we
        // need to swap set_two.
        if (parity_one ^ parity_two ^ req_parity) {
          dsu[set_unoin_one].cost_on += dsu[set_unoin_two].cost_off;
          dsu[set_unoin_one].cost_off += dsu[set_unoin_two].cost_on;

          // cout << "set parity: " << set_unoin_two << endl;
          dsu[set_unoin_two].parity = 1;
          // value stored in dsu[set_union_two] no longer really matter.
        } else {
          dsu[set_unoin_one].cost_on += dsu[set_unoin_two].cost_on;
          dsu[set_unoin_one].cost_off += dsu[set_unoin_two].cost_off;
        }

      // cout << "resulting:\n";
      // cout << "cost_on: " << dsu[set_unoin_one].cost_on << ", cost_off: " << dsu[set_unoin_one].cost_off << endl;

        fix(set_unoin_one);
        fix(set_unoin_two);
        ans += get_min(set_unoin_one);
      }
    }
    printf("%d\n", ans);
  }

  return 0;
}
