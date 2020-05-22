#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = (1 << 20) + 5;

int t[MAXN];
int removed_in[MAXN];
vector<int> removals;
long long removed_sum = 0;

void delete_in_subtr(int i, int x);

void upd_removal_stats(int i) {
  while (i) {
    removed_in[i]++;
    i /= 2;
  }
}

// Does not perform any checks for removed_in[i] == x.
void remove_longest_or_in_other_subtr(int start_i, int i, int x) {
  if (x == 1 || t[i * 2] == t[i * 2 + 1]) { // succeed removing longest.
    removed_sum += t[start_i];
    removals.push_back(start_i);
    upd_removal_stats(i);
    int cur = t[i];
    int up = t[i / 2];
    t[i] = 0;
    while (i != start_i) {
      up = t[i / 2];
      t[i / 2] = cur;
      i /= 2;
      cur = up;
    }
  } else {
    int less_son = i * 2;
    int greater_son = i * 2 + 1;
    if (t[i * 2] > t[i * 2 + 1]) {
      swap(less_son, greater_son);
    }

    // otherwise in this subtree can only be x / 2!
    // Note: removal along max path occurs once in a call.
    if (removed_in[greater_son] < x / 2) {
      remove_longest_or_in_other_subtr(start_i, greater_son, x / 2);
    } else {
      // if greater subtree is exhausted, we now sure, that we need to remove
      // all we can in less subtree with total elements to be removed equal to x/2.
      delete_in_subtr(less_son, x / 2);
    }
  }
}

void delete_in_subtr(int i, int x) {
  // cout << "delete_in_subtr: " << i << ", " << x << endl;
  while (removed_in[i] != x) {
    remove_longest_or_in_other_subtr(i, i, x);
  }
}

void solve() {
  removed_sum = 0;
  removals.clear();
  int source_h, target_h;
  scanf("%d%d", &source_h, &target_h);

  long long source_sum = 0;
  int cnt_to_delete = (1 << source_h) - (1 << target_h);
  for (int i = 1; i < (1 << source_h); ++i) {
    scanf("%d", &t[i]);
    source_sum += t[i];
    removed_in[i] = 0;
  }

  removed_sum = 0;
  delete_in_subtr(1, cnt_to_delete);
  printf("%lld\n", source_sum - removed_sum);
  for (auto el: removals) {
    printf("%d ", el);
  }
  printf("\n");
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    solve();
  }
  return 0;
}
