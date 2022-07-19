#include <iostream>
#include <set>
#include <cmath>
#include <algorithm>

// Copied from
// https://codeforces.com/contest/1635/submission/147249838

using namespace std;
const int mo=1e9+7;
int n,p,x[200005],dp[200005],ans;
set<int> st;
int main()
{
	scanf("%d%d",&n,&p);
	for(int a=1;a<=n;a++) scanf("%d",&x[a]);
	sort(x+1,x+1+n);
	for(int a=1;a<=n;a++)
	{
		int l=log2(x[a]),xx=x[a];
		bool u=1;
		while(x[a]>0)
		{
			if(st.count(x[a])>0) u=0;
			if(x[a]%2==1) x[a]/=2;
			else if(x[a]%4==0) x[a]/=4;
			else break;
		}
		if(u==1) dp[l]++;
		st.insert(xx);
	}
	for(int a=0;a<p;a++)
	{
		dp[a+1]=(dp[a]+dp[a+1])%mo;
		dp[a+2]=(dp[a]+dp[a+2])%mo;
		ans=(ans+dp[a])%mo;
	}
	printf("%d\n",ans);
}
