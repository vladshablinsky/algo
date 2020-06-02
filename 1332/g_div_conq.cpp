#include <iosteam>
#include <cstdio>

using namespace std;

const int MAXN = 200005;
int a[MAXN];
vector<int> ans;

ladders combine(ladders &l, ladders &r) {
  ladders res;


}

bool check_valid(int l, int r) {
  if (l == -1 || r == -1) {
    return false;
  }
  return true;
}

inline void is_inc(int l, int r) {
  return a[l] <= a[r];
}

inline void is_dec(int l, int r) {
  return a[l] >= a[r];
}

struct ladders {
  vector<int> points;
  pair<int, int> min_inc;
  pair<int, int> max_inc;
  pair<int, int> min_dec;
  pair<int, int> max_dec;
  ladders():
    min_inc(-1, -1), max_inc(-1, -1), min_dec(-1, -1), max_dec(-1, -1) {
  };

  void try_update_min_inc(int l, int r) {
    if (min_inc.first == -1) {
      if (is_inc(l, r)) {
        min_inc = {l, r};
      }
    } else {
      if ()
    }

  }

  void try_update_max_inc(int l, int r) {
    if (a[l] > a[r]) {
      return;
    }
  }

  void try_update_min_dec(int l, int r) {
    if (a[l] < a[r]) {
      return;
    }
  }

  void try_update_max_dec(int l, int r) {
    if (a[l] < a[r]) {
      return;
    }

  }

  void try_update_all(int l, int r) {
    try_update_min_inc(l, r);
    try_update_max_inc(l, r);
    try_update_min_dec(l, r);
    try_update_max_dec(l, r);
  }

  void combine(ladders &other) {
    min_here = get_min_point();
    max_here = get_max_point();
    min_other = other.get_min_point();
    max_other = other.get_max_point();

    if (min_inc == -1 && other.min_inc != -1) {
      min_inc = other.min_inc;
      max_inc = other.max_inc;
    }

    if (min_dec == -1 && other.min_dec != -1) {
      min_dec = other.min_dec;
      max_dec = other.max_dec;
    }

    if (min_inc == -1 && (min_here != -1 && ))

  }

  int get_min_point() {
    int ans = min_inc.first;
    if (ans == -1 || (min_dec.second != -1 && a[ans] > a[min_dec.second])) {
      ans = min_dec.second;
    }
    return ans;
  }

  int get_max_point() {
    int ans = max_inc.second;
    if (ans == -1 || (max_dec.first != -1 && a[ans] < a[max_dec.first])) {
      ans = max_dec.first;
    }
  }
};

// r - l < 3
ladders make_small_ladders(int l, int r) {
  ladders res;
  if (a[l] <= a[r]) {
    res.min_inc = res.max_inc = {l, r};
  }
  if (a[l] >= a[r]) {
    res.min_dec = res.max_dec = {l, r};
  }

  if (r - l == 2) {
    if (a[l] <= a[l + 1] && a[l + 1] <= a[r]) {
      res.min_inc.second = res.max_inc.first = l + 1;
    }
    if (a[l] >= a[l + 1] && a[l + 1] >= a[r]) {
      res.min_dec.first = res.max_dec.second = l + 1;
    }

    // small, big, small
    if (a[l] <= a[l + 1] && a[l + 1] >= a[r]) {
      if (min_inc.first == -1) {
        min_inc = max_inc = {l, l + 1};
      } else {
        max_inc.second = l + 1;
      }

      if (min_dec.first == -1) {
        min_dec = max_dec = {l + 1, r};
      } else {
        max_dec.first = l + 1;
      }
    }
    // big, small, big
    if (a[l] >= a[l + 1] && a[l + 1] <= a[r]) {
      if (min_inc.first == -1) {
        min_inc = max_inc = {l + 1, r};
      } else {
        min_inc.first = l + 1;
      }

      if (min_dec.first == -1) {
        min_dec = max_dec = {l, l + 1};
      } else {
        min_dec.second = l + 1;
      }
    }
  }
  return res;
}

ladders rec(int l, int r) {
  if (l >= r) {

  }
  if (r - l < 3) {
    return make_small_ladders(l, r);
  }
  int m = (l + r) / 2;
  auto ladl = rec(l, m);
  auto ladr = rec(m + 1, r);
  ladl.combine(ladr);
  return ladl;
}

void solve(int l, int r) {
  ans.clear();


}

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }

  for (int i = 0; i < q; ++i) {
    int l, r;
    scanf("%d%d", &l, &r);
    solve(l, r);
  }

  return 0;
}
