// Solution to:
// https://www.spoj.com/problems/MKTHNUM/
//
// Statement:
// Given an array of n different integer numbers
//
// answer online m queries:
// given i, j, k what is the k-th smallest
// number on the segment [i, ... j]
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

// 1e5
const int MAXN = 100005;
const int LOGN = 18;

// Our segment tree is going to count
// the number of elements in the range l, r
// Going down in the ST subtrees we can find the k'th element
struct Node {
  Node* l{nullptr};
  Node* r{nullptr};

  int val{0};
  int tl{0}, tr{0};
};

using pnode = Node*;

// Pool
Node pool[4 * MAXN * LOGN];

Node* acquire_node(int l, int r) {
  static int sz = 0;

  pool[sz].tl = l;
  pool[sz].tr = r;
  return &pool[sz++];
}

int a[MAXN];
pair<int, int> backmap[MAXN];

void build(pnode& root, int tl, int tr) {
  root = acquire_node(tl, tr);
  if (tl != tr) {
    int tm = (tl + tr) / 2;
    build(root->l, tl, tm);
    build(root->r, tm + 1, tr);
  }
}

pnode update(pnode root, int tl, int tr, int pos, int val) {
  pnode new_root = acquire_node(tl, tr);

  if (tl == tr) {
    new_root->val = val;
  } else {
    int tm = (tl + tr) / 2;
    *new_root = *root;

    if (pos <= tm) {
      new_root->l = update(root->l, tl, tm, pos, val);
    } else {
      new_root->r = update(root->r, tm + 1, tr, pos, val);
    }

    new_root->val = new_root->l->val + new_root->r->val;
  }

  return new_root;
}

int query(pnode a, pnode b, int k) {
  // cout << "query (" << b->tl << ", " << b->tr << "): " << b->val << " - " <<  a->val << endl;

  if (a->tl == a->tr) {
    // cout << "single!\n";
    return a->tl;
  }

  int l_val = b->l->val - a->l->val;
  // int r_val = b->r->val - a->r->val;
  if (l_val >= k) {
    // cout << "go left\n";
    return query(a->l, b->l, k);
  } else {
    // cout << "go right\n";
    // l_val < k
    return query(a->r, b->r, k - l_val);
  }
}

// Roots
Node* roots[MAXN];

void input_array(int n) {
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
}

void compress_array(int n) {
  for (int i = 1; i <= n; ++i) {
    backmap[i] = {a[i], i};
  }
  sort(backmap + 1, backmap + n + 1);

  int nxt = 1;
  for (int i = 1; i <= n; ++i) {
    if (i > 1 && backmap[i].first != backmap[i - 1].first) {
      ++nxt;
    }
    a[backmap[i].second] = nxt;

    backmap[nxt].first = backmap[i].first;
  }
  // to retrieve original a, you do backmap[a[i]].first;
  // cout << "compressed: ";
  // for (int i = 1; i <= n; ++i) {
  //   cout << a[i] << " ";
  // }
  // cout << endl;
  // cout << "backmapped: ";
  // for (int i = 1; i <= n; ++i) {
  //   cout << backmap[a[i]].first << " ";
  // }
  // cout << endl;
}

void init_persistent_tree(int n) {
  // Each time we do update, we store new root
  build(roots[0], 1, n);
  // cout << "root ok\n";
  for (int i = 1; i <= n; ++i) {
    roots[i] = update(roots[i - 1], 1, n, a[i], 1);
  }
  // cout << "init ok\n";
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  input_array(n);
  compress_array(n);
  init_persistent_tree(n);

  for (int i = 0; i < m; ++i) {
    int l, r, k;
    scanf("%d%d%d", &l, &r, &k);
    printf("%d\n", backmap[query(roots[l - 1], roots[r], k)].first);
  }
}
