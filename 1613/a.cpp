#include <iostream>
#include <cstdio>

using namespace std;

string solve() {
  int a_zeros, b_zeros;
  string a;
  string b;
  cin >> a >> a_zeros;
  cin >> b >> b_zeros;

  while (a.length() < b.length() && a_zeros) {
    a.push_back('0');
    --a_zeros;
  }

  while (b.length() < a.length() && b_zeros) {
    b.push_back('0');
    --b_zeros;
  }

  if (a.length() < b.length()) {
    return "<";
  } else if (a.length() > b.length()) {
    return ">";
  } else { // length equal
    if (a == b && a_zeros == b_zeros) {
      return "=";
    } else if ((a < b && a_zeros == b_zeros) || (a_zeros < b_zeros)) {
      return "<";
    } else {
      return ">";
    }
  }
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    cout << solve() << "\n";
  }
}
