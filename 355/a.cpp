#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 105;

int a[MAXN];

int main() {
  int n;
  cin >> n;

  int max_a = -1;
  int min_a = n + 1;
  int max_a_pos = -1;
  int min_a_pos = -1;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    if (a[i] < min_a) {
      min_a = a[i];
      min_a_pos = i;
    }
    if (a[i] > max_a) {
      max_a = a[i];
      max_a_pos = i;
    }
  }

  //cout << min_a_pos << " " << max_a_pos << endl;

  if (min_a_pos == 0 || min_a_pos == n - 1 || max_a_pos == 0 || max_a_pos == n - 1) {
    cout << n - 1 << "\n";
    return 0;
  }

  cout << max(max(min_a_pos, max_a_pos),
      max(n - min_a_pos - 1, n - max_a_pos - 1)) << "\n";

  return 0;
}
