/*

   数列の最大長方形

*/



#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
struct LR{
  ll n;
  vector<ll>a;
  LR(int sz):n(sz),a(sz+1){}
  void Input(){
    for(int i=0;i<n;i++) cin>>a[i];
    a[n]=0;
  }
  ll solve(){
    ll ans=0,ls=0;
    stack<pair<ll,ll> >st;
    for(int j=0;j<n+1;j++){
      if(st.empty())st.push(make_pair(a[j],j));
      else if(st.top().first==a[j])continue;
      else if(st.top().first<a[j])st.push(make_pair(a[j],j));
      else{
        while(!st.empty()&&st.top().first>a[j]){
          ans=max(ans,(j-st.top().second)*st.top().first);
          ls=st.top().second;
          st.pop();
        }
        st.push(make_pair(a[j],ls));
      }
    }
    return ans;
  }
};
int main(){
  int n;
  cin>>n;
  LR L(n);
  L.Input();
  cout<<L.solve()<<endl;
}