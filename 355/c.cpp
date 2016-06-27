#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;

int n, k;
int ans = 0;
string s;

int main() {
  scanf("%d%d", &n, &k);
  cin >> s;

  int l = 0, r = 0;
  int cnt_b = s[0] == 'b';

  // try to change all the b's into a's
  while (r < n) {
    if (cnt_b > k) {
      while (cnt_b > k && l <= r) {
        cnt_b -= s[l] == 'b';
        l++;
      }
      if (l > r) {
        r = l;
        cnt_b = s[r] == 'b';
      }
    } else {
      ans = max(ans, r - l + 1);
      if (r + 1 < n) {
        cnt_b += s[r + 1] == 'b';
        ++r;
      } else {
        break;
      }
    }
  }

  l = 0, r = 0;
  int cnt_a = s[0] == 'a';
  // try to change all the a's into b's
  while (r < n) {
    if (cnt_a > k) {
      while (cnt_a > k && l <= r) {
        cnt_a -= s[l] == 'a';
        l++;
      }
      if (l > r) {
        r = l;
        cnt_a = s[r] == 'a';
      }
    } else {
      ans = max(ans, r - l + 1);
      if (r + 1 < n) {
        cnt_a += s[r + 1] == 'a';
        ++r;
      } else {
        break;
      }
    }
  }

  cout << ans << "\n";
  return 0;
}
