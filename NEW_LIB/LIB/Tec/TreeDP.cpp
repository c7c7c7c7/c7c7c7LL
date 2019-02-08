#include <bits/stdc++.h>
#define r(i,n) for(int i=0;i<n;i++)
using namespace std;

#define int long long

vector<int>v[200009];
int dp[300003];
int ans[300003];
int n , mod  , m ;

void dfs( int now , int pre ) {
  dp[now] = 1;
  r(i,v[now].size()){
    int nex = v[now][i];
    if( pre == nex )continue;
    dfs( nex , now );
    dp[now] = ( dp[now] * (dp[nex]+1) ) % mod;
  }
}

void dfs2( int now , int pre , int x ) {
  ans[now] = ( dp[now] * x ) %mod;

  vector<int> l , r;
  l.push_back( 1 );
  r(i,v[now].size()){
    int nex = v[now][i];
    int w = nex==pre ? 1 : dp[nex]+1 ;
    l.push_back( w );
    r.push_back( w );
  }
  r.push_back( 1 );

  for( int i = 1 ; i < l.size() ; i++ ){
    l[i] = ( l[i] * l[i-1] ) % mod;
  }

  for( int i = r.size()-2 ; i >= 0 ; i-- ){
    r[i] = ( r[i] * r[i+1] ) % mod;
  }

  for( int i = 0 ; i < v[now].size() ; i++ ){
    if( v[now][i] == pre )continue;
    dfs2( v[now][i] , now , ( (x*(l[i]*r[i+1]%mod))%mod+1) %mod );
  }

}

signed main(){
  cin>>n>>mod;

  r(i,n-1){
    int a,b;
    cin>>a>>b;a--;b--;
    v[a].push_back(b);
    v[b].push_back(a);
  }

  dfs(0,0);
  dfs2(0,0,1);

  r(i,n) cout<<ans[i]<<endl;
}
