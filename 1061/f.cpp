#include <iostream>
#include <cstdio>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

vector<int> eligible_vertices;

void fill_eligible_vertices(int n) {
  eligible_vertices.resize(n);
  for (int i = 0; i < n; ++i) {
    eligible_vertices[i] = i + 1;
  }
}

bool make_query(int a, int b, int c) {
  string q_ans;
  cout << "? " << a << " " << b << " " << c << "\n";
  cin >> q_ans;
  return q_ans[0] == 'Y';
}

void give_ans(int a) {
  cout << "! " << a << "\n";
  cout.flush();
}

int pop_rand_eligible() {
  swap(eligible_vertices.back(),
      eligible_vertices[rand() % eligible_vertices.size()]);
  int res = eligible_vertices.back();
  eligible_vertices.pop_back();
  return res;
}

bool check_leaf(int x) {
  int z = pop_rand_eligible();
  for (auto v: eligible_vertices) {
    if (make_query(z, x, v)) {
      eligible_vertices.push_back(z);
      return false;
    }
  }
  eligible_vertices.push_back(z);
  return true;
}

bool check_max_lca_leaf(int x, int y, int h, vector<int> &between) {
  for (auto v: eligible_vertices) {
    if (make_query(x, v, y)) {
      between.push_back(v);
    }
  }
  if (between.size() != 2 * h - 1) {
    between.clear();
    return false;
  }
  return true;
}

int calc_height(int n, int k) {
  int cur_k = 1;
  int cur_h = -1;
  int cur_sum = 0;
  while (cur_sum < n) {
    cur_sum += cur_k;
    cur_k *= k;
    ++cur_h;
  }
  return cur_h;
}

int pop_any_leaf() {
  int leaf = -1;
  while (!check_leaf(leaf = pop_rand_eligible())) {
    eligible_vertices.push_back(leaf);
  }
  return leaf;
}

int pop_max_lca_leaf(int leaf, int h, vector<int> &between) {
  int res_leaf = -1;
  while (!check_max_lca_leaf(leaf, res_leaf = pop_rand_eligible(), h, between)) {
    eligible_vertices.push_back(res_leaf);
  }
  return res_leaf;
}

int main() {
  srand(time(0));
  int n, k;
  cin >> n >> k;
  fill_eligible_vertices(n);
  vector<int> between;
  int h = calc_height(n, k);
  int l1 = pop_any_leaf();
  int l2 = pop_max_lca_leaf(l1, h, between);

  vector<int> res = {l1, between.back(), l2};
  between.pop_back();

  for (auto b_v: between) {
    auto ins_it = res.begin();
    while (!make_query(*ins_it, b_v, *next(ins_it))) {
      ++ins_it;
      if (next(next(ins_it)) == res.end()) {
        break;
      }
    }
    res.insert(next(ins_it), b_v);
  }
  give_ans(res[res.size() / 2]);
  return 0;
}
