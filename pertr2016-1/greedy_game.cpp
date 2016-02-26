#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1e5 + 5;
int n;

struct Data {
  int a, b;
  int id;
  Data() {};
  Data(int a, int b, int id): a(a), b(b), id(id) {};
};

Data a[MAXN];
Data b[MAXN];
int id_in_a[MAXN];
int id_in_b[MAXN];

// sort for first player
bool cmp_1(Data d1, Data d2) {
  if (d1.a == d2.a) {
    return d1.b > d2.b;
  } else {
    return d1.a > d2.a;
  }
}

// sort for second player
bool cmp_2(Data d1, Data d2) {
  if (d1.b == d2.b) {
    return d1.a > d2.a;
  } else {
    return d1.b > d2.b;
  }
}

void proceed_first(int &i) {
  while (a[i].id == -1 && i < n) {
    ++i;
  }
  if (i == n) {
    return;
  }
  // cout << " take " << a[i].a << " from first " << " index was " << a[i].id << endl;
  b[id_in_b[a[i].id]].id = -1;
  ++i;
}

int proceed_second(int &i) {
  while (b[i].id == -1 && i < n) {
    ++i;
  }
  if (i == n) {
    return 0;
  }
  // cout << " take " << b[i].b << " from second " << " index was " << b[i].id << endl;
  a[id_in_a[b[i].id]].id = -1;
  return b[i++].b;
}

int main() {
  freopen("game.in", "r", stdin);
  freopen("game.out", "w", stdout);
  long long ans = 0;
  int t;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &t);
    a[i].id = i;
    a[i].a = t;
    b[i].a = t;
    b[i].id = i;
  }

  for (int i = 0; i < n; ++i) {
    scanf("%d", &t);
    a[i].b = t;
    b[i].b = t;
  }

  sort(a, a + n, cmp_1);
  sort(b, b + n, cmp_2);

  //for (int i = 0; i < n; ++i) {
    //cout << a[i].a << " ";
  //}
  //cout << endl;
  //for (int i = 0; i < n; ++i) {
    //cout << a[i].b << " ";
  //}
  //cout << endl;
  //cout << " ============== " << endl;
  //for (int i = 0; i < n; ++i) {
    //cout << b[i].a << " ";
  //}
  //cout << endl;
  //for (int i = 0; i < n; ++i) {
    //cout << b[i].b << " ";
  //}
  //cout << endl;

  for (int i = 0; i < n; ++i) {
    id_in_a[a[i].id] = i;
    id_in_b[b[i].id] = i;
  }

  int cur_pos_a = 0;
  int cur_pos_b = 0;
  for (int i = 0; i < n; ++i) {
    if (i % 2 == 0) {
      proceed_first(cur_pos_a);
    } else {
      ans += proceed_second(cur_pos_b);
    }
  }
  cout << ans << "\n";
}
