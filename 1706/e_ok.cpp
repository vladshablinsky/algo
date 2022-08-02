// Copied from https://codeforces.com/contest/1706/submission/164835737

#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;
const int N=2e5+10;
int a[N];
int T,n,m,q;
int lg[N],f[N][20];
int d[N],fa[N][20];
vector <int> e[N];
namespace dsu
{
	int fa[N];
	void init(){for(int i=1;i<=2*n;i++) fa[i]=i;}
	int get(int x){return x==fa[x]?x:fa[x]=get(fa[x]);}
}
void dfs(int x)
{
	for(int i=1;i<20;i++) fa[x][i]=fa[fa[x][i-1]][i-1];
	for(int i:e[x]) if(i!=fa[x][0]) fa[i][0]=x,d[i]=d[x]+1,dfs(i);
}
int LCA(int x,int y)
{
	if(d[x]<d[y]) swap(x,y);
	int t=d[x]-d[y];
	for(int i=0;i<20;i++) if(t&(1<<i)) x=fa[x][i];
	if(x==y) return x;
	for(int i=19;i>=0;i--) if(fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}
int calc(int l,int r)
{
	int k=lg[r-l+1];
	return LCA(f[l][k],f[r-(1<<k)+1][k]);
}
int main()
{
	for(int i=2;i<N;i++) lg[i]=lg[i/2]+1;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d%d",&n,&m,&q);
		dsu::init();int cnt=n;
		for(int i=1,x,y;i<=m;i++)
		{
			scanf("%d%d",&x,&y);
			int p=dsu::get(x),q=dsu::get(y);
			if(p==q) continue;
			a[++cnt]=i,dsu::fa[p]=dsu::fa[q]=cnt;
			e[cnt].push_back(p),e[cnt].push_back(q);
		}
		dfs(cnt);
		for(int i=1;i<n;i++) f[i][1]=LCA(i,i+1);
		for(int j=2;j<20;j++)
			for(int i=1;i<=n-(1<<j)+1;i++)
				f[i][j]=LCA(f[i][j-1],f[i+(1<<j-1)][j-1]);
		while(q--)
		{
			int l,r;scanf("%d%d",&l,&r);
			printf("%d ",a[calc(l,r)]);
		}
    printf("\n");
		for(int i=1;i<=cnt;i++) e[i].clear();
		for(int i=1;i<=cnt;i++) d[i]=fa[i][0]=0;
	}
	return 0;
}
