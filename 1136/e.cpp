#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <ctime>

using namespace std;

const int MAXN = 100005;
int a[MAXN];
int k[MAXN];
long long sum_k_1[MAXN];
long long sum_k_2[MAXN];
long long a_0;

struct node {
  node *l, *r;
  int cnt, prior;
  long long sum1;
  long long sum2;
  long long val1;
  long long val2;
  bool zero;
  node(): l(nullptr), r(nullptr), val1(0), val2(0), sum1(0), sum2(0), zero(false) {}
};

typedef node * pnode;
node pool[MAXN];
int cur_node = 0;
vector<int> priors(MAXN);

void init_priors() {
  srand(time(NULL));
  for (int i = 0; i < priors.size(); ++i) {
    priors[i] = i + 1;
  }
  random_shuffle(priors.begin(), priors.end());
}

pnode get_node() {
  if (cur_node == MAXN) {
    return nullptr;
  } else {
    pool[cur_node].prior = priors[cur_node];
    return &pool[cur_node++];
  }
}
pnode t = nullptr;

int cnt(pnode t) {
  return t ? t->cnt : 0;
}

long long sum1(pnode t) {
  return t ? t->sum1 : 0;
}

long long sum2(pnode t) {
  return t ? t->sum2 : 0;
}

void upd_cnt(pnode t) {
  if (t) {
    t->cnt = 1 + cnt(t->l) + cnt(t->r);
  }
}

void upd_sum(pnode t) {
  if (t) {
    t->sum1 = sum1(t->l) + sum1(t->r) + t->val1;
    t->sum2 = sum2(t->l) + sum2(t->r) + t->val2;
  }
}

void push(pnode t) {
  if (t && t->zero) {
    t->zero = false;
    t->val1 = t->val2 = 0;
    if (t->l) {
      t->l->val1 = t->l->val2 = t->l->sum1 = t->l->sum2 = 0;
      t->l->zero = true;
    }
    if (t->r) {
      t->r->val1 = t->r->val2 = t->r->sum1 = t->r->sum2 = 0;
      t->r->zero = true;
    }
  }
}

void split(pnode t, pnode &l, pnode &r, int key, int add = 0) {
  if (!t) {
    l = r = nullptr;
    return;
  }

  push(t);
  int cur_key = add + cnt(t->l);

  if (key <= cur_key) {
    split(t->l, l, t->l, key, add);
    r = t;
  } else {
    split(t->r, t->r, r, key, add + cnt(t->l) + 1);
    l = t;
  }

  upd_cnt(t);
  upd_sum(t);
}

void merge(pnode &t, pnode l, pnode r) {
  push(l);
  push(r);
  if (!l || !r) {
    t = l ? l : r;
  } else if (l->prior > r->prior) {
    merge(l->r, l->r, r);
    t = l;
  } else {
    merge(r->l, l, r->l);
    t = r;
  }
  upd_cnt(t);
  upd_sum(t);
}

void insert(pnode &t, pnode nd, int pos) {
  if (!t) {
    t = nd;
  } else {
    pnode t1, t2;
    split(t, t1, t2, pos);
    merge(t, t1, nd);
    merge(t, t, t2);
  }
}

// r is zero-indexed.
long long sum(int r, int n) {
  if (r <= 0) {
    return a_0 * (r + 1);
  }

  // split should be done to r - 1
  pnode less_eq, greater;
  split(t, less_eq, greater, r);

  // c_0 * (n - 1) + c_1 * (n - 2) + ... + c_{r-1} * (n - r)
  long long c_part1 = sum1(less_eq);
  long long c_part2 = sum2(less_eq);  // c_0 + c_1 + ... + c_{r - 1}
  long long k_part_1 = sum_k_1[r - 1];
  long long k_part_2 = sum_k_2[r - 1];

  //long long c_part = c_part1 - c_part2 * (n - r - 1); // c_0 * r + c_1 * (r-1) + c_{r-1}
  //long long k_part = sum_k_1[r - 1] - sum_k_2[r - 1] * (n - r - 1);

  merge(t, less_eq, greater);

  return a_0 * (r + 1) + (c_part1 + k_part_1) - (c_part2 + k_part_2) * (n - r - 1);
}

