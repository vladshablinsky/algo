#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int main()
{
  int q;
  cin >> q;
  for (int i = 0; i < q; ++i) {
    int l, r, ans = 0;
    cin >> l >> r;
    if (!(l&1)) {ans+=l;l++;}
    if (r&1){ans-=r;r--;}
    ans+=(r-l+1)>>1;
    cout<<ans<<endl;
  }
  return 0;
}
