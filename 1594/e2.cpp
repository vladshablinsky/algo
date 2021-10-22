#include <iostream>
#include <cstdio>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <map>
#include <cassert>
#include <tuple>
#include <algorithm>

using namespace std;

const int MAXN = 2005;
const int MAXP = 61;
const int MOD = 1000 * 1000 * 1000 + 7;

// f[c1][i][c2] number of ways to
// start with color c1, make a path lenght i, and finish with color c2
int f[6][MAXP][6];

// 0 - w, forb 1
// 1 - y, forb 0
// 2 - g, forb 3
// 3 - b, forb 2
// 4 - r, forb 5
// 5 - o, forb 4
int get_color(const string& s) {
  static unordered_map<char, int> color_mapping{
      {'w', 0},
      {'y', 1},
      {'g', 2},
      {'b', 3},
      {'r', 4},
      {'o', 5}
  };
  return color_mapping[s[0]];
}

void init_f() {
  for (int c1 = 0; c1 < 6; ++c1) {
    f[c1][0][c1] = 1;
    // Init dp. May seem strange, but f(i, j, k) where j >= 1 will get correct.
    // for (int c2 = 0; c2 < 6; ++c2) {
    // }

    for (int i = 1; i < MAXP; ++i) {
      for (int c2 = 0; c2 < 6; ++c2) {
        for (int from = 0; from < 6; ++from) {
          if (from == c2 || (from ^ 1) == c2) {
            continue;
          }

          f[c1][i][c2] += f[c1][i - 1][from];
          f[c1][i][c2] %= MOD;
        }
      }
    }
  }

  // cout << "f: " << f[0][3][0] << endl;
}

int binpow(int a, long long p) {
  if (p == 0) {
    return 1;
  } else {
    if (p & 1) {
      return (a * 1ll * binpow(a, p - 1)) % MOD;
    } else {
      long long res = binpow(a, p / 2);
      return (res * res) % MOD;
    }
  }
}

int modmul(int a, int b) {
  return (a * 1ll * b) % MOD;
}

void modadd(int& a, int b) {
  a += b;
  a %= MOD;
}

struct Node {
  Node* p{nullptr};
  Node* l{nullptr};
  Node* r{nullptr};
  long long val{0};
  int depth{0};
  int color{0};
  bool fixed{false};
  int ways[6];
};

Node pool[MAXN * MAXP + 500];
Node* acquire_node(bool reset=false) {
  static int sz = 0;

  if (reset) {
    sz = 0;
  }

  pool[sz].p = pool[sz].l = pool[sz].r = nullptr;
  for (int i = 0; i < 6; ++i) {
    pool[sz].ways[i] = 1;
  }

  return &pool[sz++];
}

// returns up steps from a to lca
// a != b
// NOTE: lca must not be a or be!
tuple<long long, int, bool> find_lca(long long a, long long b) {
  assert(a != b);

  bool is_a_in_left_subtree = false;

  int ups = 0;
  while (a != b) {
    if (a < b) {
      b /= 2;
    } else {
      ++ups;
      is_a_in_left_subtree = !(a & 1);
      a /= 2;
    }
  }
  return {a, ups, is_a_in_left_subtree};
}

int k;
long long global_fours_cnt = 0;
void traverse(Node* v) {
  if (!v) {
    return;
  }

  if (v->fixed) {
    for (int i = 0; i < 6; ++i) {
      if (i != v->color) {
        v->ways[i] = 0;
      }
    }
  }
  traverse(v->l);
  traverse(v->r);


  // cout << "traverse: " << v->val << endl;
  auto& l = v->l;
  auto& r = v->r;
  --global_fours_cnt;
  if (l) {
    global_fours_cnt -= l->depth - v->depth  - 1;
  }
  if (r) {
    global_fours_cnt -= r->depth - v->depth - 1;
  }

  if (l && r) {
    int up1 = l->depth - v->depth;
    int up2 = r->depth - v->depth;
    int ll = l->val;
    int rr = r->val;

    //cout << "ll: " << ll << ", rr: " << rr << ", ups: " << up1 << ", " << up2 << endl;

    for (int v_to = 0; v_to <= (!v->fixed) * 5; ++v_to) {
      int v_color = v->color + v_to;
      v->ways[v_color] = 0;

      for (int left_from = 0; left_from <= (!l->fixed) * 5; ++left_from) {
        int l_color = l->color + left_from;
        for (int right_from = 0; right_from <= (!r->fixed) * 5; ++right_from) {
          int r_color = r->color + right_from;

          int left_single = modmul(l->ways[l_color], f[l_color][up1][v_color]);
          int right_single = modmul(r->ways[r_color], f[r_color][up2][v_color]);

          //printf("(%d,%lld) ->(%d,%lld) - %d\t", l_color, l->val, v_color, v->val, left_single);
          //printf("(%d,%lld) ->(%d,%lld) - %d\n", r_color, r->val, v_color, v->val, right_single);

          // combine left & right
          modadd(v->ways[v_color], modmul(left_single, right_single));
        }
      }
      //cout << v->ways[v_color] << "\n";
    }
     //cout << endl;
  } else if (l || r) { // all
    auto& child = l ? l : r;

    // Root may be artificially added, in that case iterate all colors.
    for (int v_to = 0; v_to <= (!v->fixed) * 5; ++v_to) {
      int v_color = v->color + v_to;
      v->ways[v_color] = 0;

      for (int v_from = 0; v_from <= (!child->fixed) * 5; ++v_from) {
        int from_color = child->color + v_from;
        modadd(v->ways[v_color],
            modmul(
              child->ways[from_color],
              f[from_color][child->depth - v->depth][v_color])
        );
      }
    }

    // cout << "ways: ";
    // cout << v->ways[v->color] << endl;

    // add not used subtree.
    //cout << "ONE CHILD:" << v->val << " ad to global\n";
    //auto all_subtree = (1ll << (k - v->depth)) - 1;
    //auto child_subtree = (1ll << (k - child->depth)) - 1;
    //auto len = child->depth - v->depth;
		//cout << "global: " << global_fours_cnt << endl;
    //global_fours_cnt += (all_subtree - child_subtree - len);
  } else {
    //cout << "NO CHILD:" << v->val << " ad to global\n";
    // no children at all. So we can do anything here
    // Looks like we can multiply later
    //global_fours_cnt += (1ll << (k - v->depth)) - 2;
    //cout << "global: " << global_fours_cnt << endl;
  }
}

