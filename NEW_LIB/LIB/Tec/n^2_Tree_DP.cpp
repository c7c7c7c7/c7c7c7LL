#include <bits/stdc++.h>
#define r(i,n) for(int i=0;i<n;i++)
#define int long long
using namespace std;

int dp[3001][3001] , n , k;
int sz[3001];
vector<int> v[3001];

void dfs( int now , int pre ){
  dp[now][0] = 1;
  sz[now] = 1;
  r( o , v[now].size() ){
    int nex = v[now][o];
    if( nex == pre ) continue;
    dfs( nex , now );
    for( int i = sz[now]-1 ; i >= 0 ; i-- ){
      for( int j = 1 ; j <= sz[nex] ; j++ ){
        dp[now][i+j] += dp[nex][j] * dp[now][i];
        dp[now][i+j] %= 1000000007;
      }
    }
    sz[now] += sz[nex];
  }
  dp[now][sz[now]] = 1;
}

signed main(){
  cin >> n >> k;
  r( i , n-1 ){
    int a , b;
    cin >> a >> b;
    v[a].push_back(b);
    v[b].push_back(a);
  }
  dfs( 0 , -1 );
  cout << dp[0][k] << endl;
}

