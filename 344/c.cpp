#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <deque>

using namespace std;

const int MAXN = 200005;
int n, m;

int a[MAXN];
int r[MAXN];
vector<int> st;
vector<int> sorted_part;
deque<int> sorted_deq;

vector<int> res;

int mabs(int x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

bool cmp(int a, int b) {
  return a > b;
}

int main() {
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
  }
  for (int i = 0; i < m; ++i) {
    int q_id, tr;
    scanf("%d%d", &q_id, &tr);
    if (q_id == 1) {
      r[i] = tr;
    } else {
      r[i] = -tr;
    }
  }

  st.push_back(r[0]);

  for (int i = 1; i < m; ++i) {
    int head = mabs(st.back());
    int cur = r[i];
    int acur = mabs(r[i]);
    while (!st.empty() && mabs(st.back()) <= acur) {
      st.pop_back();
    }
    st.push_back(cur);
  }

  //cout << "STACK\n";
  //for (int i = 0; i < st.size(); ++i) {
    //cout << st[i] << " ";
  //}
  //cout << endl;

  for (int i = 0; i < mabs(st[0]); ++i) {
    sorted_part.push_back(a[i]);
  }

  sort(sorted_part.begin(), sorted_part.end());

  //cout << "SORTED\n";
  for (int i = 0; i < sorted_part.size(); ++i) {
    //cout << sorted_part[i] << endl;
    sorted_deq.push_back(sorted_part[i]);
  }


  for (int i = 0; i < st.size(); ++i) {
    int direction = st[i] > 0;
    int cnt = mabs(st[i]);
    if (i + 1 < st.size()) {
      cnt -= mabs(st[i + 1]);
    }

    //cout << " DIRECTION " << direction << " CNT " << cnt << endl;
    for (int j = 0; j < cnt; ++j) {
      if (direction == 1) {
        res.push_back(sorted_deq.back());
        sorted_deq.pop_back();
      } else {
        res.push_back(sorted_deq.front());
        sorted_deq.pop_front();
      }
    }
  }

  reverse(res.begin(), res.end());

  for (int i = mabs(st[0]); i < n; ++i) {
    res.push_back(a[i]);
  }

  for (int i = 0; i < res.size(); ++i) {
    printf("%d ", res[i]);
  }
  printf("\n");
  return 0;
}
