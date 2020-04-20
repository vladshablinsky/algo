#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 200005;
int id_to_pos[MAXN];

int main() {
  int q;
  cin >> q;

  int left_pos = 0; // free left pos
  int right_pos = 1; // free right pos
  for (int i = 0; i < q; ++i) {
    char q_type;
    int id;
    cin >> q_type >> id;

    if (q_type == 'L') {
      id_to_pos[id] = left_pos--;
    } else if (q_type == 'R') {
      id_to_pos[id] = right_pos++;
    } else {
      int pos = id_to_pos[id];
      cout << min(pos - left_pos, right_pos - pos) - 1 << "\n";
    }
  }

  return 0;
}

