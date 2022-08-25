#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <random>

using namespace std;

int main(int argc, char** argv) {
  int n = atoi(argv[1]);
  int m = atoi(argv[2]);

  set<pair<int, int>> st;
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist(1, n);

  while (st.size() != m) {
    int a = dist(rng);
    int b = dist(rng);
    if (a == b) {
      continue;
    }
    st.emplace(a, b);
  }

  int k = dist(rng);
  printf("%d %d %d\n", n, m, k);
  for (auto [from, to]: st) {
    printf("%d %d\n", from, to);
  }
  for (int i = 0; i < n; ++i) {
    printf("%d ", dist(rng));
  }
  printf("\n");
}
