#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <cstdio>

using namespace std;

struct st {
  int key;
  int id;
  st() {};
};

bool cmp1(st a, st b) {
  if (a.key == b.key)
    return a.id < b.id;
  return a.key < b.key;
}

bool cmp2(st a, st b) {
  return a.id < b.id;
}

st a[100005];
int n;

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int t;
    scanf("%d", &t);
    a[i].key = t;
    a[i].id = i;
  }
  sort(a, a + n, cmp1);
  for (int i = 0; i < n; ++i) {
    a[i].key = i + 1;
  }
  sort(a, a + n, cmp2);
  for (int i = 0; i < n; ++i) {
    printf("%d ", a[i].key);
  }
  cout << "\n";
  return 0;
}
