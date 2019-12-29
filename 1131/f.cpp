#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 150005;

struct node {
  node *next;
  node *prev;
  int val;
  node(int val): val(val), next(nullptr), prev(nullptr) {}
};

node *last_in_group[MAXN];
node *first_in_group[MAXN];

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n - 1; ++i) {
    int x, y;
    cin >> x >> y;
    cout << "BEFORE\n";
    if (first_in_group[x]) cout << "first_in_group[" << x << "] is " << first_in_group[x]->val << endl;
    if (last_in_group[x]) cout << "last_in_group[" << x << "] is " << last_in_group[x]->val << endl;
    if (first_in_group[y]) cout << "first_in_group[" << y << "] is " << first_in_group[y]->val << endl;
    if (last_in_group[y]) cout << "last_in_group[" << y << "] is " << last_in_group[y]->val << endl;

    if (!last_in_group[x] && !last_in_group[y]) {
      node *a = new node(x);
      node *b = new node(y);
      a->next = b;
      b->prev = a;
      last_in_group[x] = b;
      last_in_group[y] = b;
      first_in_group[x] = a;
      first_in_group[y] = a;
    } else if (!last_in_group[x] || !last_in_group[y]) {
      int new_val = x;
      int exs_val = y;
      if (last_in_group[x]) {
        swap(new_val, exs_val);
      }

      node *b = new node(new_val);
      cout << "add new node\n";
      last_in_group[exs_val]->next = b;
      b->prev = last_in_group[exs_val];
      last_in_group[exs_val] = last_in_group[new_val] = b;
      first_in_group[new_val] = first_in_group[exs_val];
    } else {
      last_in_group[x]->next = first_in_group[y];
      first_in_group[y]->prev = last_in_group[x];
      last_in_group[x] = last_in_group[y];
      first_in_group[y] = first_in_group[x];
    }
    cout << "AFTER\n";
    cout << "first_in_group[" << x << "] is " << first_in_group[x]->val << endl;
    cout << "last_in_group[" << x << "] is " << last_in_group[x]->val << endl;
    cout << "first_in_group[" << y << "] is " << first_in_group[y]->val << endl;
    cout << "last_in_group[" << y << "] is " << last_in_group[y]->val << endl;
    cout << "end\n";
  }

  node *cur_node = first_in_group[1];
  while (cur_node) {
    cout << cur_node->val << " ";
    cur_node = cur_node->next;
  }
  cout << "\n";
  return 0;
}
