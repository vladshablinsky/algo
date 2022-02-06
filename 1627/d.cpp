#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <map>

using namespace std;

const int MAXN = 1000005;

vector<int> divisors[MAXN];
int divisibles_gcd[MAXN];
bool present[MAXN];
int n;

int gcd(int a, int b) {
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}

void calc_divisors() {
  for (int i = 2; 2 * i < MAXN; ++i) {
    for (int j = 2 * i; j < MAXN; j +=i) {
      divisors[j].push_back(i);
    }
  }
  for (int i = 2; i < MAXN; ++i) {
    divisors[i].push_back(i);
  }
}

void input_array() {
  scanf("%d", &n);
  int el;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &el);
    present[el] = true;

    // cout << "processing " << el << endl;

    for (auto div: divisors[el]) {
      if (!divisibles_gcd[div]) {
        divisibles_gcd[div] = el;
      }
      divisibles_gcd[div] = gcd(divisibles_gcd[div], el);
      // cout << "divisibles gcd: " << div << " " << divisibles_gcd[div] << endl;
    }
    if (!divisibles_gcd[1]) {
      divisibles_gcd[1] = el;
    }
    divisibles_gcd[1] = gcd(divisibles_gcd[1], el);
  }
}

void solve() {
  int cnt = (!present[1] && divisibles_gcd[1] == 1);
  for (int i = 2; i < MAXN; ++i) {
    if (!present[i] && divisibles_gcd[i] == i) {
      ++cnt;
    }
  }

  printf("%d\n", cnt);
}

int main() {
  calc_divisors();
  input_array();
  solve();
}
