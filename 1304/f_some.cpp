#include <iostream>
#include <cstdio>

using namespace std;
typedef long long ll;
const int N=2e4;

int a[80][N],d[80][N],l[80][N],r[80][N];

int main(){
  ios::sync_with_stdio(0);
  int n,m,k,ans=0;
  cin>>n>>m>>k;
  for(int i=0;i<n;i++)
    for(int j=1;j<=m;j++)cin>>a[i][j];
  for(int i=1;i<=n;i++){
    for(int j=k;j<=m;j++){
      int s=0;
      for(int c=j-k+1;c<=j;c++)s+=a[i][c];
      int t=s;
      d[i][j]=d[i-1][j]+s;
      for(int c=j;c>j-k;c--){
        s+=a[i-1][c];
        d[i][j]=max(d[i][j],s+l[i-1][c-1]);
      }
      for(int c=j-k+1;c<=j;c++){
        t+=a[i-1][c];
        d[i][j]=max(d[i][j],t+r[i-1][c+k]);
      }
    }
    for(int j=1;j<=m;j++)
      l[i][j]=max(l[i][j-1],d[i][j]);
    for(int j=m;j>0;j--)
      r[i][j]=max(r[i][j+1],d[i][j]);
    ans=max(ans,l[i][m]);
  }
  cout<<ans;
  return 0;
}