long long sum(int l, int r, int n) {
  return sum(r, n) - sum(l - 1, n);
}

int main() {
  init_priors();
  int n, q;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }

  a_0 = a[0];
  for (int i = 0; i < n - 1; ++i) {
    int k_i;
    scanf("%d", &k_i);
    long long c_i = a[i + 1] - a[i];
    c_i -= k_i;

    pnode cur_node = get_node();
    cur_node->val1 = (n - 1 - i) * c_i;
    cur_node->val2 = c_i;
    upd_sum(cur_node);

    insert(t, cur_node, i);

    sum_k_1[i + 1] = sum_k_1[i] += (n - 1 - i) * 1ll * k_i;
    sum_k_2[i + 1] = sum_k_2[i] += k_i;
  }


  scanf("%d", &q);
  for (int i = 0; i < q; ++i) {
    char c;
    cin >> c;
    if (c == '+') {
      int idx, x;
      scanf("%d%d", &idx, &x);

      --idx;

      // Increasing previous one
      if (idx != 0) {
        // set idx - 1
        pnode less_i, eq_i, greater_i;
        split(t, less_i, eq_i,  idx - 1); // from idx - 1 to last
        split(eq_i, eq_i, greater_i, 1); // get exactly idx - 1'th
        eq_i->val1 += (n - idx) * 1ll * x;
        eq_i->val2 += x;
        merge(eq_i, eq_i, greater_i);
        merge(t, less_i, eq_i);
      } else {
        a_0 += x;
      }

      // Decreasing next
      if (idx < n - 1) {
        int l = idx;
        int r = n - 2;

        pnode less_i, geq_i;
        split(t, less_i, geq_i, idx);

        pnode cur_node = geq_i;

        int ans_idx = r - l;
        int cur_add = 0;
        long long cur_x = x;

        // cout << "yo! " << cur_node->sum2 << endl;
        // cout << "ans_idx " << ans_idx << endl;

        while (cur_node) {
          push(cur_node);
          // cout << "x = " << cur_x << endl;
          // cout << cur_node->sum2 << endl;
          // cout << "left_sum2 is " << sum2(cur_node->l) << endl;
          if (sum2(cur_node->l) + cur_node->val2 >= cur_x) {
            ans_idx = min(ans_idx, cur_add + cnt(cur_node->l));
            //cout << "ans_idx " << ans_idx << endl;
            cur_node = cur_node->l;
          } else {
            cur_x -= (sum2(cur_node->l) + cur_node->val2);
            cur_add += cnt(cur_node->l) + 1;
            cur_node = cur_node->r;
          }
        }

        ans_idx += idx;

        // cout << "idx: " << idx << endl;
        // cout << "ans_idx: " << ans_idx << endl;

        pnode tail;
        split(geq_i, geq_i, tail, ans_idx - idx + 1);
        long long val2_to_set = max(0ll, geq_i->sum2 - x);

        pnode node_at_idx;
        split(geq_i, geq_i, node_at_idx, ans_idx - idx);
        node_at_idx->val1 = val2_to_set * (n - ans_idx - 1);
        node_at_idx->val2 = val2_to_set;

        if (geq_i) {
          geq_i->zero = true;
        }

        merge(geq_i, geq_i, node_at_idx);
        merge(geq_i, geq_i, tail);
        merge(t, less_i, geq_i);
      }

    } else if (c == 's') {
      int l, r;
      scanf("%d%d", &l, &r);
      --l; --r;
      // get sum
      // printf("%I64d\n", sum(l, r, n));
      printf("%I64d\n", sum(l, r, n));
      //

			//printf("%lld\n", sum(l, r, n));
    } else if (c == 'd') { // debug
      int idx;
      scanf("%d", &idx);
      pnode l, m, r;
      split(t, l, m, idx);
      split(m, m, r, 1);
      cout << m->val1 << ", " << m->val2 << endl;
      merge(m, m, r);
      merge(t, l, m);
    }
  }

  return 0;
}
