#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <tuple>
#include <cmath>

using namespace std;

pair<int, int> query(int x) {
  int triplets, straights;
  cout << "+ " << x << "\n";
  cin >> triplets >> straights;
  return {triplets, straights};
}

int main() {
  int n;
  int triplets, straights;
  cin >> n;
  cin >> triplets >> straights;
  vector<pair<int, int>> deltas(n + 1);
  vector<int> a(n + 1);

  auto insert_delta = [&](int x) {
    auto new_vals = query(x);
    deltas[x] = {new_vals.first - triplets, new_vals.second - straights};
    std::tie(triplets, straights) = new_vals;
  };

  for (int i = n - 1; i >= 3; --i) {
    insert_delta(i);
  }
  insert_delta(1);
  int straights_first_ins = deltas[1].second;  // a_2 * (a_3 + 1)
  insert_delta(2);
  insert_delta(1);
  int straights_second_ins = deltas[1].second;  // (a_2 + 1) * (a_3 + 1)

  a[1] = (-1 + (int)sqrt(1 + 8 * deltas[1].first)) / 2;
  a[3] = straights_second_ins - straights_first_ins - 1;
  a[2] = straights_first_ins / (a[3] + 1);
  a[4] = (deltas[2].second - (a[3] + 1) * (a[1] + 1)) / (a[3] + 1) - (n != 4);

  for (int i = 3; i + 2 <= n; ++i) {
    a[i + 2] = (deltas[i].second - (a[i - 1] * a[i - 2] + a[i - 1] * (a[i + 1] + 1))) / (a[i + 1] + 1) - (i + 2 != n);
  }

  cout << "! ";
  for (int i = 1; i <= n; ++i) {
    cout << a[i] << " ";
  }
  cout.flush();
  return 0;
}
