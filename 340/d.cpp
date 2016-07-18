#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

vector<pair<int, int> > v;

int main() {
  int x_1, y_1;
  int x_2, y_2;
  int x_3, y_3;
  cin >> x_1 >> y_1;
  cin >> x_2 >> y_2;
  cin >> x_3 >> y_3;
  v.push_back(make_pair(x_1, y_1));
  v.push_back(make_pair(x_2, y_2));
  v.push_back(make_pair(x_3, y_3));

  sort(v.begin(), v.end());

  if (v[0].first == v[1].first) {
    if (v[1].first == v[2].first) {
      cout << "1\n";
      return 0;
    }
    if (v[1].second <= v[2].second || v[0].second >= v[2].second) {
      cout << "2\n";
      return 0;
    } else {
      cout << "3\n";
      return 0;
    }
  }

  if (v[1].first == v[2].first) {
    if (v[2].second <= v[0].second || v[1].second >= v[0].second) {
      cout << "2\n";
      return 0;
    } else {
      cout << "3\n";
      return 0;
    }
  }

  for (int i = 0; i < 3; ++i) {
    swap(v[i].first, v[i].second);
  }

  sort(v.begin(), v.end());

  if (v[0].first == v[1].first) {
    if (v[1].first == v[2].first) {
      cout << "1\n";
      return 0;
    }
    if (v[1].second <= v[2].second || v[0].second >= v[2].second) {
      cout << "2\n";
      return 0;
    } else {
      cout << "3\n";
      return 0;
    }
  }

  if (v[1].first == v[2].first) {
    if (v[2].second <= v[0].second || v[1].second >= v[0].second) {
      cout << "2\n";
      return 0;
    } else {
      cout << "3\n";
      return 0;
    }
  }
  cout << "3\n";
  return 0;
}
