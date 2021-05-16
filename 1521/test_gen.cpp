#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include <random>
#include <ctime>

using namespace std;

vector<pair<int, int>> gen_tree_edges(int tree_size) {
  std::srand(std::time(nullptr));

  vector<pair<int, int>> result;
  int root = 1 + rand() % tree_size;
  vector<int> dyn_tree{root};
  for (int i = 1; i <= tree_size; ++i) {
    if (i != root) {
      result.push_back({i, dyn_tree[rand() % dyn_tree.size()]});
      dyn_tree.push_back(i);
    }
  }

  return result;
}

void print_test_instance(int test_cnt) {
  int n = 50;
  cout << test_cnt << endl;
  while (test_cnt--) {
    const auto& edges = gen_tree_edges(n);
    cout << edges.size() + 1 << endl;
    for (auto [from, to]: edges) {
      cout << from << " " << to << endl;
    }
  }
}

int main() {
  print_test_instance(1);
  return 0;
}
