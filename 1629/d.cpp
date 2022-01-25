#include <iostream>
#include <cstdio>
#include <set>

using namespace std;

const int BASE = 29;

inline int num(const string& s, bool reverse=false) {
  int start = 0;
  int end = s.length() - 1;
  int step = 1;
  if (reverse) {
    step *= -1;
    swap(start, end);
  }

  int result = 0;
  for (int i = start; ; i += step) {
    result *= BASE;
    result += (s[i] - 'a' + 1);
    if (i == end) {
      break;
    }
  }

  return result;
}


bool solve() {
  // number representing the segment + its occurence index
  // NOTE: store here singles, doubles and triples
  set<int> all;
  set<int> trimmed_tripples;

  int n;
  bool result = false;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;

    if (!result) {
      if (s.front() == s.back()) {
        result = true;
        continue;
      }

      // Check prev
      int num_s_rev = num(s, true);
      // cout << "CUR: " << num_s_rev << ", trim: " << num_s_rev / BASE << endl;
      if (all.count(num_s_rev)) {
        // Full match
        result = true;
      } else if (all.count(num_s_rev / BASE)) {
        // Trim current, checks:
        // 2 - 3 case
        result = true;
      } else if (trimmed_tripples.count(num_s_rev)) {
        // Trim prev, checks 3 - 2 case
        result = true;
      }

      // Add current
      // NOTE: no checks whether the length is 3 performed due to
      // even if the length is 2, we won't suck.
      int num_s = num(s);
      all.insert(num_s);
      trimmed_tripples.insert(num_s / BASE);

      // cout << "INSERT: " << num_s << ", trim: " << num_s/BASE << endl;
    }
  }
  return result;
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    if (solve()) {
      printf("YES\n");
    } else {
      printf("NO\n");
    }
  }
}
