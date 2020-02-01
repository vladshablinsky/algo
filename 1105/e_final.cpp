#include <iostream>
#include <vector>
#include <cstdio>
#include <unordered_map>
#include <unordered_set>

using namespace std;

const int MAXN = 40;
const int MAX_P = 20;
const int MAX_MASK = (1 << MAX_P) + 1;

int counter = 0;
int f[MAX_MASK];
long long neighbours_mask[MAXN];
unordered_map<string, int> mp;

int get_neighbours(int v, int shift=0) {
  return neighbours_mask[v] >> shift;
}

int get_f(int mask, int count, int shift) {
  if (mask == 0) {
    return 0;
  } else {
    if (!f[mask]) {
      int set_bits_cnt = 0;
      int ok_bits_cnt = 0;
      int cur_res = 0;
      for (int i = 0; i < count; ++i) {
        int cur_mask = (1 << i);
        if (!(mask & cur_mask)) {
          continue;
        }
        ++set_bits_cnt;
        int neighbours = get_neighbours(i + shift, shift);
        if ((mask & neighbours) == mask) {
          ++ok_bits_cnt;
        } else {
          cur_res = max(cur_res, get_f(mask ^ cur_mask, count, shift));
          cur_res = max(cur_res, get_f(mask & neighbours, count, shift));
        }
      }
      f[mask] = cur_res;
      if (ok_bits_cnt == set_bits_cnt) {
        f[mask] = set_bits_cnt;
      }
    }
    //cout << "get_f " << mask << ", shift: " << shift << ": " << f[mask] << endl;
    return f[mask];
  }
}

int main() {
  int n, m;
  cin >> n >> m;
  unordered_set<int> cur_block;

  auto make_block = [&]() {
    long long block_mask = 0;
    for (auto el: cur_block) {
      block_mask |= (1ll << el);
    }
    for (auto el: cur_block) {
      neighbours_mask[el] |= block_mask;
    }
    cur_block.clear();
  };

  for (int i = 0; i < n; ++i) {
    int query_type;
    cin >> query_type;
    if (query_type == 2) {
      string s;
      cin >> s;
      if (!mp.count(s)) {
        mp[s] = counter++;
      }
      cur_block.insert(mp[s]);
    } else {
      make_block();
    }
  }
  make_block();
  for (int i = 0; i < m; ++i) {
    neighbours_mask[i] ^= ((1ll << m) - 1); // inverted graph
    neighbours_mask[i] ^= (1ll << i); // add self to neighbours.
  }

  //for (int i = 0; i < m; ++i) {
  //  cout << "i: " << i << endl;
  //  for (int j = 0; j < m; ++j) {
  //    if (neighbours_mask[i] & (1 << j)) {
  //      cout << "(" << i << "," << j << ")" << endl;
  //    }
  //  }
  //}

  // neighbours and stuff initialized.

  // calculate right dp.
  int right_cnt = m - m / 2;  // vertices from 0 to right_cnt - 1
  int left_cnt = m - right_cnt; // vertices from right_cnt to m - 1

  //cout << "right: " << right_cnt << ", left: " << left_cnt << endl;

  int ans = 0;
  for (int mask = 0; mask < (1 << right_cnt); ++mask) {
    bool complete_graph = true;
    int right_part_size = 0;
    int mask_to_left_part = (1 << left_cnt) - 1;
    for (int j = 0; j < right_cnt; ++j) {
      if (mask & (1 << j)) {
        ++right_part_size;
        complete_graph &= ((mask & get_neighbours(j)) == mask);
        mask_to_left_part &= get_neighbours(j, right_cnt);
      }
      if (!complete_graph) {
        break;
      }
    }
    if (complete_graph) {
      int max_left_clique = get_f(mask_to_left_part, left_cnt, right_cnt);
      //cout << mask << " - compl graph on right side, mask_to_left_part is: " << mask_to_left_part << ", clique: " << max_left_clique << endl;
      ans = max(ans, right_part_size + max_left_clique);
    }
  }
  cout << ans << "\n";
  return 0;
}
