#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

const int MAXN = 2e5 + 5;
const int R = 0;
const int G = 1;
const int B = 2;

pair<int, int> ans_r[MAXN];
pair<int, int> ans_g[MAXN];
pair<int, int> ans_b[MAXN];


int main() {
  //freopen("input.txt", "r", stdin);
  //freopen("output1.txt", "w", stdout);

	//auto pfile = fopen("output_d.txt", "w");
  int n;
  cin >> n;
  string s;
  cin >> s;

  for (int i = 1; i <= n; ++i) {
    if (ans_g[i - 1].first < ans_b[i - 1].first) {
      ans_r[i] = {ans_g[i - 1].first + (s[i - 1] != 'R'), G};
    } else {
      ans_r[i] = {ans_b[i - 1].first + (s[i - 1] != 'R'), B};
    }

    if (ans_r[i - 1].first < ans_b[i - 1].first) {
      ans_g[i] = {ans_r[i - 1].first + (s[i - 1] != 'G'), R};
    } else {
      ans_g[i] = {ans_b[i - 1].first + (s[i - 1] != 'G'), B};
    }

    if (ans_r[i - 1].first < ans_g[i - 1].first) {
      ans_b[i] = {ans_r[i - 1].first + (s[i - 1] != 'B'), R};
    } else {
      ans_b[i] = {ans_g[i - 1].first + (s[i - 1] != 'B'), G};
    }

    //fprintf(pfile, "to %d end with R: %d, from %d\n",i, ans_r[i].first, ans_r[i].second);
    //fprintf(pfile, "to %d end with G: %d, from %d\n",i, ans_g[i].first, ans_g[i].second);
    //fprintf(pfile, "to %d end with B: %d, from %d\n",i, ans_b[i].first, ans_b[i].second);
    //fprintf(pfile, "==============\n");
  }
	//fclose(pfile);

  string ans_s = s;
  auto &ans = ans_r[n];
  ans_s.back() = 'R';
  if (ans_g[n].first < ans.first) {
    ans = ans_g[n];
    ans_s.back() = 'G';
  }
	if (ans_b[n].first < ans.first) {
    ans = ans_b[n];
    ans_s.back() = 'B';
  }

  cout << ans.first << "\n";
  for (int i = 0; i < n - 1; ++i) {
    if (ans.second == R) {
      ans_s[n - i - 2] = 'R';
      ans = ans_r[n - i - 1];
    } else if (ans.second == G) {
      ans_s[n - i - 2] = 'G';
      ans = ans_g[n - i - 1];
    } else {
      ans_s[n - i - 2] = 'B';
      ans = ans_b[n - i - 1];
    }
  }

  cout << ans_s << "\n";
  return 0;
}
