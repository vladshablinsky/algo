#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN=300005;

long long pref[MAXN];
long long max_l[MAXN];
long long max_r[MAXN];
long long a[MAXN];

// f(i) is max segment sum ending in i and with a group of x-multiplied elements
long long f[MAXN];

int main() {
  long long n, x;
  cin >> n >> x;
  long long cur_pref_s = 0;

  long long min_left = 0;
  long long max_segment = 0;

  for (int i = 0; i < n; ++i) {
    cin >> a[i];

    // calc prefix related  stuff
    cur_pref_s += a[i];
    pref[i] = cur_pref_s;

    min_left = min(min_left, cur_pref_s);
    max_l[i] = cur_pref_s - min_left;
    max_segment = max(max_l[i], max_segment);
  }

  long long min_right = 0;
  long long cur_post_s = 0;
  for (int i = n - 1; i >= 0; --i) {

    cur_post_s += a[i];
    min_right = min(min_right, cur_post_s);
    max_r[i] = cur_post_s - min_right;
  }

  for (int i = 0; i < n; ++i) {
    f[i] = max(
        max_l[i],                      // x-multiplied group begins from i + 1
        (i ? f[i - 1] : 0) + x * a[i]  // x-multiplied group already began
    );
    max_segment = max(max_segment, f[i] + max_r[i + 1]);
  }

  cout << max_segment << "\n";
  return 0;
}
