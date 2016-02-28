#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 200000;

vector<int> a;
vector<int> b;
int n;

int main() {
  scanf("%d", &n);

  for (int i = 0; i < n; ++i) {
    int t;
    scanf("%d", &t);
    if (t == 0) {
      continue;
    }
    a.push_back(t);
  }
  for (int i = 0; i < n; ++i) {
    int t;
    scanf("%d", &t);
    if (t == 0) {
      continue;
    }
    b.push_back(t);
  }


  for (int i = 0; i < n - 1; ++i) {
    if (b[i] == a[0]) {
      for (int j = 0; j < n - 1; ++j) {
        if (a[j] != b[(i + j) % (n - 1)]) {
          cout << "NO\n";
          return 0;
        }
      }
      cout << "YES\n";
      return 0;
    }
  }
  return 0;
}
