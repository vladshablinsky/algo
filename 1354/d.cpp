#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 1000005;
const int SQRT = 1005;
const int BITS = 20;
vector<bool> storage(BITS * MAXN);
int decomposed[SQRT];

int get_cnt(int x) {
  int ans = 0;
  for (int i = 0; i < BITS; ++i) {
    ans += (1 << i) * storage[BITS * x + i];
  }
  return ans;
}

void set_cnt(int x, int val) {
  for (int i = 0; i < BITS; ++i) {
    storage[BITS * x + i] = ((val & (1 << i)) != 0);
  }
}

void inc_decomposed(int x, int val) {
  decomposed[x / SQRT] += val;
}

int remove_k_th(int k) {
  int block = 0;
  int left_behind = 0;
  while (block < SQRT && left_behind + decomposed[block] < k) {
    left_behind += decomposed[block];
    ++block;
  }

  if (block < SQRT) {
    for (int i = SQRT * block; i < SQRT * (block + 1); ++i) {
      int cnt_i = get_cnt(i);
      if (left_behind + cnt_i < k) {
        left_behind += cnt_i;
      } else {
        inc_decomposed(i, -1);
        set_cnt(i, cnt_i - 1);
        return i;
      }
    }
  }

  return 0;
}

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  int prev = 0;
  int cur_cnt = 0;

  for (int i = 0; i < n; ++i) {
    int cur;
    scanf("%d", &cur);
    if (cur == prev || !prev) {
      ++cur_cnt;
    } else {
      set_cnt(prev, cur_cnt);
      inc_decomposed(prev, cur_cnt);
      cur_cnt = 1;
    }
    prev = cur;
  }
  set_cnt(prev, cur_cnt);
  inc_decomposed(prev, cur_cnt);

  for (int i = 0; i < q; ++i) {
    int k;
    scanf("%d", &k);
    if (k < 0) {
      remove_k_th(-k);
    } else {
      set_cnt(k, get_cnt(k) + 1);
      inc_decomposed(k, 1);
    }
  }
  printf("%d\n", remove_k_th(1));
  return 0;
}
