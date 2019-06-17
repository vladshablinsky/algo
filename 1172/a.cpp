#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 200000 + 5;
const int NONE = -1;

int check_no_move(vector<bool> my_cards, vector<int>& pile, int start_number, int n) {
  int steps = 0;
  int pos = 0;
  for (int i = start_number; i <= n; ++i) {
    if (!my_cards[i]) {
      return NONE;
    } else {
      my_cards[pile[pos++]] = true;
      ++steps;
    }
  }
  return steps;
}

int check_move(vector<bool> my_cards, vector<int>& pile, int pos_one, int n) {
  // cout << "Checking move 2\n";
  int steps = 0;
  int pos = 0;

  if (pos_one != NONE) {
    while (pos <= pos_one) {
      my_cards[pile[pos++]] = true;
      ++steps;
    }
  }

  // cout << "pos is " << pos << endl;
  // cout << "steps is " << steps << endl;

  for (int cur_num = 1; cur_num <= n; ++cur_num) {
    if (!my_cards[cur_num]) {
      // cout << cur_num << " not on hands\n";
      while (!my_cards[cur_num]) {
        // cout << "take one more: " << pile[pos] << ", steps: " << steps + 1 << endl;
        my_cards[pile[pos++]] = true;
        ++steps;
      }
    }

    // cout << cur_num << " on hands, steps: " << steps + 1<< endl;
    my_cards[pile[min(pos++, n - 1)]] = true;
    ++steps;
  }
  return steps;
}

int main() {
  int n;
  vector<bool> my_cards;
  vector<int> pile;

  scanf("%d", &n);
  my_cards.resize(n + 1);
  pile.resize(n);

  for (int i = 0; i < n; ++i) {
    int t;
    scanf("%d", &t);
    my_cards[t] = true;
  }

  int pos_one = NONE;

  for (int i = 0; i < n; ++i) {
    scanf("%d", &pile[i]);
    if (pile[i] == 1) {
      pos_one = i;
    }
  }

  int steps = NONE;
  int pos = 0;

  if (pos_one != NONE) {
    int cur_pos = pos_one;
    while (cur_pos + 1 < n && pile[cur_pos] + 1 == pile[cur_pos + 1]) {
      ++cur_pos;
    }

    if (cur_pos == n - 1) {
      steps = check_no_move(my_cards, pile, 2 + cur_pos - pos_one, n);
    }
  }

  if (steps == NONE) {
    steps = check_move(my_cards, pile, pos_one, n);
  }

  cout << steps << "\n";

  return 0;
}
