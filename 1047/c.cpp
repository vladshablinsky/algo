#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <memory.h>

using namespace std;

const int N = 1e8 / 2 + 5;
const int SQR = 1e4;

vector<bool> prime(SQR, true);
vector<bool> has_number(N);
unordered_map<int, vector<int>> divisors;
unordered_map<int, pair<int, int>> mp; // divisor -> (min power, cnt numbers with that power)
unordered_map<int, int> cnt_divisor;// how many numbers have this divisor

void sieve() {
  for (int i = 2; i * 1ll * i < N; ++i) {
    if (prime[i]) {
      for (int j = i * 2; j < N; j += i) {
        if (j < SQR) {
          prime[j] = false;
        }

        if (has_number[j]) {
          divisors[j].push_back(i);
        }
      }
    }
  }
}

int main() {
  int n;
  vector<int> v;
  scanf("%d", &n);
  v.resize(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &v[i]);
    has_number[v[i]] = true;
  }
  sieve();
  // cout << "sieved\n";

  for (int i = 0; i < n; ++i) {
    if (!divisors[v[i]].size() && !(v[i] == 1)) {
      divisors[v[i]].push_back(v[i]);
    }

    // cout << v[i] << " divisors: \n";
    int cur_v = v[i];
    for (auto div: divisors[v[i]]) {
      // cout << "div = " << div << " ";
      int pow = 0;
      long long powered_div = div;
      while (cur_v % div  == 0) {
        ++pow;
        cur_v /= div;
      }
      // cout << endl;

      auto it = mp.find(div);
      if (it != mp.end()) {
        if (it->second.first == pow) {
          it->second.second++;
        } else if (it->second.first > pow) {
          it->second.first = pow;
          it->second.second= 1;
        }
      } else {
        mp[div] = make_pair(pow, 1);
      }
      cnt_divisor[div]++;
    }

    if (cur_v != 1) {
      mp[cur_v].first = 1;
      mp[cur_v].second++;
      cnt_divisor[cur_v]++;
    }
  }

  int ans = n;
  for (auto &x: mp) {
    if (cnt_divisor[x.first] != n) {
      x.second = make_pair(0, n - cnt_divisor[x.first]);
    }

    // cout << " divisor " << x.first << " power " << x.second.first << " nums with that pow " << x.second.second << endl;
    ans = min(ans, x.second.second);
  }

  if (ans == n) {
    ans = -1;
  }
  printf("%d\n", ans);
  return 0;
}
