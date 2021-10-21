#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <set>
#include <map>
using namespace std;
#define For(Ti,Ta,Tb) for(int Ti=(Ta);Ti<=(Tb);++Ti)
#define Dec(Ti,Ta,Tb) for(int Ti=(Ta);Ti>=(Tb);--Ti)
template<typename T> void Read(T &_x){
	_x=0;int _f=1;
	char ch=getchar();
	while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();
	while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();
	_x*=_f;
}
template<typename T,typename... Args> void Read(T &_x,Args& ...others){
	Read(_x);Read(others...);
}
typedef long long ll;
const int N=65,Mod=1e9+7;
struct Value{
	int col;
	ll val[8];
	Value(int c):col(c){}
	Value(const Value&)=default;
	Value()=default;
};
int k,n;ll f[N][8];
const set<int> ban[8]{{},{1,2},{1,2},{3,4},{3,4},{5,6},{5,6}};
map<ll,Value,greater<ll>> sp;
ll F(ll x,int c){
	if(x>=1LL<<k) return 0;
	if(sp.count(x)) return sp[x].val[c];
	int hb=0;
	while(x<1LL<<k) ++hb,x=x*2+1;
	return f[hb][c];
}
map<char,int> mp{{'w',1},{'y',2},{'g',3},{'b',4},{'r',5},{'o',6}};
int main(){
	Read(k);
	For(j,1,6) f[1][j]=1;
	For(i,2,k){
		For(j,1,6){
			ll cnt=0;
			For(pre,1,6){
				if(!ban[j].count(pre)) cnt=(cnt+f[i-1][pre])%Mod;
			}
			f[i][j]=cnt*cnt%Mod;
		}
	}
	Read(n);
	For(i,1,n){
		ll x;char temp[20];
		scanf("%lld%s",&x,temp);
		sp[x]=Value(mp[temp[0]]);
	}
	auto spe=sp;
	for(const auto &x:spe){
		ll u=x.first;
		while(u){
			if(!sp.count(u)) sp[u]=Value(0);
			u>>=1;
		}
	}
	for(auto it=sp.begin();it!=sp.end();++it){
//		printf("%lld\n",it->first);
		For(j,1,6){
			if(it->second.col&&j!=it->second.col){
				it->second.val[j]=0;continue;
			}
			ll cnt1=0,cnt2=0;
			For(pre,1,6){
				if(!ban[j].count(pre)){
					cnt1=(cnt1+F(it->first*2,pre))%Mod;
					cnt2=(cnt2+F(it->first*2+1,pre))%Mod;
				}
			}
			it->second.val[j]=cnt1*cnt2%Mod;
			if(it->first*2>=1LL<<k) it->second.val[j]=1;
//			printf("%lld %d:%lld\n",it->first,j,it->second.val[j]);
		}
	}
	ll ans=0;
	For(i,1,6) ans=(ans+F(1,i))%Mod;
	printf("%lld\n",ans);
	return 0;
}

