#include <iostream>
#include <cstdio>

using namespace std;

bool used[15];

void init_used() {
  for (int i = 0; i < 15; ++i) {
    used[i] = false;
  }
}

void update(long long val, int &cnt) {
  while (val != 0) {
    if (!used[val % 10]) {
      ++cnt;
      used[val % 10] = true;
    }
    val /= 10;
  }
}

long long solve(long long val) {
  init_used();
  int cnt = 0;
  long long cur_val = val;
  long long i = 2;

  update(cur_val, cnt);

  while (cnt != 10) {
    cur_val = val * i;
    ++i;
    update(cur_val, cnt);
  }
  return cur_val;
}

int main() {
  int t;
  int n;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    scanf("%d", &n);
    if (n == 0) {
      printf("Case #%d: INSOMNIA\n", i + 1);
    } else {
      printf("Case #%d: %lld\n", i + 1, solve(n));
    }
  }
  return 0;
}
