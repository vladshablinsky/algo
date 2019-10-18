#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

long long get_m_factor(int idx, int k) {
  if (idx == 1) {
    return 0ll;
  }
  if (idx == k || idx + 1 == k) {
    return 1ll;
  } else {
    return 1ll << (k - 1 - idx);
  }
}

void query() {
  long long a, b, m;
  vector<long long> ms;  // m's starting from second since first one is 0
  cin >> a >> b >> m;
  if (a == b) {
    cout << 1 << " " << a << "\n";
    return;
  }

  long long cur_mn = a;
  ms.push_back(0ll);
  for (int i = 2; i <= 50; ++i) {
    cur_mn = a << (i - 2);
    if (cur_mn > b) {
      break;
    }

    for (int j = 1; j < ms.size(); ++j) {
      ms[j] = 1ll;
    }
    ms.push_back(1ll);

    long long value_to_get = b - cur_mn - (1ll << (i - 2));

    // cout << "i is " << i << endl;
    // cout << "cur_mn is " << cur_mn << endl;
    // cout << "value_to_get is " << value_to_get << endl;


    if (value_to_get < 0) {
      break;
    }

    int cur_idx = 2;
    while (cur_idx <= i && value_to_get > 0) {
      long long factor = get_m_factor(cur_idx, i);
      //cout << "factor for " << cur_idx << " is " << factor << endl;
      long long m_idx_to_add = min(m - 1, value_to_get / factor);
      //cout << "m_idx_to_add is " << m_idx_to_add << endl;
      value_to_get -= factor * m_idx_to_add;
      ms[cur_idx - 1] += m_idx_to_add;
      ++cur_idx;
    }

    if (value_to_get == 0) {
      long long cur_num = a;
      long long prev_sum = 0;
      cout << i << " ";
      for (auto &el: ms) {
        cur_num += el;
        cout << cur_num << " ";
        prev_sum += cur_num;
        cur_num = prev_sum;
      }
      cout << "\n";
      return;
    }
  }
  cout << "-1\n";
  return;
}

int main() {
  int q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    query();
  }

  return 0;
}
