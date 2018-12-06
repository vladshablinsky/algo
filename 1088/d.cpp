#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

int a, b;

int query(int c, int d) {
  int result;
  printf("? %d %d\n", c, d);
  fflush(stdout);
  scanf("%d", &result);
  return result;

  // if ((a ^ c) < (b ^ d)) {
  //   return -1;
  // } else if ((a ^ c) > (b ^ d)) {
  //   return 1;
  // } else {
  //   return 0;
  // }
}

int main() {
  int mask = 1 << 29;
  int cur_a = 0;
  int cur_b = 0;
  int pref_q = query(0, 0);
  while (mask) {
    int q1 = query(cur_a | mask, cur_b);
    int q2 = query(cur_a, cur_b | mask);
    if (q1 != q2) {
      if (q1 == -1) {
        cur_a |= mask;
        cur_b |= mask;
      }
    } else {
      if (pref_q == 1) {
        cur_a |= mask;
        pref_q = q1;

      } else {
        cur_b |= mask;
        pref_q = q2;
      }
    }
    mask >>= 1;
  }

  printf("! %d %d\n", cur_a, cur_b);
  fflush(stdout);
  return 0;
}
