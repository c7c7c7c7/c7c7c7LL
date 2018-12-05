#include <bits/stdc++.h>
#define re(i,n) for(int i=0;i<n;i++)
using namespace std;

struct UnionFind{
  int n;
  vector<int> r,p;
  UnionFind(){}
  UnionFind(int sz):n(sz),r(sz,1),p(sz,0){iota(p.begin(),p.end(),0);}
  int find(int x){
    return (x==p[x]?x:p[x]=find(p[x]));
  }
  bool same(int x,int y){
    return find(x)==find(y);
  }
  void unite(int x,int y){
    x=find(x);y=find(y);
    if(x==y) return;
    r[x]+=r[y];
    p[y]=x;
  }
};

template<typename T, typename E>
struct SkewHeap{
  using G = function<T(T,E)>;
  using H = function<E(E,E)>;
  using C = function<bool(T,T)>;
  G g;
  H h;
  C c;
  T INF;
  E ei;
  SkewHeap(G g,H h,C c,T INF,E ei):g(g),h(h),c(c),INF(INF),ei(ei){}
  
  struct Node{
    Node *l,*r;
    T val;
    E add;
    Node(T val,E add):val(val),add(add){l=r=nullptr;}
  };

  void eval(Node *a){
    if(a==nullptr) return;
    if(a->add==ei) return;
    if(a->l) a->l->add=h(a->l->add,a->add);
    if(a->r) a->r->add=h(a->r->add,a->add);
    a->val=g(a->val,a->add);
    a->add=ei;
  }
  
  T top(Node *a){
    return a!=nullptr?g(a->val,a->add):INF;
  }

  T snd(Node *a){
    eval(a);
    return a!=nullptr?min(top(a->l),top(a->r)):INF;
  }

  Node* add(Node *a,E d){
    if(a!=nullptr) a->add=h(a->add,d);
    return a;
  }
  
  Node* push(T v){
    return new Node(v,ei);
  }
  
  Node* meld(Node *a,Node *b){
    using V = tuple<Node*, Node*>;
    stack<V> st;
    Node* res;
  ENTRYPOINT:
    if(!a||!b) res=a?a:b;
    else{
      if(c(top(a),top(b))) swap(a,b);
      eval(a);
      st.emplace(a,b);
      a=a->r;
      goto ENTRYPOINT;
    RETURNPOINT:
      tie(a,b)=st.top();st.pop();
      a->r=res;
      swap(a->l,a->r);
      res=a;
    }
    if(!st.empty()) goto RETURNPOINT;
    return res;
  }
  
  Node* pop(Node* a){
    eval(a);
    auto res=meld(a->l,a->r);
    delete a;
    return res;
  }
  
};

//INSERT ABOVE HERE
template<typename T>
struct Arborescence{
  typedef pair<T, int> P;
  using Heap = SkewHeap<P, T>;
  
  struct edge{
    int from,to;
    T cost;
    edge(){}
    edge(int from,int to,T cost):from(from),to(to),cost(cost){}
  };
  
  int n;
  P INF;
  UnionFind uf;
  vector<edge> edges;
  vector<typename Heap::Node*> come;
  vector<int> used,from;
  vector<T> cost;
  
  Arborescence(int n,T INF):n(n),INF(INF,-1),uf(n),come(n,NULL),
                used(n,0),from(n,-1),cost(n,-1){};

  void add_edge(int from,int to,T cost){
    edges.emplace_back(from,to,cost);
  }

  void input(int m,int offset=0){
    for(int i=0;i<m;i++){
      int u,v;
      T c;
      cin>>u>>v>>c;
      add_edge(u+offset,v+offset,c);
    }
  }

  T build(int r){
    typename Heap::G g=[](P a,T b){return P(a.first+b,a.second);};
    typename Heap::H h=[](T a,T b){return a+b;};
    typename Heap::C c=[](P a,P b){return a>b;};
    Heap heap(g,h,c,INF,0);
  
    used[r]=2;
    for(int i=0;i<(int)edges.size();i++){
      edge &e=edges[i];
      come[e.to]=heap.meld(come[e.to],heap.push(P(e.cost,i)));
    }
    
    T res=0;
    for(int i=0;i<n;i++){
      if(used[i]) continue;
      int v=i;
      vector<int> l;
      while(used[v]!=2){
    used[v]=1;
    l.emplace_back(v);
    if(!come[v]) return T(-1);
    from[v]=uf.find(edges[come[v]->val.second].from);
    cost[v]=heap.top(come[v]).first;
    come[v]=heap.pop(come[v]);
    if(from[v]==v) continue;
    
    res+=cost[v];
    if(used[from[v]]==1){
      int p=v;
      do{
        if(come[p]!=nullptr) heap.add(come[p],-cost[p]);
        if(p!=v){
          uf.unite(v,p);
          come[v]=heap.meld(come[v],come[p]);
        }
        p=uf.find(from[p]);
      }while(p!=v);
    }else{
      v=from[v];
    }
      }
      for(int u:l) used[u]=2;
    }
    return res;
  }
};

int n,m;
double v[111][111];
double cost[111][111];
signed main(){
  cin>>n>>m;
  Arborescence<double> G(m+1,1e14);
  re(i,m)re(j,n)cin>>v[i][j];
  re(j,n)v[m][j]=0;
  re(i,m)re(j,m){
    if(i==j)continue;
    double L=-1000,R=1000;
    re(k,50){
      double mid=(L+R)/2;
      double s1=0,s2=0;
      re(l,n)s1+=abs(v[j][l]-mid*v[i][l])*abs(v[j][l]-mid*v[i][l]);
      re(l,n)s2+=abs(v[j][l]-(mid+1e-6)*v[i][l])*abs(v[j][l]-(mid+1e-6)*v[i][l]);
      if(s1>s2)L=mid;
      else R=mid;
    }
    double sum=0;
    re(l,n)sum+=abs(v[j][l]-L*v[i][l])*abs(v[j][l]-L*v[i][l]);
    G.add_edge(i,j,sum);
  }
  re(i,m){
    double sum=0;
    re(l,n)sum+=v[i][l]*v[i][l];
    G.add_edge(m,i,sum);
  }
  printf("%.9f\n", G.build(m));
}