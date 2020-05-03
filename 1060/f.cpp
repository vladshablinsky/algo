#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 52;

// f(i, j) -- is described as follows:
//   Suppose you rooted your tree at some vertex (no matter which for now).
//   Then, consider subtree made by node labeled i. Let's call it T_i.
//   T_i has a root in i now. Let's perform some shrinks there in T_i subtree.
//   Root of the subtree T_i may change or not -- we just don't care for now.
//   So it is possible that after some shrinks in T_i it is not even vertex
//   i in the root of subtree, but we remember that we fixed node that
//   initialy had label i.
//
//   Now let's suppose that we've made j shrinks and did not care at all
//   whether they changed something in T_i or not. Now we do care. Regardless
//   the label in T_i's root we now don't change it when perform shrinks.
//   Meaning if after we performed any j shrinks in T_i, we fix T_i's root
//   and any shrink involving it should not change it.
//
//   f(i, j) then, is a probability among all the ways to shrink T_i into
//   single node so that after first j shrinks (no matter what they are) we
//   don't change label at the root of T_i till the end. So it's probability
//   that we perform j shrinks and then T_i is shrunk to a single node having
//   label same as after j'th shrink in T_i.
//   Let's describe it in more details. Any all-tree-shrink of a tree is
//   described by a sequence of edges we shrink. Thus any all-tree-shrink
//   is some permutation of edges in T_i. f(i, j) goes among all permutations
//   and for each of them it counts
//   P{T_i's root doesn't change after j'th shrunk edge in current permutation}.
//   If size of T_i is S_i edges, then there are fact(S_i) permutations.
//   Then for f(i, j) we can say that it sums
//   P{current permutation} * P{T_i's root doesn't change after j'th shrunk in it}.
//   So, this is what f(i, j) is. The value of f(root, 0) is what we're asked in
//   the problem when we root our tree at 1...n and calculate f-function for
//   each such tree.
//
//   Now let's see how it can be obtained in rooted tree going from sons to parents.
//
//      x
//     /
//    /
//  T_i
//
//  Suppose now you have T_i with no shrinks yet and you extend it with x node
//  (thus adding one edge). Let's call this x-rooted tree T_i_x.
//  Also, suppose that you've already calculated f(i, l) for l in (0...S_i).
//  Let's now calculate g_x(j) for j in [0...S_i + 1], where g_x(j) stands for
//  probability that in T_i_x the root no longer changes after any first j
//  shrinks in T_i_x. This  is described pretty similar to f(i, j). g_x(j) sums
//  P{some permutation} * P{T_i_x root doesn't change after j-th shrunk in it}
//  among all sequencies (permutations) of T_i_x's edges.
//
//  How do we calculate g_x(j)?
//  Let's suppose the edge incident to x is removed after first l removals
//  already occured in T_i_x, thus removed (l+1)-th.
//  What does it contribute to g_x(j)?
//
//  a) If x-edge is removed when when more or equal than j edges already removed
//  in T_i_x, we 1) don't want x-edge to eliminate x 2) don't want any other
//  edge-shrinks after that (which can only then occur in T_i subtree)
//  to eliminate T_i_x's current root.
//
//  This case adds P{x-edge keeps x} * P{pick x-edge} * f(i, l) =
//  0.5 * (1 / (S_i + 1)) * f(i, l)
//
//  b) If l is less than j, then there are l shrinks in T_i not changing the
//  root obviously, then goes (l + 1)-th shrink of x-edge,
//  which we don't care either, and then other (j - l) shrinks come. This
//  is the same as only j - 1 shrink allowed in T_i.
//
//  This case adds P{pick x-edge} * f(i, j - 1).
//
//  To calculate g_x(j) for each j we should go through all possible l-s, where
//  l means that x-edge is removed after l shrinks in T_i or which is the same
//  in T_i_x.
//
//  OK, now we're able to calculate g_x. What's next? Suppose we have T_i_x
//  something like this i.e. some subtree.
//
//    +------------T_i_x                        +-------------T_i_x
//    |          .__/ |    Let's now            |          .__/  |\
//    |       ._/  /  |    have T_j             |       ._/  /   | \
//    |      / /  /   |    as follows:          |      / /  /    |  \
//    |        ._/    |                         |        ._/     |  T_j
//    |     ._/ /     |                         |     ._/ /      |
//    |    /   /      |                         |    /   /       |
//    |     ._/       |                         |     ._/        |
//    |    / /        |                         |    / /         |
//    |  .. ..        |                         |  .. ..         |
//    |               |                         |                |
//    +---------------+                         +----------------+
//
//  Are (x and T_i) case and (T_i_x and T_j) really a lot different?
//  It turns out they are not and we can calculate f(T_i_j_x, l) where
//  T_i_j_x -- is a tree obtained by adding T_j to T_i_x tree:
//
//    +-------------T_i_j_x
//    |              /|  |
//    |          .__/ |  |
//    |       ._/  /  |  |
//    |      / /  /  T_j |
//    |        ._/       |
//    |     ._/ /        |
//    |    /   /         |
//    |     ._/          |
//    |    / /           |
//    |  .. ..           |
//    |                  |
//    +------------------+
//
//  So how to calculate f(T_i_j_x, l) having g_{T_i_x} and f(T_i_x, l) already
//  calculated?
//
//  Let's suppose we have f(T_i_x, a) and g_{T_i_x}(b).
//  How does it contribute to f(T_i_j_x, a + b)?
//

