#include<bits/stdc++.h>
#include<atcoder/dsu>

using namespace std;
using namespace atcoder;

int main(){
  int n,q;
  cin >> n >> q;
  dsu d(n+1);
  vector<int> c(n+1,0);
  vector<int> s(n+1,0);

  while(q--){
    int typ;
    cin >> typ;
    if(typ==1){
      int u,v;
      cin >> u >> v;
      u=d.leader(u);
      v=d.leader(v);
      if(u!=v){
        d.merge(u,v);
        int w=d.leader(u);
        s[w]=s[u]+s[v];
        s[u^v^w]=0;
      }
    }
    else if(typ==2){
      int u;
      cin >> u;
      s[d.leader(u)]-=c[u];
      c[u]^=1;
      s[d.leader(u)]+=c[u];
    }
    else{
      int u;
      cin >> u;
      if(s[d.leader(u)]){cout << "Yes\n";}
      else{cout << "No\n";}
    }
  }
  return 0;
}
