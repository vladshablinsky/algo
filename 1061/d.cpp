#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <list>
#include <deque>

using namespace std;

const int MOD = 1e9 + 7;

template<typename T>
T abs(T &x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

struct Event {
  int stamp;
  int length;
  int id;
  bool is_open;

  Event(int stamp, int length, int id, bool is_open)
    :stamp(stamp)
    ,length(length)
    ,id(id)
    ,is_open(is_open) {}

  bool operator<(const Event &other) const {
    if (stamp != other.stamp) {
      return stamp < other.stamp;
    } else {
      if (is_open != other.is_open) {
        return other.is_open; // this is closing, so it should be first
      } else {
        return length < other.length;
      }
    }
  }
};

int main() {
  vector<Event> segs;
  int n, x, y;

  scanf("%d%d%d", &n, &x, &y);
  for (int i = 0; i < n; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    segs.push_back(Event(l, r - l, i, true));
    segs.push_back(Event(r + 1, r - l, i, false));
  }

  //cout << (segs[5] < segs[8]) << endl;

  sort(segs.begin(), segs.end());

  // rent stamp and last time since tv available in inc order of last time
  deque<pair<int, int>> free_tvs;
  // rent stamp of tv processing i'th segment and last enqueue time
  vector<pair<int, int>> tv_rent_info(n);

  int price = 0;
  for (auto &el: segs) {
    bool is_open = el.is_open;
    int seg_id = el.id;
    int seg_stamp = el.stamp;

    // cout << "seg_id: " << seg_id << ", stamp: " << seg_stamp << ", is_open: " << is_open << endl;

    if (is_open) {
      while (!free_tvs.empty()) {
        long long use_old_add_price = y * 1ll * (seg_stamp - free_tvs.front().second + 1);
        long long rent_new_add_price = x;
        // cout << "for seg available from: " << free_tvs.front().second << ", use_old_add_price: " << use_old_add_price << ", rent new " << rent_new_add_price << endl;
        if (use_old_add_price > rent_new_add_price) {
          free_tvs.pop_front();
        } else {
          break;
        }
      }

      if (free_tvs.empty()) {
        price = (price + x) % MOD;
        tv_rent_info[seg_id] = make_pair(seg_stamp, seg_stamp);
        //cout << "add new, price += " << x << ", = " << price << endl;
      } else {
        int rent_stamp = free_tvs.back().first;
        int available_stamp = free_tvs.back().second;
        price = (y * 1ll * (seg_stamp - available_stamp + 1) + price) % MOD;
        //cout << "using prev, price += " << y * 1ll * (seg_stamp - available_stamp + 1) << ", = " << price << endl;
        tv_rent_info[seg_id] = make_pair(rent_stamp, seg_stamp);
        free_tvs.pop_back();
      }
    } else {
      int rent_stamp = tv_rent_info[seg_id].first;
      int seg_enqueue_stamp = tv_rent_info[seg_id].second;
      price = ((seg_stamp - seg_enqueue_stamp - 1) * 1ll * y + price) % MOD;
      //cout << "finishing segment, price += " << (seg_stamp - seg_enqueue_stamp - 1) * 1ll * y << ", rent_stamp: " << rent_stamp << ", enqueue: " << seg_enqueue_stamp << ", price: " << price << endl;
      free_tvs.push_back(make_pair(rent_stamp, seg_stamp));
    }
  }
  cout << price << "\n";
  return 0;
}
