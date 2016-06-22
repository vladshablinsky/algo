#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <string>

using namespace std;

map<int, set<pair<int, string>>> mp;

int main() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    string name;
    int region, score;
    cin >> name >> region >> score;
    mp[region].insert(make_pair(-score, name));
  }

  for (int i = 1; i <= m; ++i) {
    vector<pair<int, string> > guys;
    int j = 0;
    for (auto it = mp[i].begin(); it != mp[i].end() && j < 3; ++it, ++j) {
      guys.push_back(*it);
    }
    if (guys.size() == 3 && guys[1].first == guys[2].first) {
      printf("?\n");
    } else {
      cout << guys[0].second << " " << guys[1].second << "\n";
    }
  }

  return 0;
}
