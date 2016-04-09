#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

long long pow[13][18];
int a[16];
int cnt_printed = 0;

void init_pows() {
  for (int i = 2; i <= 10; ++i) {
    pow[i][0] = 1;
    for (int j = 1; j <= 15; ++j) {
      pow[i][j] = pow[i][j - 1] * 1ll * i;
    }
  }
}

long long is_prime(long long num) {
  if (num == 1 || num == 2) {
    return true;
  }
  for (long long i = 2; i * i <= num; ++i) {
    if (num % i == 0) {
      return i;
    }
  }
  return 0;
}

long long get_number_for(int base) {
  long long ans = 0;
  for (int i = 0; i < 16; ++i) {
    if (a[i] == 1) {
      ans += pow[base][i];
    }
  }
  return ans;
}

void rec(int pos) {
  if (cnt_printed == 50) {
    exit(0);
  }

  if (pos == 32) {
    vector<long long> ans;
    vector<long long> nums;
    for (int i = 2; i <= 10; ++i) {
      long long num = get_number_for(i);
      long long divisor = is_prime(num);
      ans.push_back(divisor);
      nums.push_back(num);
      if (divisor == 0) {
        return;
      }
    }
    for (int i = 15; i >= 0; --i) {
      printf("%d", a[i]);
    }
    printf(" ");
    for (int i = 0; i < ans.size(); ++i) {
      printf("%lld ", ans[i]);
    }
    //printf("\n");
    //printf("AUX OUTPUT\n");
    //for (int i = 0; i < nums.size(); ++i) {
      //printf("%lld ", nums[i]);
    //}
    printf("\n");

    ++cnt_printed;
    return;
  }
  rec(pos + 1);
  a[pos] = 1;
  rec(pos + 1);
  a[pos] = 0;
}

int main() {
  init_pows();
  a[0] = 1;
  a[31] = 1;
  cout << "Case #1:\n";
  rec(1);
  return 0;
}
