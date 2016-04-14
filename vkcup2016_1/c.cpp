#include <iostream>
#include <cstdio>

using namespace std;

const int MAXN = 2e5 + 40;

int num[MAXN];
int a[MAXN];
int pref[MAXN];
bool isneg = false;
int n;
int max_k;

int mabs(int x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

void neg() {
  isneg = !isneg;
  for (int i = 0; i < MAXN; ++i) {
    num[i] = -num[i];
    a[i] = -a[i];
  }
}

void bin() {
  int carry = 0;
  for (int i = 0; i < MAXN; ++i) {
    if (mabs(num[i] + carry) % 2 == 0) {
      carry = (num[i] + carry) / 2;
      num[i] = 0;
    } else {
      carry = (num[i] + carry - 1) / 2;
      num[i] = 1;
    }
  }
}

void calc_pref() {
  pref[0] = num[0];
  for (int i = 1; i < MAXN; ++i) {
    pref[i] = pref[i - 1] + num[i];
  }
}

int cnt_ones(int from, int to) {
  if (from < to) {
    return 0;
  }
  return pref[from] - (to > 0 ? pref[to - 1] : 0);
}

void prepare_num() {
  int carry = 0;
  for (int i = 0; i < MAXN; ++i) {
    if (mabs(num[i] + carry) % 2 == 0) {
      carry = (num[i] + carry) / 2;
    } else {
      carry = (num[i] + carry - 1) / 2;
    }
  }

  if (carry < 0) {
    neg();
  }
  bin();
}

void add(int x, int power) {
  int k = x < 0 ? -1 : 1;
  x = k * x;
  while (x != 0) {
    num[power++] += k * (x % 2);
    x /= 2;
  }
}

bool try_for(int index) {
  bool zero_allowed = index != n;

  int a_i = a[index];
  int k = a_i < 0 ? -1 : 1;
  a_i *= k;

  int carry = 0;
  long long cur_num = 0;
  int power = 0;

  for (int i = 0; i <= 32; ++i) {
    int cur_digit = num[index++] - k * (a_i % 2) + carry;
    a_i /= 2;
    if (mabs(cur_digit) % 2 == 0) {
      carry = cur_digit / 2;
    } else {
      carry = (cur_digit - 1) / 2;
      cur_num += 1ll << power;
    }
    ++power;
    if (cnt_ones(MAXN - 1, index) == 0 && carry == -1) {
      while (cur_num > 0) {
        cur_num += 1ll << (power++);
      }
      break;
    }
  }

  if (cnt_ones(MAXN - 1, index) != 0 || (carry != 0 && carry != -1)
      || cur_num > max_k || cur_num < -max_k || (cur_num == 0 && !zero_allowed)) {
    return false;
  } else {
    return true;
  }
}

int main() {
  scanf("%d%d", &n, &max_k);

  for (int i = 0; i <= n; ++i) {
    scanf("%d", &a[i]);
    add(a[i], i);
  }

  prepare_num();
  calc_pref();

  int ans = 0;
  for (int i = 0; i <= n; ++i) {
    if (cnt_ones(i - 1, 0) > 0) {
      break;
    }
    ans += try_for(i);
  }
  printf("%d\n", ans);
  return 0;
}