int main() {
  init_f();

  int n;
  scanf("%d", &k);

  scanf("%d", &n);

  string s;
  long long node_id;
  // set<long long> st;
  Node* root = nullptr;
  unordered_map<long long, Node*> mp;
  for (int i = 0; i < n; ++i) {
    cin >> node_id >> s;
    Node* nd = mp[node_id] = acquire_node();
    nd->color = get_color(s);
    nd->ways[nd->color] = 1;
    nd->val = node_id;
    nd->fixed = true;
    if (node_id == 1) {
      root = nd;
    }
  }

  if (!root) {
    root = mp[1] = acquire_node();
    root->val = 1;
    root->depth = 0;
  }


  vector<long long> els;
  for (auto [el, _]: mp) {
    els.push_back(el);
  }
  sort(els.begin(), els.end());

  int cur_depth = 0;
  long long min_at_depth = 1;
  for (const auto el: els) {
    //cout << "el: " << el << endl;
    if (el == 1) {
      continue;
    }

    // Current node corresponding to el.
    Node* nd_ptr = mp[el];
    while (el >= min_at_depth * 2) {
      min_at_depth *= 2;
      cur_depth++;
    }

    nd_ptr->depth = cur_depth;
    //cout << "depth: " << cur_depth << endl;

    // Find node's parent
    long long prev_el = el;
    long long parent_el = el / 2;
    while (!mp.count(parent_el)) {
      prev_el = parent_el;
      parent_el /= 2;
    }
    Node* parent_nd = mp[parent_el];

    //cout << "parent: " << parent_nd->val << ", prev: " << prev_el << endl;

    // Attach parent to the node
    auto& attach_nd = (prev_el & 1) ? parent_nd->r : parent_nd->l;
    // cout << "prev_el " << prev_el << endl;
    if (attach_nd) {
      //cout << "attach already occupied with " << attach_nd->val << endl;
      auto [lca, ups, is_left] = find_lca(el, attach_nd->val);
      Node* lca_nd = mp[lca] = acquire_node();

      lca_nd->fixed = false;
      lca_nd->val = lca;
      lca_nd->p = attach_nd->p;
      lca_nd->depth = nd_ptr->depth - ups;
      //cout << "introduce new node lca(" << el << "," << attach_nd->val << "): " << lca << endl;

      attach_nd->p = lca_nd;
      nd_ptr->p = lca_nd;

      if (is_left) {
        //printf("  %d\n / \\\n%d %d\n", lca, nd_ptr->val, attach_nd->val);
        lca_nd->l = nd_ptr;
        lca_nd->r = attach_nd;
      } else {
        //printf("  %d\n / \\\n%d %d\n", lca, attach_nd->val, nd_ptr->val);
        lca_nd->l = attach_nd;
        lca_nd->r = nd_ptr;
      }

      // NOTE: important, update cur_el son!
      attach_nd = lca_nd;
    } else {
      attach_nd = nd_ptr;
      nd_ptr->p = parent_nd;
    }
    //cout << "attached to: " << nd_ptr->p->val << endl;
  }

  traverse(root);

  //cout << global_fours_cnt << endl;
  global_fours_cnt += (1ll << k) - 1;
  // cout << "glob fours: ";
  //cout << global_fours_cnt << endl;

  int fours = binpow(4, global_fours_cnt);
  int res = 0;
  for (int i = 0; i < 6; ++i) {
    modadd(res, root->ways[i]);
  }

  //cout << "RES: " << res << endl;

  cout << (fours * 1ll * res) % MOD << "\n";
  return 0;
}
