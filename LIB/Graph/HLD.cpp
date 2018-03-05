#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> P;

struct RSAQ{
  struct BIT{
    int size;
    vector<ll> dat;
    BIT(){
      size=(1<<17);
      dat.clear();
      dat.resize((1<<17)+1);
    }
    void Add(int i,ll x){
      while(0<i&&i<=size){
        dat[i]+=x;
        i+=(i&-i);
      }
    }
    ll Sum(int i){
      ll res=0;
      while(0<i){
        res+=dat[i];
        i-=(i&-i);
      }
      return res;
    }
  };
  BIT A,B;
  // 0 index
  void add(int l,int r,ll v){
    l++;r++;
    A.Add(l,v);
    A.Add(r-1,-v);
    B.Add(l,-v*(l-1));
    B.Add(r-1,v*(l-1)+v*(r-l));
  }
  ll sum(int l,int r){
    return A.Sum(r)*r+B.Sum(r)-A.Sum(l)*l-B.Sum(l);
  }
};
 
struct HLD {
  int n,pos;
  vector<vector<int> > G;
  vector<int> vid, head, sub, hvy, par, dep, inv, type;
  RSAQ rsq;

  HLD(){}
  HLD(int sz):n(sz),pos(0),G(n),vid(n,-1),head(n),sub(n,1),hvy(n,-1),par(n),dep(n),inv(n),type(n){}
  
  void add_edge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
  }

  void build() {
    dfs(0);
    bfs(0, 0);
  }

  void build_2(vector<int> rs) {
    int c=0;
    for(int i=0;i<rs.size();i++){
        int r=rs[i];
      dfs(r);
      bfs(r, c++);
    }
  }
  
  void dfs(int rt) {
    stack<P> st;
    par[rt]=-1;
    dep[rt]=0;
    st.push(P(rt,0));
    while(!st.empty()){
        int v=st.top().first;
        int &i=st.top().second;
        if(i<(int)G[v].size()){
            int u=G[v][i++];
            if(u==par[v]) continue;
            par[u]=v;
            dep[u]=dep[v]+1;
            st.push(P(u,0));
        }else{
            st.pop();
            int res=0;
            for(int i=0;i<G[v].size();i++){
                int u=G[v][i];
                if(u==par[v]) continue;
                sub[v]+=sub[u];
                if(res<sub[u]) res=sub[u],hvy[v]=u;
            }
        }
    }
  }

  void bfs(int r,int c) {
    int &k=pos;
    queue<int> q;
    q.push(0);
    while(!q.empty()){
      int h=q.front();q.pop();
      for(int i=h;i!=-1;i=hvy[i]) {
        type[i]=c;
        vid[i]=k++;
        inv[vid[i]]=i;
        head[i]=h;
        for(int J=0;J<G[i].size();J++){
            int j=G[i][J];
            if(j!=par[i]&&j!=hvy[i]) q.push(j);
        }
      }
    }
  }
  
  // for_each(vertex)
  // [l,r] <- attention!!
  int for_each(int u, int v) {
    int ans=0;
    while(1){
      if(vid[u]>vid[v]) swap(u,v);
      //f(max(vid[head[v]],vid[u]),vid[v]);
      //ans = max(ans,rmq.query(l, r + 1));
      if(head[u]!=head[v]) v=par[head[v]];
      else {return ans;}
    }
  }
  
  // for_each(edge)
  // [l,r] <- attention!!
  ll for_each_edge(int u, int v) {
    ll ans=0;
    while(1){
      if(vid[u]>vid[v]) swap(u,v);
      if(head[u]!=head[v]){
        //f(vid[head[v]],vid[v]);
        ans += rsq.sum(vid[head[v]],vid[v]+1);
        v=par[head[v]];
      } else{
        //if(u!=v) f(vid[u]+1,vid[v]);
        if(u!=v) ans += rsq.sum(vid[u]+1,vid[v]+1);
        return ans;
      }
    }
  }

  /*void update_edge(int u,int w){
    rsq.add(vid[u],w);
  }*/

  void range_update_edge(int u,int v,int w){
    while(1){
      if(vid[u]>vid[v]) swap(u,v);
      if(head[u]!=head[v]){
        //f(vid[head[v]],vid[v]);
        rsq.add(vid[head[v]],vid[v]+1,w);
        v=par[head[v]];
      } else{
        //if(u!=v) f(vid[u]+1,vid[v]);
        rsq.add(vid[u]+1,vid[v]+1,w);
        break;
      }
    }
  }

  int lca(int u,int v){
    while(1){
      if(vid[u]>vid[v]) swap(u,v);
      if(head[u]==head[v]) return u;
      v=par[head[v]];
    }
  }

  int distance(int u,int v){
    return dep[u]+dep[v]-2*dep[lca(u,v)];
  }
};
int main(){
    int n,m,x,w;
    scanf("%d",&n);
    HLD Tree(n);
    for(int i=0;i<n;i++){
        scanf("%d",&m);
        for(int j=0;j<m;j++){
            scanf("%d",&x);
            Tree.add_edge(i,x);
        }
    }
    Tree.build();
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&m);
        if(m==0){
            scanf("%d%d",&x,&w);
            Tree.range_update_edge(0,x,w);
        }
        else{
            scanf("%d",&x);
            printf("%lld\n",Tree.for_each_edge(0,x));
        }
    }
}