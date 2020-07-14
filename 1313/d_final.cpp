#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 100005;
const int MAXK = 8;

const int OPEN = 1;
const int CLOSE = 0;

int mask_parities[1 << MAXK];

void init_parities() {
  for (int i = 0; i < (1 << MAXK); ++i) {
    mask_parities[i] = __builtin_popcount(i) & 1;
  }
}

string to_bits(int x, int k=3) {
  string ans;
  for (int i = 0; i < k; ++i) {
    ans.push_back('0' + ((x & (1 << (k - i - 1))) != 0));
  }
  return ans;
}

struct event {
  int x;
  int event_type;
  int segment_id;
  event() = default;
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

int insert_one_bit_mask(int mask, int target, bool use_mask) {
  // cout << "target: " << to_bits(target) << ", mask: " << to_bits(mask) << endl;
  // cout << "shift left: " << to_bits((target & ~(mask - 1)) << 1) << ", right_part: " << to_bits((target & (mask - 1))) << ", middle: " << to_bits(mask * use_mask) << endl;

  return ((target & ~(mask - 1)) << 1) | (target & (mask - 1)) | (mask * use_mask);
}

// support current event & last event + querying masks
struct prefix_events_view {
  vector<int> open_segments_ids;

  int last_event_type;
  int last_event_mask;
  int last_event_i;

  prefix_events_view()
    : last_event_type(0), last_event_mask(0), last_event_i(0) {};

  int cnt_open() {
    return open_segments_ids.size();
  }

  int get_event_mask_bit(event &e) {
    last_event_type = e.event_type;
    if (e.event_type == OPEN) {
      return 0;
    } else {
      int idx_open;
      for (int i = 0; i < open_segments_ids.size(); ++i) {
        if (open_segments_ids[i] == e.segment_id) {
          idx_open = i;
          break;
        }
      }
      return  (open_segments_ids.size() - 1 - idx_open);
    }
  }

  void add_event(event &e) {
    // cout << "add event (" << e.x << ", " << e.event_type << ")\n";
    last_event_type = e.event_type;
    if (e.event_type == OPEN) {
      open_segments_ids.push_back(e.segment_id);
      last_event_mask = 1;
      last_event_i = 0;
    } else {
      int idx_open;
      for (int i = 0; i < open_segments_ids.size(); ++i) {
        if (open_segments_ids[i] == e.segment_id) {
          idx_open = i;
          break;
        }
      }

      //cout << "idx_open: " << idx_open << "cntopen: " << open_segments_ids.size() << endl;
      last_event_mask = (1 << (open_segments_ids.size() - 1 - idx_open));
      last_event_i = open_segments_ids.size() - 1 - idx_open;
      open_segments_ids.erase(open_segments_ids.begin() + idx_open);
    }
    // cout << "last_event_mask: " << last_event_mask << ": " << to_bits(last_event_mask) << endl;
  }

  vector<int> get_from_masks(int to_mask, int to_event_type) {
    int from_mask = to_mask;
    if (to_event_type == OPEN) {
      from_mask >>= 1;
    }

    if (last_event_type == OPEN) {
      return {from_mask};
    } else {
      return {
        insert_one_bit_mask(last_event_mask, from_mask, false),
        insert_one_bit_mask(last_event_mask, from_mask, true)
      };
    }
  }
};

vector<event> events;

vector<int> prev_f;
vector<int> cur_f;

int main() {
  init_parities();

  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);

  for (int i = 0; i < n; ++i) {
    int seg_begin, seg_end;
    scanf("%d%d", &seg_begin, &seg_end);
    events.emplace_back(seg_begin, OPEN, i);
    events.emplace_back(seg_end + 1, CLOSE, i);
  }
  sort(events.begin(), events.end());

  prev_f.resize(1 << k, 0);
  cur_f.resize(1 << k, 0);

  event prev_event = events[0]; // basically needed to add subsegments as we go.
  event cur_event;

  prefix_events_view view;
  view.add_event(prev_event);
  int ans = 0;
  for (int i = 1; i < events.size(); ++i) {
    int max_at_event = 0;
    cur_event = events[i];

    // cout << "i: " << i << " (" << cur_event.x << ", " << cur_event.event_type << ") " << endl;

    int min_bad_mask = (1 << (view.cnt_open() + (cur_event.event_type == OPEN)));
    for (int mask = 0; mask < min(1 << k, min_bad_mask); ++mask) {
      // cout << "mask: " << to_bits(mask) << endl;
      cur_f[mask] = 0;
      int len = cur_event.x - prev_event.x;
      // cout << "prev_event.x: " << prev_event.x << ", cur_event.x: " << cur_event.x << endl;
      // cout << "len: " << len << endl;
      // cout << "from masks: ";
      for (auto from_mask: view.get_from_masks(mask, cur_event.event_type)) {
        if (from_mask >= (1 << ((view.last_event_type == CLOSE) + view.cnt_open()))) {
          continue;
        }
        // cout << to_bits(from_mask) << ": f( " << to_bits(from_mask) << " ) = " << prev_f[from_mask] << endl;

        bool remove_last = (view.last_event_type == CLOSE) && ((view.last_event_mask & from_mask) != 0);
        bool should_count = (mask_parities[from_mask] ^ remove_last);
        cur_f[mask] = max(cur_f[mask], prev_f[from_mask] + len * should_count);
      }
      // cout << endl;
      // cout << "res: " << cur_f[mask] << endl;
      max_at_event = max(max_at_event, cur_f[mask]);
    }
    view.add_event(cur_event);

    // FIXME:
    // something wrong with parity & contribution.
    // cout << "max_at_event: " << max_at_event << endl;

    ans = max(ans, max_at_event);
    prev_event = cur_event;
    swap(prev_f, cur_f);
    // cout << "====================\n";
  }

  printf("%d\n", ans);
  return 0;
}
