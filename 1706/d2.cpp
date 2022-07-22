#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <cassert>
#include <algorithm>

using namespace std;

constexpr int kMaxN = 100001;
constexpr int kInf = 1000000000;

int a[kMaxN];

// el == 1 is a special case
// duplicates allowed. we don't care
void fill_batch(vector<pair<int, int>>& batch, int el, int p_start, int capacity) {
  // NOTE: zero must be added to batch explicitly
  // p_start cannot be greater than el
  assert(p_start <= el);

  if (el == 1 && batch.size() && batch.back().first == 1) {
    return;
  }

  // p > sqrt(el)
  // el / j  -- it is current p, j itself is the result of el / p
  for (int j = el / p_start; (el / j) * (el / j) >= el && batch.size() < capacity; ++j) {
    if (el / j > p_start) {
      continue;
    }
    batch.emplace_back(j, el / j);
  }

  p_start = batch.back().second - 1;
  // p <= squrt(el) -- just iterate
  for (int j = p_start; j >= 1 && batch.size() < capacity; --j) {
    batch.emplace_back(el / j, j);
  }
}

struct Entry {
  vector<pair<int, int>> batch;
  int el;
  int in_batch_i;
  Entry() = default;
  Entry(Entry&& e) = default;

  void update_if_threshold() {
    // can't extend anymore, p is already at 1
    if (batch[in_batch_i].second == 1) {
      return;
    }

    if (in_batch_i + kThreshold >= batch.size()) {
      vector<pair<int, int>> new_batch;
      new_batch.reserve(kBuf);

      // Note: no checks that kBuf is spacious enough
      // Push all elements left in batch to new_batch
      for (int i = in_batch_i; i < batch.size(); ++i) {
        new_batch.push_back(batch[i]);
      }

      fill_batch(new_batch, el, new_batch.back().second, new_batch.capacity());
      swap(batch, new_batch);
      in_batch_i = 0;
    }
  }

  static constexpr int kThreshold = 1;
  static constexpr int kBuf = 60;
};

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);

  multimap<int, Entry> mp;
  int mx = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);

    mx = max(mx, a[i]);

    Entry e;
    auto& batch = e.batch;
    batch.reserve(Entry::kBuf);
    e.el = a[i];

    // no sense starting from greater because it results in zero
    int sane_k = min(a[i] + 1, k);
    // entries in batch increase
    // j should decrease, entries increase
    batch.emplace_back(a[i] / sane_k, sane_k);
    if (sane_k - 1) {
      fill_batch(batch, a[i], sane_k - 1, batch.capacity());
    }

    e.in_batch_i = 0;
    assert(!batch.empty());
    mp.emplace(batch.front().first, std::move(e));
  }

  int res = kInf;
  for (;;) {
    int cur_mn = mp.begin()->first;
    int cur_mx = mp.rbegin()->first;
    // cout << cur_mn << " " << mp.begin()->second.batch[mp.begin()->second.in_batch_i].second << " -- " << mp.rbegin()->second.batch[mp.rbegin()->second.in_batch_i].second << " " << cur_mx << endl;
    res = min(res, cur_mx - cur_mn);

    if (cur_mx == cur_mn) {
      break;
    }

    // upd
    auto& entry = mp.begin()->second;

    // Ensure batch have enough elements
    entry.update_if_threshold();

    // we need to find in the batch maximum element so that it would be
    // smaller than the cur_mx; It is the lower_bound in reversed batch
    // with std::greater cmp
    auto target = make_pair(cur_mx, kInf);
    auto it = std::upper_bound(
        entry.batch.rbegin(),
        entry.batch.rend() - entry.in_batch_i - 1,
        target,
        std::greater<pair<int, int>>());

    if (it == entry.batch.rend() - entry.in_batch_i - 1) {
      // found itself => all in batch are too big. Should use it
      if (it != entry.batch.rbegin()) {
        entry.in_batch_i++;
      } else {
        // This is an important loop-terminate condition.
        // As long as one reaches its max min, we no longer proceed.
        break;
      }
    } else {
      entry.in_batch_i = std::distance(it, entry.batch.rend()) - 1;
    }

    Entry new_entry = std::move(entry);
    mp.erase(mp.begin());
    mp.emplace(new_entry.batch[new_entry.in_batch_i].first, std::move(new_entry));
  }

  printf("%d\n", res);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
