#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXA = 1000006;
const int MAXN = 500005;

int cnt[MAXA];
int a[MAXN];

int main() {
  int n;
  long long sum = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    sum += a[i];
    cnt[a[i]]++;
  }

  vector<int> ans;
  for (int i = 0; i < n; ++i) {
    --cnt[a[i]];
    if ((sum - a[i]) % 2 == 0 &&
        (sum - a[i]) / 2 < MAXA &&
        cnt[(sum - a[i]) / 2]) {
      ans.push_back(i + 1);
    }
    ++cnt[a[i]];
  }

  printf("%d\n", (int)ans.size());
  for (auto idx: ans) {
    printf("%d ", idx);
  }
  printf("\n");
  return 0;
}
