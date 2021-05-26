#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 200005;

int points[2 * MAXN];
pair<int, int> segs[MAXN];
unordered_map<int, int> compressed;

int acquire_compressed() {
  static int cur = 0;
  return cur++;
}

struct Node {
  int del;
  int as_is;
} t[8 * MAXN];

void init(int v, int tl, int tr) {

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


int main() {
}
