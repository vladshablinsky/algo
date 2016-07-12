#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <deque>

using namespace std;

const int MAX_N = 5e5 + 25;

int bro_to_the_right[MAX_N];
int bro_to_the_left[MAX_N];
int next_to_l[MAX_N];
int next_to_r[MAX_N];
string s;
string ops;

int main() {
  int n, m, p;
  scanf("%d%d%d", &n, &m, &p);
  cin >> s;
  cin >> ops;

  vector<int> v;

  for (int i = 0; i < s.length(); ++i) {
    if (s[i] == ')') {
      bro_to_the_left[i] = v.back();
      bro_to_the_right[v.back()] = i;
      v.pop_back();
    } else {
      v.push_back(i);
    }
  }

  //for (int i = 0; i < n; ++i) {
    //cout << bro_to_the_left[i] << " ";
  //}
  //cout << endl;
  //for (int i = 0; i < n; ++i) {
    //cout << bro_to_the_right[i] << " ";
  //}
  //cout << endl;

  for (int i = 0; i < n; ++i) {
    next_to_l[i] = i - 1;
    next_to_r[i] = i + 1;
  }

  int cur_pos = p - 1;
  for (int i = 0; i < ops.length(); ++i) {
    switch (ops[i]) {
      case 'L':
        cur_pos = next_to_l[cur_pos];
        break;
      case 'R':
        cur_pos = next_to_r[cur_pos];
        break;
      case 'D':
        if (s[cur_pos] == '(') {
          next_to_l[next_to_r[bro_to_the_right[cur_pos]]] = next_to_l[cur_pos];
          next_to_r[next_to_l[cur_pos]] = next_to_r[bro_to_the_right[cur_pos]];
          if (next_to_r[bro_to_the_right[cur_pos]] < n) {
            cur_pos = next_to_r[bro_to_the_right[cur_pos]];
          } else {
            cur_pos = next_to_l[cur_pos];
          }
        } else {
          next_to_l[next_to_r[cur_pos]] = next_to_l[bro_to_the_left[cur_pos]];
          next_to_r[next_to_l[bro_to_the_left[cur_pos]]] = next_to_r[cur_pos];
          if (next_to_r[cur_pos] < n) {
            cur_pos = next_to_r[cur_pos];
          } else {
            cur_pos = next_to_l[bro_to_the_left[cur_pos]];
          }
        }
        break;
    }
    //cout << "AFTER OPERATION " << ops[i] << endl;
    //cout << s << endl;
    //for (int j = 0; j < cur_pos; ++j) {
      //cout << " ";
    //}
    //cout << "^\n";
    //cout << "on pos " << cur_pos << endl;
    //cout << "to the left is " << next_to_l[cur_pos] << endl;
    //cout << "to the right is " << next_to_r[cur_pos] << endl;
  }

  deque<char> res;
  res.push_back(s[cur_pos]);
  for (int i = next_to_r[cur_pos]; i < n; i = next_to_r[i]) {
    res.push_back(s[i]);
  }
  for (int i = next_to_l[cur_pos]; i >= 0; i = next_to_l[i]) {
    res.push_front(s[i]);
  }

  for (auto it = res.begin(); it != res.end(); ++it) {
    cout << *it;
  }
  cout << "\n";
  return 0;
}
