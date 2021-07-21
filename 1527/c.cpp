#include <iostream>
#include <cstdio>

using namespace std;

const char* BOB = "BOB";
const char* ALICE = "ALICE";
const char* DRAW = "DRAW";

void solve() {
  int n;
  string s;
  cin >> n;
  cin >> s;

  bool is_central = (n % 2 == 1 && s[n / 2] == '0');
  int cnt_imbalanced = 0;
  int cnt_balanced = 0;

  for (int i = 0; i < n / 2; ++i) {
    if (s[i] != s[n - i - 1]) {
      cnt_imbalanced += (s[i] != s[n - i - 1]);
    } else {
      cnt_balanced += 2 * (s[i] == '0');
    }
  }

  int bobs_moves = 0;
  int alices_moves= 0;

  if (cnt_imbalanced) {
    alices_moves = (cnt_balanced > 0 || is_central);
    bobs_moves = cnt_imbalanced + is_central - alices_moves;
    bobs_moves += 2 * (cnt_balanced != 0);
  } else {
    alices_moves = !(is_central && cnt_balanced);
    bobs_moves = !alices_moves;
  }

  // cout << "result: ";
  // cout << bobs_moves << ", " << alices_moves << endl;

  if (bobs_moves == alices_moves) {
    cout << DRAW;
  } else if (alices_moves > bobs_moves) {
    cout << BOB;
  } else {
    cout << ALICE;
  }
  cout << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
