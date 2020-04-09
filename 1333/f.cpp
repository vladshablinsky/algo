#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int MAXN = 500005;

int smallest_div[MAXN];
vector<int> primes;

void make_primes() {
  smallest_div[1] = 1;
  for (int i = 0; i < MAXN; ++i) {
    smallest_div[i] = i;
  }
  for (int i = 2; i * i < MAXN; ++i) {
    if (smallest_div[i] == i) {
      primes.push_back(i);
      for (int j = i * i; j < MAXN; j += i) {
        smallest_div[j] = min(smallest_div[j], i);
      }
    }
  }
}

int main() {
  make_primes();
  int n;
  scanf("%d", &n);
  vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    if (smallest_div[i + 1] == i + 1) {
      v[i] = 1;
    } else {
      v[i] = (i + 1)/smallest_div[i + 1];
    }
  }
  sort(v.begin(), v.end());

  for (int i = 1; i < n; ++i) {
    printf("%d ", v[i]);
  }
  printf("\n");
  return 0;
}
