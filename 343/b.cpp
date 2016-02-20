#include <iostream>
#include <vector>
#include <cstdio>
#include <algorithm>

using namespace std;

int n;
int m_pos[500];
int f_pos[500];

int main() {
  int ans = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    char gender;
    int l, r;
    cin >> gender >> l >> r;
    if (gender == 'M') {
      m_pos[l]++;
      m_pos[r + 1]--;
    } else {
      f_pos[l]++;
      f_pos[r + 1]--;
    }
  }
  int m_today = 0;
  int f_today = 0;
  for (int i = 0; i < 500; ++i) {
    m_today += m_pos[i];
    f_today += f_pos[i];

    ans = max(ans, min(m_today, f_today) * 2);
  }
  cout << ans << "\n";
  return 0;
}
