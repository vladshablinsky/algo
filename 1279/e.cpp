#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const int MAXF = 21;
const int MAXN = 55;
long long fact[MAXF];

// f[i] is the number of good permutations starting with
// 1, 2, 3, ... i - 1
long long f[MAXN];

void init_fact() {
  fact[0] = 1;
  fact[1] = 1;
  for (int i = 2; i < MAXN; ++i) {
    fact[i] = fact[i - 1] * i;
  }
}

// input is an offset and initial permutation, with i -- currently
// being processed index and k -- the number of permutation to
// generate
//
// initial ans is
// x, x+1, x+2, ..., x+n-1
long long rec_perm(int offset, int i, long long k, vector<int>& ans) {
  int n = ans.size();
  if (i == 0) {
    return k;
  }

  auto insert_kth = [&](int kth) {

  };

  int rem = 0;
  long long cnt_suffix_perms = 1;
  long long cnt_next_suffix_perms = 1;
  if (n - i + 1 > 2) {
    cnt_suffix_perms = fact[n - i];
    cnt_next_suffix_perms = fact[n - i - 1];
  }

  if (cnt_suffix_perms < k) {
    k = rec_perm(offset, i - 1, k, ans);
  }
  rem = k % cnt_next_suffix_perms;
  insert_kth(k / cnt_next_suffix_perms - (rem == 0) + (k == 0));

  if (rem == 0) {
    k = fact[n - i];
  } else {
    k = rem;
  }
  return k;
}

// Try to generate lexi k-th good permutation leaving 1, ..., i-1 in place.
// If there are less than k good permutations with 1, ..., i-1 prefix,
// recursively try to generate k-th good permuation with 1,...,i-2 prefix.
// Once we find that there are more or equal to k permutations with
// 1,...,i-1 prefix fixed, we start filling the rest of it.
//
// We know that with 1,...,i-1 prefix unchanged first come the permutations
// [1...i-1] [i] [<blocks with i+1...n meeting NYP>],
// all these permutation follow in lexi order. smaller suffixes
// (blocks with i+1...n) go first.
//
// Then come
// [1...i-1] [i + 1, {i}], [<blocks with i+2...n meeting NYP>]]
// Again, these follow in lexi order
//
// Then come
// [1...i-1] [i + 2, {permutations of {i + 1, i}}], [{i + 3, ...., n}], ...
//
// First come smaller permutations, with lexi order suffixes,
// then follow bigger permutations, again with lexi ordered suffixes.
//
// etc.
//
// For all the above we know their number so we can find
// * Number x that goes after 1,...i-1
// * Number of the permutation of {i + 1, ..., x - 1}
// * Number of good permutation in a suffix supposing prefix of length x is fixed.
pair<int, long long> rec_nyp(int i, int n, long long k, vector<int> &ans) {
  if (i == 0) {
    return {n + 1, k};
  }

  cout << "rec_nyp " << i << ", " << k << endl;

  // * Calculate how many good permutations with 1...i-1 prefix there are,
  // * fill [x, {i + 1, ... x - 1}] part
  // * return the number of a good permutation suffix.
  auto fill_prefix = [&](long long perm_number) -> pair<int, long long> {
    cout << "=================>\nfill_prefix " << perm_number << ", i = " << i << endl;

    long long cnt_lexi_tails = 0;
    // extend the block starting at. The block must begin
    // with block_end to hold "good perm" invariant.
    for (int prefix_end = i; prefix_end <= n; ++prefix_end) {
      cout << "prefix end: " << prefix_end << endl;
      long long cnt_prefixes = 1;
      if (prefix_end > i) {
        cnt_prefixes = fact[prefix_end - i];
      }

      if (cnt_lexi_tails + cnt_prefixes * f[prefix_end + 1] >= perm_number) {
        // Lexi order of all good permutations has
        // f[prefix_end + 1] good permutations per each prefix permutation
        // so we first find what prefix is used.
        long long prefix_number = (perm_number - cnt_lexi_tails) / f[prefix_end + 1];
        long long suffix_number = (perm_number - cnt_lexi_tails) % f[prefix_end + 1];

        cout << "prefix_number: " << prefix_number << ", suf: " << suffix_number << endl;

        // TODO: fill ans[i] = block_end, then (ans[i + 1] ... ans[block_end])
        // with permutation number tail_permutation_number
        ans[i - 1] = prefix_end;
        vector<int> to_permutate;
        for (int j = i; j < prefix_end; ++j) {
          to_permutate.push_back(j);
        }

        cout << "to permutate: ";
        for (auto el: to_permutate) {
          cout << el << " ";
        }
        cout << endl;

        rec_perm(to_permutate.size(), prefix_number, to_permutate);
        cout << "permutated: ";
        for (auto el: to_permutate) {
          cout << el << " ";
        }
        cout << endl;

        for (int j = 0; j < to_permutate.size(); ++j) {
          ans[i + j] = to_permutate[j];
        }
        if (suffix_number == 0) {
          suffix_number = f[prefix_end + 1];
        }
        return {prefix_end + 1, suffix_number};
      } else {
        cnt_lexi_tails += cnt_prefixes * f[prefix_end + 1];
        cout << "cur cnt_lexi_tails: " << cnt_lexi_tails << endl;
      }
    }
    cout << "<=================\nfill prefix  f(" << i << ") = "  << cnt_lexi_tails << endl;
    f[i] = cnt_lexi_tails;
    return {i - 1, perm_number};
  };

  // this would fill the f[i], we should start with it always.
  auto [new_i, new_k] = fill_prefix(k);
  if (new_i < i) { // need to go deeper.

    std::tie(new_i, new_k) = rec_nyp(i - 1, n, k, ans);
    if (new_i < 0 || new_i > n) { // impossible
      new_i = n + 1;
    } else if (new_i == i) {
      std::tie(new_i, new_k) = fill_prefix(new_k);
    }

    // otherwise just return what found
  }
  return {new_i, new_k};
}

void solve() {
  int n;
  long long k;
  cin >> n >> k;
  f[n + 1] = 1;
  vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    v[i] = i + 1;
  }

  auto [_, rem] = rec_nyp(n, n, k, v);
  if (rem != 1) {
    cout << "-1\n";
  } else {
    for (auto el: v) {
      cout << el << " ";
    }
    cout << "\n";
  }
}

int main() {
  init_fact();

  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
