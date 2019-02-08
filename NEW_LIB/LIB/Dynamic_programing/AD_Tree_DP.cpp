#include <bits/stdc++.h>
#define r(i,n) for(int i=0;i<n;i++)
using namespace std;

#define int long long

vector<int>v[200009];
int dp[300003];
int ans[300003];
int n , mod=1000000007  , m ;

void dfs( int now , int pre ) {
  dp[now] = 0;
  r(i,v[now].size()){
    int nex = v[now][i];
    if( pre == nex )continue;
    dfs( nex , now );
    dp[now] = max( dp[now] , dp[nex] + 1 ) % mod;
  }
}

void dfs2( int now , int pre , int x ) {

  ans[now] = max( dp[now] , x) % mod;

  vector<int> l , r;
  int N = v[now].size() + 1;

  l.push_back( 0 );

  r( i , v[now].size() ){
    int nex = v[now][i];
    int w = nex==pre ? x : dp[nex]+1 ;
    l.push_back( w );
    r.push_back( w );
  }

  r.push_back( 0 );

  for( int i = 1 ; i < N ; i++ ){
    l[i] = max( l[i] , l[i-1] ) % mod;
  }

  for( int i = N-2 ; i >= 0 ; i-- ){
    r[i] = max( r[i] , r[i+1] );
  }

  for( int i = 0 ; i < v[now].size() ; i++ ){
    if( v[now][i] == pre )continue;
    dfs2( v[now][i] , now ,  max(l[i],r[i+1])+1 );
  }

}



signed main(){
  cin>>n;

  r(i,n-1){
    int a,b;
    cin>>a>>b;a--;b--;
    v[a].push_back(b);
    v[b].push_back(a);
  }

  dfs(0,0);
  dfs2(0,0,0);

  r(i,n) cout<<(n-1)*2-ans[i]<<endl;
}
/*
1,PM5~
4,AM all
*/
