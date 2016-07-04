#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;

int n;
string s;
set<char> st;

int main() {
  scanf("%d", &n);
  cin >> s;
  for (int i = 0; i < n; ++i) {
    st.insert(s[i]);
  }

  if (st.size() == n) {
    printf("0\n");
  } else if (n <= 26) {
    printf("%d\n", n - (int)st.size());
  } else {
    printf("-1\n");
  }
  return 0;
}