vector<long double> f[MAXN];
vector<int> g[MAXN];
long double choose[MAXN][MAXN];

void init_choose() {
  for (int i = 0; i < MAXN; ++i) {
    choose[i][i] = 1.;
    choose[i][1] = 1.;
    choose[i][0] = 1.;
  }

  for (int i = 1; i < MAXN; ++i) {
    for (int j = 1; j < i; ++j) {
      choose[i][j] = choose[i - 1][j] + choose[i - 1][j - 1];
    }
  }
}

int dfs(int v, int p) {
  int sz = 1;
  f[v] = vector<long double>(1, 1.);

  for (auto to: g[v]) {
    if (to != p) {
      int to_size = dfs(to, v);

      vector<long double> g_to(to_size + 1, 0);
      for (int safe_shrinks_cnt = 0; safe_shrinks_cnt <= to_size; ++safe_shrinks_cnt) {
        for (int shrunk_after = 0; shrunk_after < to_size; ++shrunk_after) {
          if (shrunk_after < safe_shrinks_cnt) {
            g_to[safe_shrinks_cnt] += f[to][safe_shrinks_cnt - 1] / to_size;
          } else {
            // meaning we don't care about what was happening before
            // first shrunk_after shrinks, but after we shrink current edge
            // we care.
            g_to[safe_shrinks_cnt] += 0.5 * f[to][shrunk_after] / to_size;
          }
        }
      }

      vector<long double> new_f(sz + to_size);
      for (int safe_shrinks_cur = 0; safe_shrinks_cur < sz; ++safe_shrinks_cur) {
        for (int safe_shrinks_g = 0; safe_shrinks_g <= to_size; ++safe_shrinks_g) {
          // a = safe_shinks_cur
          // b = safe_shrinks_g
          //
          // f(v, a + b) +=
          // 1 / (s1 + s2)! *
          //  * [number of combinations so that first go a and b, then the others] *
          //  * [probability for each combination that root is not changed after a + b] =
          //  = [combinations a and b] * [combinations s1-a and s2-b] * [...]

          new_f[safe_shrinks_cur + safe_shrinks_g] +=
            choose[sz - 1][safe_shrinks_cur] * choose[to_size][safe_shrinks_g] /
            choose[sz + to_size - 1][safe_shrinks_cur + safe_shrinks_g] *
            f[v][safe_shrinks_cur] * g_to[safe_shrinks_g];
        }
      }
      f[v] = std::move(new_f);
      sz += to_size;
    }
  }
  return sz;
}

int main() {
  init_choose();
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n - 1; ++i) {
    int from, to;
    scanf("%d%d", &from, &to);
    g[from].push_back(to);
    g[to].push_back(from);
  }

  for (int i = 1; i <= n; ++i) {
    dfs(i, -1);
    printf("%.10Lf\n", f[i][0]);
  }
  return 0;
}
