#include <iostream>
#include <cstdio>

using namespace std;
int n,r;
char s[200001],t[]="RGB";
int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output2.txt", "w", stdout);
 cin>>n>>s;
  for(int i=1;i<n;i++)
    if(s[i]==s[i-1])
    { r++;
      for(int j=0;j<3;j++)
        if(t[j]!=s[i-1] && t[j]!=s[i+1])
           s[i]=t[j];
    }
  cout<<r<<'\n';//<<s;
  return 0;
}
