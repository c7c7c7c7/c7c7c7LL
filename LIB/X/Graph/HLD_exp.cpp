#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> P;

struct RSQ{
  ll n=(1<<17),data[(1<<18)];
  RSQ(){
    memset(data,0,sizeof(data));
  }
  // 1 index
  /*void add(int i,int v){
    while(i<=n){
      data[i]+=v;
      i+=i&-i;
    }
  }*/
  // 0 index
  void add(int i,ll v){
    i+=1;
    while(i<=n){
      data[i]+=v;
      i+=i&-i;
    }
  }
  ll sum(int i){
    ll res=0;
    while(i>0){
      res+=data[i];
      i-=i&-i;
    }
    return res;
  }
  //[a,b) 1 index
  /*int sum(int x,int y){
    return sum(y-1)-sum(x-1);
  }*/
  //[a,b) 0 index
  int sum(int x,int y){
    x++;y++;
    return sum(y-1)-sum(x-1);
  }
};
 
struct HLD {
  int n,pos;
  vector<vector<int> > G;
  vector<int> vid, head, sub, hvy, par, dep, inv, type;
  RSQ rsq;

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
    if(rs.size()==0)rs.push_back(0);
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

  void update(int u,int w){
    rsq.add(vid[u],w);
  }

  void range_update(){
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
            Tree.update(x,w);
        }
        else{
            scanf("%d",&x);
            printf("%lld\n",Tree.for_each_edge(0,x));
        }
    }
}