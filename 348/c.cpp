#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cstdlib>

using namespace std;

const int MAXN = 105;

vector<int> rows[MAXN];
vector<int> cols[MAXN];
vector<int> queries[MAXN * MAXN];

int n, m, q;

void init() {
  //cout << "IN INIT\n";
  for (int i = 0; i < n; ++i) {
    vector<int> v(m);
    rows[i] = v;
  }
  for (int j = 0; j < m; ++j) {
    vector<int> v(n);
    cols[j] = v;
  }
}

void print_matrix() {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      printf("%d ", rows[i][j]);
    }
    printf("\n");
  }
}

void cyclic_row(int row) {
  //cout << "IN CYCLIC ROW " << row << endl;
  rotate(rows[row].rbegin(), rows[row].rbegin() + 1, rows[row].rend());
  //cout << "AFTER ROTATE\n";
  for (int j = 0; j < m; ++j) {
    cols[j][row] = rows[row][j];
  }
}

void cyclic_col(int col) {
  // cout << "IN CYCLIC COL " << col << endl;
  rotate(cols[col].rbegin(), cols[col].rbegin() + 1, cols[col].rend());
  // cout << "AFTER ROTATE\n";
  for (int i = 0; i < n; ++i) {
    rows[i][col] = cols[col][i];
  }
}

int main() {
  scanf("%d%d%d", &n, &m, &q);
  init();

  for (int i = 0; i < q; ++i) {
    int t;
    scanf("%d", &t);
    queries[i].push_back(t);
    if (t == 1 || t == 2) {
      int rc;
      scanf("%d", &rc);
      queries[i].push_back(rc - 1);
    } else {
      int r, c, val;
      scanf("%d%d%d", &r, &c, &val);
      queries[i].push_back(r - 1);
      queries[i].push_back(c - 1);
      queries[i].push_back(val);
    }
  }

  for (int i = q - 1; i >= 0; --i) {
    //cout << "i = " << i << endl;
    if (queries[i][0] == 1) {
      //cout << "1==================\n";
      cyclic_row(queries[i][1]);
      //print_matrix();
    } else if (queries[i][0] == 2) {
      //cout << "2==================\n";
      cyclic_col(queries[i][1]);
      //print_matrix();
    } else {
      //cout << "3==================\n";
      int row = queries[i][1];
      int col = queries[i][2];
      int val = queries[i][3];
      rows[row][col] = val;
      cols[col][row] = val;
      //print_matrix();
    }
  }
  print_matrix();

  return 0;
}
