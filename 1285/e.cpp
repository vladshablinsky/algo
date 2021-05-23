#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

const int MAXN = 200005;
const int INF = 1e9;
int points[2 * MAXN];
pair<int, int> segs[MAXN];
unordered_map<int, int> compressed;

int cnt_segs_left[2 * MAXN];
int mostright_open_seg_at[2 * MAXN];
int mostleft_open_seg_at[2 * MAXN];
int cnt_segs_right[2 * MAXN];

multiset<int> start_at[MAXN]; // store only two max
multiset<int> end_at[MAXN]; // store only two min

int acquire_compressed() {
  static int cur = 0;
  return cur++;
}

void solve() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &segs[i].first, &segs[i].second);
    points[2 * i] = segs[i].first;
    points[2 * i + 1] = segs[i].second;
  }

  // Initialize compressor
  sort(points, points + 2 * n);
  for (int i = 0; i < 2 * n; ++i) {
    if (compressed.count(points[i])) {
      compressed[points[i]] = acquire_compressed();
    }
  }

  // Compress points
  for (int i = 0; i < n; ++i) {
    segs[i].first = compressed[segs[i].first];
    segs[i].second = compressed[segs[i].second];
  }
  sort(segs, segs + n);

  int cnt_points = compressed.size();
  int cur_seg_idx = 0;
  int mostright_seg_end = -1;
  int union_power; // number of sets in the union

  // LEFT TO RIGHT
  for (int cur_point = 0; cur_point < cnt_points; ++cur_point) {
    // FIXME: what if several start at same point
    // possible fix: store separately
    mostright_open_seg_at[cur_point] = mostright_seg_end;
    cnt_segs_left[cur_point] = union_power;

    while (cur_seg_idx < n && segs[cur_seg_idx].first == cur_point) {
      end_at[cur_point].insert(segs[cur_seg_idx].second)
      if (mostright_seg_end < segs[cur_seg_idx].first) {
        ++union_power;
      }
      mostright_seg_end = max(mostright_seg_end, segs[cur_seg_idx].second);
      ++cur_seg_idx;
    }

    // Leave two max
    while (end_at[cur_point].size() > 2) {
      end_at[cur_point].erase(end_at[cur_point].begin());
    }
  }

  // RIGHT TO LEFT
  sort(segs, segs + n, [](pair<int, int>& a, pair<int, int>& b) {
    if (a.second == b.second) {
      return a.first > b.first;
    }
    return a.second > b.second;
  });

  cur_seg_idx = 0;
  union_power = 0;
  int mostleft_seg_end = INF;
  for (int cur_point = 0; cur_point < cnt_points; ++cur_point) {
    mostleft_open_seg_at[cur_point] = mostleft_seg_end;
    cnt_segs_right[cur_point] = union_power;

    while (cur_seg_idx < n && segs[cur_seg_idx].second == cur_point) {
      start_at[cur_point].insert(segs[cur_seg_idx].first);
      if (mostleft_seg_end > segs[cur_seg_idx].first) {
        ++union_power;
      }
      mostleft_seg_end = min(mostleft_seg_end, segs[cur_seg_idx].first);
      ++cur_seg_idx;
    }

    // Leave two min
    while (start_at[cur_point].size() > 2) {
      start_at[cur_point].erase(start_at[cur_point].rbegin());
    }
  }

  // Go throug all segments and update optimal solution.
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    int l = segs[i].first;
    int r = segs[i].second;


  }

}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
