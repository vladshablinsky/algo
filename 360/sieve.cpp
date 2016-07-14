#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAX_N = 1e6 + 5;

int divisor[MAX_N];
int power[MAX_N];
int c[MAX_N];

void init() {
  divisor[1] = 1;
  for (int i = 2; i * 1ll * i < MAX_N; ++i) {
    if (divisor[i] == 0) {
      for (int j = i; j < MAX_N; j += i) {
        divisor[j] = i;
      }
    }
  }
  for (int i = 2; i < MAX_N; ++i) {
    if (divisor[i] == 0) {
      divisor[i] = i;
    }
  }
}

// divisor + cnt
vector<pair<int,int>> factorize(int x) {
  vector<pair<int, int>> ans;
  ans.push_back(make_pair(1, 1));
  while (x != 1) {
    if (divisor[x] == ans.back().first) {
      //cout << divisor[x] << " incrementing\n";
      ++ans.back().second;
    } else {
      //cout << divisor[x] << " put\n";
      ans.push_back(make_pair(divisor[x], 1));
    }
    x /= divisor[x];
  }
  return ans;
}

int main() {
  init();
  int n, k;
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &c[i]);
    //cout << " FACTORIZING " << c[i] << endl;
    vector<pair<int, int>> fact = factorize(c[i]);
    for (int j = 1; j < fact.size(); ++j) {
      //cout << " Factor " << fact[j].first << " power " << fact[j].second << endl;
      power[fact[j].first] = max(power[fact[j].first], fact[j].second);
    }
  }

  vector<pair<int,int>> k_fact = factorize(k);
  for(int i = 1; i < k_fact.size(); ++i) {
    if (power[k_fact[i].first] < k_fact[i].second) {
      printf("No\n");
      return 0;
    }
  }
  printf("Yes\n");
  return 0;
}
