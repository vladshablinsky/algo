#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

constexpr int kMod = 1000000007;
constexpr int kMax = 1000000000;

int msb_idx(int x) {
  for (int i = 30; i >= 0; --i) {
    if (x & (1 << i)) {
      return i;
    }
  }
  return 0;
}

template<typename Set>
bool traverse(int xx, const Set& st) {
  int x = xx;
  for(;;) {
    if (x != xx && st.count(x)) {
      return true;
    }

    if (!(x & 3)) {
      x /= 4;
      continue;
    }
    if ((x & 1) && x > 2) {
      x -= 1;
      x /= 2;
      continue;
    }

    break;
  }
  return false;
}

int main() {
  int n, p;
  scanf("%d%d", &n, &p);

  set<int, std::greater<int>> st;
  vector<int> to_erase;
  for (int i = 0; i < n; ++i) {
    int el;
    scanf("%d", &el);
    st.insert(el);
  }

  for (auto el: st) {
    if (traverse(el, st)) {
      to_erase.push_back(el);
    }
  }

  for (auto el: to_erase) {
    st.erase(el);
  }

  vector<int> cnts(p, 0);
  for (auto el: st) {
    //cout << "base: " << base << ", min: " << mn << endl;
    int idx = msb_idx(el);
    if (idx < p) {
      cnts[idx]++;
    }
  }

  int ans = 0;
  for (int i = 0; i < p; ++i) {
    cnts[i] %= kMod;
    //cout << "i: " << i << ", cnts: " << cnts[i] << endl;
    for (int j = 1; i + j < p && j <= 2; ++j) {
      cnts[i + j] += cnts[i];
      cnts[i + j] %= kMod;
    }

    ans += cnts[i];
    ans %= kMod;
  }

  cout << ans << "\n";
}
