#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

vector<int> v;

int mabs(int x) {
  if (x < 0) {
    return -x;
  }
  return x;
}

int main() {
  v.push_back(1);
  string s;
  getline(cin, s);
  int num = 0;
  int cur_sum = 1;
  for (int i = 0; i < s.length(); ++i) {
    if (s[i] == '+') {
      v.push_back(1);
      ++cur_sum;
    } else if (s[i] == '-') {
      v.push_back(-1);
      --cur_sum;
    }

    if (s[i] >= '0' && s[i] <= '9') {
      while(i != s.length()) {
        num = num * 10 + (s[i++] - '0');
      }
    }
  }

  int to_add = num - cur_sum;
  for (int i = 0; i < v.size(); ++i) {
    if (to_add == 0) {
      break;
    }
    if (v[i] < 0 && to_add < 0) {
      int cur_add = min(num - 1, -to_add);
      to_add += cur_add;
      v[i] -= cur_add;
    }
    if (v[i] > 0 && to_add > 0) {
      int cur_add = min(num - 1, to_add);
        to_add -= cur_add;
      v[i] += cur_add;
    }
  }

  if (to_add != 0) {
    printf("Impossible\n");
  } else {
    printf("Possible\n");
    for (int i = 0; i < v.size(); ++i) {
      if (v[i] > 0 && i != 0) {
        printf("+ ");
      } else if (i != 0) {
        printf("- ");
      }

      printf("%d ", mabs(v[i]));
    }
    printf("= %d\n", num);
  }

  return 0;
}
