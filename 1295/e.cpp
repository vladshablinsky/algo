#include <iostream>
#include <cstdio>
#include <algorith>

using namespace std;

const int MAXN = 100005;

int p[MAXN];
int cost_i[MAXN];


int main() {
  int n;
  scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    scanf("%d", &p[i]);
  }

  for (int i = 0; i < n; ++i) {
    scanf("%d", &cost_i[p[i]]);
  }

  int cnt = 0;
  long long cost = 1000000000 * 1000000000;

  // Try to split after the first and find optimal;

  // Iterate over cnt on the left.
  long long rl_transfer_cost = 0;
  for (int i = 1; i <= n; ++i) {
    rl_transfer_cost += cost_i[p[i - 1]];

    int sub = (p[0] <= i) * cost_i[p[0]];
    if (rl_transfer_cost - sub < cost) {
      cost = rl_transfer_cost - sub;
      cnt = i;
    }
  }

  // Then check results if a barrier is initially set at i
  for (int i = 2; i <= n; ++i) {
    if (cnt >= p[i - 1]) {
      cost -= cost_i[p[i - 1]];
    }
  }

  cout << cost << "\n";

  return 0;
}
