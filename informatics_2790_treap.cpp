#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int INF = 2e9;
const int MAX_N = 2e5 + 5;

struct node {
  int prior;
  int cnt;
  int min;
  node *l, *r;
  node() {
    cnt = 0;
    min = INF;
  }
};

typedef node * pnode;

node pool[MAX_N];
int cur_node_idx = 0;

pnode make_node(int prior) {
  pool[cur_node_idx].prior = prior;
  pool[cur_node_idx].min = prior;
  return &pool[cur_node_idx++];
}

int cnt(pnode t) {
  return t ? t->cnt : 0;
}

int get_min(pnode t) {
  return t ? t->min : INF;
}

void upd_everything(pnode t) {
  if (t) {
    t->cnt = 1 + cnt(t->l) + cnt(t->r);
    t->min = min(t->prior, min(get_min(t->l), get_min(t->r)));
  }
}

void merge(pnode &t, pnode l, pnode r) {
  if (!l || !r) {
    t = r ? r : l;
  } else {
    if (l->prior > r->prior) {
      merge(l->r, l->r, r); t = l;
    } else {
      merge(r->l, l, r->l); t = r;
    }
  }
  upd_everything(t);
}

void print_tree(pnode t) {
  if (t) {
    cout << "prior: " << t->prior << ", cnt " << t->cnt << ", min: " << t->min << endl;
    cout << "going left\n";
    print_tree(t->l);
    cout << "return from left of " << t->prior << endl;
    cout << "going right\n";
    print_tree(t->r);
    cout << "return from right of " << t->prior << endl;
  }
}

void split(pnode t, pnode &l, pnode &r, int key, int add=0) {
  if (!t) {
    l = r = nullptr;
  } else {
    int cur_key = add + cnt(t->l);
    if (cur_key < key) {
      split(t->r, t->r, r, key, cur_key + 1); l = t;
    } else {
      split(t->l, l, t->l, key, add); r = t;
    }
    upd_everything(t);
  }
}

void add_pos(pnode &t, int pos, int prior) {
  pnode pos_node = make_node(prior);
  pnode prev;
  pnode remain;
  split(t, prev, remain, pos);
  merge(prev, prev, pos_node);
  merge(t, prev, remain);
}

int query_min(pnode t, int l, int r) {
  pnode t1;
  pnode t2;
  pnode t3;
  split(t, t1, t2, l);
  split(t2, t2, t3, r - l + 1);
  int ans = get_min(t2);
  merge(t, t2, t3);
  merge(t, t1, t);
  return ans;
}

int main() {
  pnode treap = nullptr;
  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    char c;
    int a, b;
    cin >> c >> a >> b;
    if (c == '?') {
      cout << query_min(treap, a - 1, b - 1) << "\n";
    } else {
      add_pos(treap, a, b);
    }
  }
  return 0;
}
