#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
const ll mod=998244353;
typedef std::pair<ll,ll> P;
const int N=22,M=1<<10;
P dp[N][M];int a[N],top,cnt[M],k;ll l,r,ten[N];
bool vis[N][M];
P dfs(int p,int sta,bool zero,bool lim) {
    if(p<0) return cnt[sta]<=k&&!zero?P(0,1):P(0,0);
    if(!zero&&!lim&&vis[p][sta]) return dp[p][sta];
    P ans(0,0);int up=lim?a[p]:9;
    for(int i=0;i<=up;i++) {
        P c=dfs(p-1,zero&&!i?0:(sta|1<<i),zero&&!i,lim&&i==up);
        ans.second+=c.second;
        ans.first+=c.first;
        ans.first+=c.second*i*ten[p]%mod;
        ans.first%=mod;ans.second%=mod;
    }
    if(!zero&&!lim) vis[p][sta]=1,dp[p][sta]=ans;
    return ans;
}
ll solve(ll x) {
    if(!x) return 0;
    top=0;while(x) a[top++]=x%10,x/=10;
    ll res= dfs(top-1,0,1,1).first;
    cout << res << endl;
    return res;
}
int main() {
    ten[0]=1;for(int i=1;i<N;i++) ten[i]=ten[i-1]*10%mod;
    for(int i=0;i<1<<10;i++) for(int j=i;j;j-=j&-j) cnt[i]++;
    scanf("%lld%lld%d",&l,&r,&k);
    printf("%lld\n",(solve(r)-solve(l-1)+mod)%mod);
    return 0;
}
