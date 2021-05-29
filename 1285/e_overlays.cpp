#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

const int MAXN = 200005;
const int INF = 1e9;
const int POINT = -1;
const int OPEN = 1;
const int CLOSE = 0;

pair<int, int> segs[MAXN];
vector<pair<int, int>> events;
unordered_map<int, int> compressed;
int overlay[6 * MAXN];
int cnt_zeros[6 * MAXN];
int cnt_ones[6 * MAXN];

void solve() {
  events.clear();
  compressed.clear();
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &segs[i].first, &segs[i].second);
    if (segs[i].first != segs[i].second) {
      events.push_back({segs[i].first, OPEN});
      events.push_back({segs[i].second, CLOSE});
    } else {
      events.push_back({segs[i].first, POINT});
    }
  }

  sort(events.begin(), events.end());

  // COMPRESS
  int cur_cover = 0;
  int cur_compressed = 1;
  int prev = -INF - 5;
  bool ends_with_empty;
  for (int i = 0; i < events.size(); ++i) {
    int cur = events[i].first;
    //cout << "event: " << cur << " " << events[i].second << endl;
    // Ensure next != cur
    int j = 0;
    while (i + j + 1 < events.size() && events[i + j + 1].first == cur) {
      //cout << "++\n";
      ++j;
    }

    // Always true for the first one. Thus first elements is 1 always.
    // if (cur - prev > 1) {
    //   cur_compressed++;
    // }
    compressed[cur] = cur_compressed++;
    // [x] added, add (x, x + 1] if this is not the last point
    if (events[i].second != OPEN &&
        (i + j + 1 < events.size() || (j && events[i + j].second == OPEN))) {
      cur_compressed++;
    }
    i += j;
    prev = cur;
  }

  for (int i = 0; i <= cur_compressed; ++i) {
    overlay[i] = 0;
  }

  // OVERLAYS
  for (auto event: events) {
    overlay[compressed[event.first]] += (event.second == OPEN) + (event.second == POINT);
    overlay[compressed[event.first] + 1] -= ((event.second == CLOSE) + (event.second == POINT));
  }
  // cout << "cur_compressed = " << cur_compressed << endl;

  for (int i = 1; i <= cur_compressed; ++i) {
    overlay[i] += overlay[i - 1];
    cnt_ones[i] = cnt_ones[i - 1] + (overlay[i] == 1);
    cnt_zeros[i] = cnt_zeros[i - 1] + (overlay[i] == 0);
  }

  // for (int i = 0; i <= cur_compressed; ++i) {
  //   cout << overlay[i] << " ";
  // }
  // cout << endl;

  // CALC
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    // Point
    int right;
    int left;
    int middle;

    int l = compressed[segs[i].first];
    int r = compressed[segs[i].second];

    // cout << "(" << segs[i].first << "," << segs[i].second << ") ->";
    // cout << "(" << l << ", " << r << ")" << endl;

    middle = cnt_ones[r] - cnt_ones[l - 1];
    left = cnt_zeros[l - 1];
    right = cnt_zeros[cur_compressed - 1] - cnt_zeros[r - 1];

    int sub = 0;
    sub += (overlay[l] == 1);
    sub += (r > l && overlay[r] == 1);
    sub += (l + 1 < r && overlay[l] == 1 && overlay[l + 1] == 1);
    sub += (r - 1 > l && overlay[r] == 1 && overlay[r - 1] == 1);

    // empty
    if (sub == r - l + 1) {
      middle = (overlay[l - 1] != 0 || overlay[r + 1] != 0);
    } else {
      middle -= sub;
      middle++;
      middle += (overlay[l - 1] != 0 && overlay[l] == 1);
      middle += (overlay[r + 1] != 0 && overlay[r] == 1);
    }

    // cout << "middle: " << middle << ", left: " << left << ", right: " << right << endl;
    // cout << "curans: " << middle + left + right << endl;
    ans = max(ans, middle + left + right);
  }
  printf("%d\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
  return 0;
}
