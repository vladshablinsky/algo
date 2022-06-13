#include <iostream>
#include <cstdio>

using namespace std;

constexpr int kMaxN = 1000;

int t[kMaxN];

int sum(int r) {
    int res = 0;
    for (; r >= 0; r = (r & (r + 1)) - 1) {
        res += t[r];
    }

    return res;
}

int sum(int l, int r) {
    return sum(r) - sum(l - 1);
}

void add(int i, int d) {
    for (; i < n; i = (i | (i + 1))) {
        t[i] += d;
    }
}

int main() {
    int n = 20;
    for (int i = 0; i < n; ++i) {
        inc(i, i);
    }
}
