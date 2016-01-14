#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

const int base = 1000000000;

int is_pretty(string &s) {
  for (int i = 1; i < s.length(); ++i) {
    if (s[i] != '0') {
      return -2;
    }
  }
  if (s[0] == '1') {
    return s.length() - 1;
  }
  if (s[0] == '0') {
    return -1;
  }
  return -2;
}

vector<int> to_big(string s) {
  vector<int> a;
  for (int i=(int)s.length(); i>0; i-=9)
    if (i < 9)
      a.push_back (atoi (s.substr (0, i).c_str()));
    else
      a.push_back (atoi (s.substr (i-9, 9).c_str()));

  return a;
}

vector<int> multiply_big(vector<int> a, vector<int> b) {
  vector<int> c (a.size()+b.size());
  for (size_t i=0; i<a.size(); ++i)
    for (int j=0, carry=0; j<(int)b.size() || carry; ++j) {
      long long cur = c[i+j] + a[i] * 1ll * (j < (int)b.size() ? b[j] : 0) + carry;
      c[i+j] = int (cur % base);
      carry = int (cur / base);
    }
  while (c.size() > 1 && c.back() == 0)
    c.pop_back(); int carry = 0;
  return c;
}

void print_big(vector<int> a) {
  printf ("%d", a.empty() ? 0 : a.back());
  for (int i=(int)a.size()-2; i>=0; --i)
    printf ("%09d", a[i]);
}

int main() {
  int n;
  string not_p = "";
  cin >> n;
  int summary = 0;

  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    int t = is_pretty(s);
    if (t == -1) {
      cout << "0\n";
      return 0;
    } else if (t == -2) {
      not_p = s;
    } else {
      summary += t;
    }
  }

  string p = "";
  p += "1";
  for (int i = 0; i < summary; ++i) {
    p += "0";
  }

  vector<int> a = to_big(p);
  vector<int> b = to_big(not_p);

  if (not_p == "") {
    print_big(a);
  } else {
    print_big(multiply_big(a,b));
  }

  cout << "\n";

  return 0;
}
