#include<bits/stdc++.h>
using namespace std;

struct CPP{

  struct Edge {
    int dst,weight;
  };

  int V,E;
  vector<int>s,t,d;

  CPP(int N,int M):V(N),E(M),s(M),t(M),d(M){}

  void Input(){
    for(int i=0;i<E;i++){
      cin>>s[i]>>t[i]>>d[i];
    }
  }

  int solve() {
    int mini = 0;
    vector<vector<Edge> > G(V);
    vector<vector<int> > wf(V,vector<int>(V,INT_MAX));
    for(int i=0;i<V;++i) wf[i][i] = 0;
    for(int i=0;i<E;++i) {
      G[s[i]].push_back((Edge){t[i],d[i]});
      G[t[i]].push_back((Edge){s[i],d[i]});
      wf[s[i]][t[i]] = wf[t[i]][s[i]] = min(wf[s[i]][t[i]],d[i]);
      mini += d[i];
    }
    for(int k=0;k<V;++k) for(int i=0;i<V;++i) for(int j=0;j<V;++j) if( wf[i][k] != INT_MAX && wf[k][j] != INT_MAX ) wf[i][j] = min(wf[i][j],wf[i][k]+wf[k][j]);
    vector<int> odd;
    for(int i=0;i<V;++i) if( (int)G[i].size() & 1 ) odd.push_back(i);
    int n = (int)odd.size();
    vector<int> dp((1<<n),INT_MAX);
    dp[0] = 0;
    for(int state=0;state<(1<<n);++state) {
      for(int sp=0;sp<n;++sp) if( !( (state>>sp) & 1 ) ) {
        for(int ep=0;ep<n;++ep) if( sp != ep && !( (state>>ep) & 1 ) )  {
            dp[state|(1<<sp)|(1<<ep)] = min(dp[state|(1<<sp)|(1<<ep)],dp[state]+wf[odd[sp]][odd[ep]]);
        }
      }
    }
    return mini + dp[(1<<n)-1];
  }
};
 
int main() {
  int V,E;
  cin>>V>>E;
  CPP C(V,E);
  C.Input();
  cout << C.solve() << endl;
}