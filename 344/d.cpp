#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <deque>
#include <ctime>

using namespace std;

const int MAXN = 200000 + 5;
const int MAXP = 1e6 + 40;
const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;
int n, m;
int rand_val;

vector<pair<char, long long> > t;
vector<pair<char, long long> > s;

int p_pow1[MAXP];
int p_pow2[MAXP];
int h1_s[MAXN];
int h1_t[MAXN];
int h2_s[MAXN];
int h2_t[MAXN];

bool is_prime(int x) {
  if (x == 1 || x == 2) {
    return true;
  } else {
    for (int i = 2; i * 1ll * i <= x; ++i) {
      if (x % i == 0) {
        return false;
      }
    }
  }
  return true;
}

void init_hashes() {
  int p1 = 27000005;
  for(; !is_prime(++p1); );
  int p2 = p1;
  for(; !is_prime(++p2); );

  p_pow1[0] = 1;
  p_pow2[0] = 1;
  for (int i = 1; i < MAXP; ++i) {
    p_pow1[i] = (p_pow1[i - 1] * 1ll * p1) % MOD1;
    p_pow2[i] = (p_pow2[i - 1] * 1ll * p2) % MOD2;
  }

  for (int i = 0; i < s.size(); ++i) {
    int symb = ((s[i].second - 1) * 27 + 1 + s[i].first - 'a');
    h1_s[i] = (symb * 1ll * p_pow1[i]) % MOD1;
    h2_s[i] = (symb * 1ll * p_pow2[i]) % MOD2;
    if (i)  {
      h1_s[i] = (h1_s[i] + h1_s[i - 1]) % MOD1;
      h2_s[i] = (h2_s[i] + h2_s[i - 1]) % MOD2;
    }
  }

  for (int i = 0; i < t.size(); ++i) {
    int symb = ((t[i].second - 1) * 27 + 1 + t[i].first - 'a');
    h1_t[i] = (symb * 1ll * p_pow1[i]) % MOD1;
    h2_t[i] = (symb * 1ll * p_pow2[i]) % MOD2;
    if (i)  {
      h1_t[i] = (h1_t[i] + h1_t[i - 1]) % MOD1;
      h2_t[i] = (h2_t[i] + h2_t[i - 1]) % MOD2;
    }
  }
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    int cnt;
    char c;
    scanf("%d-%c", &cnt, &c);
    char prev_c = t.empty() ? '#' : t.back().first;
    if (prev_c == c) {
      t.back().second += cnt;
    } else {
      t.push_back(make_pair(c, cnt));
    }
  }

  for (int i = 0; i < m; ++i) {
    int cnt;
    char c;
    scanf("%d-%c", &cnt, &c);
    char prev_c = s.empty() ? '#' : s.back().first;
    if (prev_c == c) {
      s.back().second += cnt;
    } else {
      s.push_back(make_pair(c, cnt));
    }
  }

  init_hashes();
  long long ans = 0;

  if (t.size() < s.size()) {
    printf("0\n");
    return 0;
  }

  if (s.size() == 1) {
    for (int i = 0; i < t.size(); ++i) {
      if (t[i].first == s[0].first && t[i].second >= s[0].second) {
        ans += t[i].second - s[0].second + 1;
      }
    }
  } else if (s.size() == 2) {
    for (int i = 0; i < t.size() - 1; ++i) {
      if (t[i].first == s[0].first && t[i].second >= s[0].second &&
          t[i + 1].first == s[1].first && t[i + 1].second >= s[1].second) {
        ++ans;
      }
    }
  } else {
    for (int i = 1; i + s.size() - 2 < t.size() ; ++i) {
      int last_index = i + s.size() - 2;
      if (t[i - 1].first != s[0].first ||
          t[last_index].first != s.back().first ||
          t[i - 1].second < s[0].second ||
          t[last_index].second < s.back().second) {
        continue;
      }
      int h1 = (h1_t[i + s.size() - 3] - h1_t[i - 1] + MOD1) % MOD1;
      int h2 = (h1_s[s.size() - 2] - h1_s[0] + MOD1) % MOD1;

      int h3 = (h2_t[i + s.size() - 3] - h2_t[i - 1] + MOD2) % MOD2;
      int h4 = (h2_s[s.size() - 2] - h2_s[0] + MOD2) % MOD2;

      if (h1 == (h2 * 1ll * p_pow1[i - 1]) % MOD1 &&
          h3 == (h4 * 1ll * p_pow2[i - 1]) % MOD2) {
        ++ans;
      }
    }
  }

  cout << ans << "\n";

  return 0;
}
