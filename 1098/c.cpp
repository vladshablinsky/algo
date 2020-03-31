#include <iostream>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

long long calc_min_for(long long n, long long branching) {
  int level = 0;
  long long cur_cnt = 0;
  long long cur_level_nodes = 1;
  while (cur_cnt + cur_level_nodes <= n) {
    ++level;
    cur_cnt += cur_level_nodes;
    cur_level_nodes *= branching;
  }

  long long result = (n - cur_cnt) * (level + 1);
  long long cur_subtree_sum = 1;
  for (int i = 0; i < level; ++i) {
    cur_level_nodes /= branching;
    result += cur_level_nodes * cur_subtree_sum;
    cur_subtree_sum *= branching;
    cur_subtree_sum++;
  }
  return result;
}

long long calc_max_for(long long n, long long branching) {
  return n * (n + 1) / 2 - (branching) * (branching - 1) / 2;
}

void gen_solution(int n, int branching, long long s) {
  //cout << "gen_solution: " << branching << endl;
  map<long long, vector<int>> mp;
  vector<int> v(n, 0);
  vector<int> cnt_sons(n, 1);
  for (int i = 0; i < n; ++i) {
    mp[i] = {i}; // on level i vertex i.
    v[i] = i - 1; // i'th parent is
  }


  long long cur_s = calc_max_for(n, 1);
  for (int i = n - 1; i >= 0 && cur_s != s; --i) {
    cnt_sons[i] = 0;
    mp.erase(i);
    auto it = mp.lower_bound(s - cur_s + i - 1);
    cur_s += it->first + 1 - i;
    int v_to_use = it->second.back();
    v[i] = v_to_use; // link i to v_to_use
    mp[it->first + 1].push_back(i); // add to vertices with that depth

    if (++cnt_sons[v_to_use] == branching) {
      it->second.pop_back();
      if (it->second.empty()) {
        mp.erase(it);
      }
    }
  }
  // cout << "now cur_s is " << cur_s << endl;
  for (int i = 1; i < n; ++i) {
    cout << v[i] + 1 << " ";
  }
  cout << "\n";
}

int main() {
  int n;
  long long s;
  cin >> n >> s;
  for (int i = 1; i < n; ++i) {
    if (s >= calc_min_for(n, i) && s <= calc_max_for(n, i)) {
      cout << "Yes\n";
      gen_solution(n ,i, s);
      return 0;
    }
  }
  cout << "No\n";
  return 0;
}
