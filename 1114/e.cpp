#include <iostream>
#include <cstdio>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <random>
#include <chrono>

using namespace std;

const int INF = 1e9;
const int MAX_QUERIES = 60;

int gcd(int a, int b) {
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}

int main() {
  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

  int n;
  int left_queries = MAX_QUERIES;

  cin >> n;

  int l = 0, r = INF;
  int ans_max = r;
  while (l <= r) {
    int m = (l + r) / 2;
    int result;
    cout << "> " << m << "\n";
    --left_queries;
    cin >> result;
    if (!result) {
      ans_max = min(ans_max, m);
      r = m - 1;
    } else {
      l = m + 1;
    }
  }

  vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    v[i] = i + 1;
  }
  shuffle(v.begin(), v.end(), rng);

  vector<int> known_elements;
  known_elements.push_back(ans_max);

  for (int i = 0; i < n && left_queries; ++i) {
    cout << "? " << v[i] << "\n";
    --left_queries;
    int result;
    cin >> result;
    known_elements.push_back(result);
  }

  assert (known_elements.size() > 1);
  sort(known_elements.begin(), known_elements.end());
  int cur_gcd = known_elements[1] - known_elements[0];
  for (int i = 2; i < known_elements.size(); ++i) {
    cur_gcd = gcd(cur_gcd, known_elements[i] - known_elements[i - 1]);
  }

  cout << "! " << ans_max - cur_gcd * (n - 1) << " " << cur_gcd << "\n";
  cout.flush();
  return 0;
}
