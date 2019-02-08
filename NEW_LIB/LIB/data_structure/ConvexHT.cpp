#include<bits/stdc++.h>
using namespace std;


typedef long long ll;

template <typename T,T INF,bool isMin>
struct ConvexHullTrick {
  using P = pair<T, T>;
  deque<P> L;
 
  inline T getY(const P &a,const T &x){
    return a.first*x+a.second; 
  }
 
  inline bool check(const P &a,const P &b,const P &c){
    return (b.first-a.first)*(c.second-b.second)
      >= (b.second-a.second)*(c.first-b.first);
  }
  
  void add(T a,T b){
    if(!isMin) a*=-1,b*=-1;
    P line(a,b);
    if(!L.empty()&&L.back().first==a){
      line.second=min(line.second,L.back().second);
      L.pop_back();
    }
    while(L.size()>=2&&check(L[L.size()-2],L[L.size()-1],line)) L.pop_back();
    L.emplace_back(line);    
  }
 
  T get(T x){
    if(L.empty()) return isMin?INF:-INF;
    ll low=-1,high=L.size()-1;
    while(low+1<high){
      ll mid=(low+high)>>1;
      if(getY(L[mid],x)>=getY(L[mid+1],x)) low=mid;
      else high=mid;
    }
    return (!isMin?-1:1)*getY(L[high],x);
  }
};
 
ll n,c;
ll h[200009];
ll dp[200009];

signed main(){
  cin>>n>>c;
  for(int i=0;i<n;i++) cin>>h[i];
  ConvexHullTrick< ll , (ll)1e18 ,true > C;

  for(int i=1;i<n;i++){
    C.add(-2*h[i-1],dp[i-1]+h[i-1]*h[i-1]);
    dp[i]=C.get(h[i])+h[i]*h[i]+c;
  }

  cout<<dp[n-1]<<endl;
}
