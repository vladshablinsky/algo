#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

const int maxn=200007;
int n,q,a[maxn],b[maxn],c[maxn],t[maxn],sum[maxn];
int st1[maxn],st2[maxn],p1,p2,r1,r2,s1,s2;
int ans1[maxn][4],ans2[maxn][4];
set<int> s;

bool cmp1(int u,int v){
    return a[u]<a[v];
}

bool cmp2(int u,int v){
    return a[u]>a[v];
}

void print_s() {
  cout << "s1: [";
  for (int i = 1; i <= p1; ++i) {
    cout << a[st1[i]] << ", ";
  }
  cout << "], s2: [";
  for (int i = 1; i <= p2; ++i) {
    cout << a[st2[i]] << ", ";
  }
  cout << "]\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin>>n>>q;
    for (int i=1;i<=n;++i){
        cin>>a[i];
    }
    p1=p2=r1=r2=0;
    s.insert(n+1);
    for (int i=n;i>0;--i){
        while (p1){
            int u=st1[p1];
            if (a[u]>a[i]){
              cout << "pop1\n";
                t[u]--;
                if (!t[u]) s.insert(u);
                p1--;
                r1=0;
            }
            else{
                break;
            }
        }
        while (p2){
            int u=st2[p2];
            if (a[u]<a[i]){
              cout << "pop2\n";
                t[u]--;
                if (!t[u]) s.insert(u);
                p2--;
                r2=0;
            }
            else{
                break;
            }
        }
        print_s();
        cout << "lb in s1 for " << a[i] << "is " << *lower_bound(st1+1,st1+p1+1,i,cmp1) << endl;
        cout << "lb in s2 for " << a[i] << "is " << *lower_bound(st2+1,st2+p2+1,i,cmp2) << endl;
        s1=lower_bound(st1+1,st1+p1+1,i,cmp1)-st1-1;
        s2=lower_bound(st2+1,st2+p2+1,i,cmp2)-st2-1;
        cout << "s1 is fuck " << s1 << " " << p1 << endl;
        cout << "s2 is fuck " << s2 << " " << p2 <<  endl;
        b[i]=i+max(r1,r2)+1;
        ans1[i][0]=i, ans1[i][1]=b[i]-1, ans1[i][2]=b[i];
        if (s1&&s2){
            c[i]=*s.lower_bound(max(st1[s1],st2[s2]));
            cout << "C[i] = " << c[i] << " i chto blyat?'\n";
            if (c[i]<=n){
                int u = lower_bound(st1+1,st1+p1+1,c[i],greater<int>())-st1;
                int v = lower_bound(st2+1,st2+p2+1,c[i],greater<int>())-st2;
                cout << "u: " << u << ", v: " << v << endl;
                ans2[i][0]=i, ans2[i][1]=min(st1[u],st2[v]), ans2[i][2]=max(st1[u],st2[v]), ans2[i][3]=c[i];
            }
        }
        else{
            c[i]=n+1;
        }
        st1[++p1]=i;
        st2[++p2]=i;
        r1++, r2++;
        t[i]+=2;
        if (i<n&&b[i]>b[i+1]){
            b[i]=b[i+1];
            for (int j=0;j<3;++j){
                ans1[i][j]=ans1[i+1][j];
            }
        }
        if (i<n&&c[i]>c[i+1]){
            c[i]=c[i+1];
            for (int j=0;j<4;++j){
                ans2[i][j]=ans2[i+1][j];
            }
        }
    }
    while (q--){
        int l,r;
        cin>>l>>r;
        if (r>=c[l]){
            cout<<"4\n";
            for (int j=0;j<4;++j){
                cout<<ans2[l][j]<<" ";
            }
            cout<<"\n";
        }
        else{
            if (r>=b[l]){
                cout<<"3\n";
                for (int j=0;j<3;++j){
                    cout<<ans1[l][j]<<" ";
                }
                cout<<"\n";
            }
            else{
                cout<<"0\n\n";
            }
        }
    }
    return 0;
}
