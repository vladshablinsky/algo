#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>
#include <unordered_map>

using namespace std;

const int MAXN = 100005;
const int INF = 1e9;
const int MAXK = 8;

const int OPEN = 1;
const int CLOSE = 0;

struct event {
  int x;
  int event_type;
  int segment_id;
  event(int x, int event_type, int segment_id):
    x(x), event_type(event_type), segment_id(segment_id) {};
  bool operator<(const event &other) const {
    if (x == other.x) {
      return event_type < other.event_type;
    } else {
      return x < other.x;
    }
  }
};

struct current_events_block {
  int x;
  int parity;
  current_events_block(): x(0), parity(0) {};
};

vector<event> events;
int segment_mask[MAXN];

vector<int> prev_f;
vector<int> cur_f;

vector<current_events_block> prev_g;
vector<current_events_block> cur_g;

// get open event idx by close segment_id
// can be used this way:
//    if we now at event `i` with some `mask` and it is a closing event,
//    what we want to know is a bit in the `mask` corresponding to this event
//    for that purpose we retrieve event `j` where `i` started and calculate
//    number of events `X` started after that before `i`. The bit corresponding
//    to `j`-open & `i`-close segment in the `mask` is 1 << X. X is calculated
//    with use of prefix sums of open segments. pref_sum_open[i] is the ovreall
//    number of open-events (thus opened segments) among first i events.
vector<int> pref_sum_open;
unordered_map<int, int> seg_id_to_open_idx;

string to_bits(int mask, int k) {
  string s;
  for (int i = 0; i < k; ++i) {
    s.push_back('0' + mask % 2);
    mask /= 2;
  }
  reverse(s.begin(), s.end());
  return s;
}

int main() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);

  k = min(n, k);

  for (int i = 0; i < n; ++i) {
    int seg_begin, seg_end;
    scanf("%d%d", &seg_begin, &seg_end);
    events.emplace_back(seg_begin, OPEN, i);

    // TODO: doublecheck
    events.emplace_back(seg_end + 1, CLOSE, i);
  }

  sort(events.begin(), events.end());

  prev_f.resize(1 << k, 0);
  cur_f.resize(1 << k);
  prev_g.resize(1 << k);
  cur_g.resize(1 << k);
  pref_sum_open.resize(events.size(), 0);

  auto cnt_add_from_mask_to_x = [](int mask, int x) {
    return (x - prev_g[mask].x) * (prev_g[mask].parity);
  };

  auto closed_segment_mask = [](int i) {
    return 1 << (pref_sum_open[i] - pref_sum_open[seg_id_to_open_idx[events[i].segment_id]]);
  };

  int result = 0;
  int closed_mask = 0;
  for (int i = 0; i < events.size(); ++i) {
    auto &e = events[i];

    // pref_sums and open-by-close retrieval
    if (i) {
      pref_sum_open[i] = pref_sum_open[i - 1];
    }
    if (e.event_type == OPEN) {
      seg_id_to_open_idx[e.segment_id] = i;
      cout << "OPEN: seg_id_to_open_idx(" << e.segment_id << ") = " << i << endl;
      pref_sum_open[i]++;
    } else {
      closed_mask = closed_segment_mask(i);
      cout << "CLOSE: " << i << ", open: " << seg_id_to_open_idx[e.segment_id] << endl;
      cout << "cl_mask: " << closed_mask << endl;
    }

    printf("event: (%d, %d), pref_sum_open: %d \n", e.x, e.event_type, pref_sum_open[i]);

    for (int mask = 0; mask < (1 << min(k, pref_sum_open[i])); ++mask) {
      cur_f[mask] = 0;
      if (e.event_type == OPEN) {
        int mask_first_unset = (mask >> 1);
        int mask_first_set = (mask >> 1) | (1 << (k - 1));
        int res_unset = prev_f[mask_first_unset] + cnt_add_from_mask_to_x(mask_first_unset, e.x);
        int res_set = prev_f[mask_first_set] + cnt_add_from_mask_to_x(mask_first_set, e.x);


        if (pref_sum_open[i] > k && res_set > res_unset) {
          cur_f[mask] = res_set;
          cur_g[mask].parity = (prev_g[mask_first_set].parity + (mask & 1)) & 1;
        } else {
          cur_f[mask] = res_unset;
          cur_g[mask].parity = (prev_g[mask_first_unset].parity + (mask & 1)) & 1;
        }

      } else { // CLOSE
        cur_f[mask] = prev_f[mask] + cnt_add_from_mask_to_x(mask, e.x);
        cur_g[mask].parity = prev_g[mask].parity;

        // cout << "c_mask(" << to_bits(mask, k) << ") " << to_bits(closed_segment_mask(i), k) << endl;
        // here what have been opened should be tracked!
        if (mask & closed_mask) {
          cur_g[mask].parity ^= 1;
        }
      }
      // common part: x always gets updated by the event.
      cur_g[mask].x = e.x;

      cout << "cur_f[" << to_bits(mask, k) << "] = " << cur_f[mask] << ", parity, x: (" << cur_g[mask].parity << ", " << cur_g[mask].x << ")" << endl;

      result = max(cur_f[mask], result);
    }
    swap(cur_f, prev_f);
    swap(cur_g, prev_g);
  }

  printf("%d\n", result);
  return 0;
}
