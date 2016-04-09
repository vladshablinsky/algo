#include <iostream>
#include <cstdio>

using namespace std;

void solve(int t_id) {
  int k, c, s;
  scanf("%d%d%d", &k, &c, &s);
  printf("Case #%d: ", t_id);
  for (int i = 0; i < k; ++i) {
    printf("%d ", i + 1);
  }
  printf("\n");
}

int main() {
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; ++i) {
    solve(i + 1);
  }
  return 0;
}
