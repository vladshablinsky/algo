#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

const int MAXN = 20000005;
// sieve[i] contains min prime divisor of this number;
int sieve[MAXN];
int cnt_prime_divisors[MAXN];

// this should be a linear sieve!
// TODO: implement
// NOTE: the sieve can be not necessarily linear. If the number is prime
// sieve[i] can be just zero... Or we can go through all the zeros and fill them
// on the final stage of the sieve initialization
// NOTE: non-linear sieve didn't make it...
void make_sieve() {
	vector<int> pr;
	for (int i = 2; i < MAXN; ++i) {
		if (sieve[i] == 0) {
			sieve[i] = i;
			pr.push_back(i);
		}
		for (int j = 0; j < (int)pr.size() && pr[j] <= sieve[i] && i * pr[j] < MAXN; ++j) {
			sieve[i * pr[j]] = pr[j];
		}
	}

  for (int i = 1; i < MAXN; ++i) {
    if (!sieve[i]) {
      sieve[i] = i;
    }

    // Nice thing for methodology!
    cnt_prime_divisors[i] = cnt_prime_divisors[i / sieve[i]];
    if (sieve[i] != sieve[i / sieve[i]]) {
      ++cnt_prime_divisors[i];
    }
  }
}

int solve() {
  int c, d, x;
  scanf("%d%d%d", &c, &d, &x);
  vector<int> divs_to_check;
  for (int i = 1; i * i <= x; ++i) {
    if (x % i == 0) {
      if ((x / i + d) % c == 0) {
        divs_to_check.push_back((x / i + d) / c);
      }

      if (int div = x / i; div != i && (x / div + d) % c == 0) {
        divs_to_check.push_back((x / div + d) / c);
      }
    }
  }

  int ans = 0;

  // go through all the divs_to_check and get the number of unique divs
  for (auto div: divs_to_check) {
    ans += (1 << cnt_prime_divisors[div]);
  }
  return ans;
}

int main() {
  make_sieve();
  int t;
  scanf("%d", &t);
  while (t--) {
    printf("%d\n", solve());
  }
}
