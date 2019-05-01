#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int CIRCLE = 1;
const int TRIANGLE = 2;
const int SQUARE = 3;
const int INF = 1e9;

int cnt(char a, char b, char c) {
  if (a == -1 && b == -1) {
    return 0;
  }

  if (a == SQUARE && b == CIRCLE) {
    if (c == TRIANGLE) {
      return 2;
    } else if (c == SQUARE) {
      return 4;
    }
  }

  if (b == SQUARE) {
    if (c == CIRCLE) {
      return 4;
    }
  }

  if (b == CIRCLE) {
    if (c == SQUARE) {
      return 4;
    } else if (c == TRIANGLE) {
      return 3;
    }
  }

  if (b == TRIANGLE) {
    if (c == CIRCLE) {
      return 3;
    }
  }

  return INF;
}

int main() {
  int n;
  cin >> n;
  int ans = 0;
  int prev_prev = -1;
  int prev = -1;
  bool infinite = false;



  for (int i = 0; i < n; ++i) {
    int cur;
    cin >> cur;
    ans = min(INF, ans + cnt(prev_prev, prev, cur));
    prev_prev = prev;
    prev = cur;
  }

  if (ans == INF) {
    cout << "Infinite\n";
  } else {
    cout << "Finite\n";
    cout << ans << endl;
  }

  return 0;
}
