#include <bits/stdc++.h>
using namespace std;


typedef long long ll;
const ll M = 1000000007;

ll extgcd(ll a,ll b,ll& x,ll& y){
  ll d = a ;
  if ( b != 0 ) {
    d = extgcd( b , a%b , y , x ) ;
    y -= ( a / b ) * x ;
  }else{
    x = 1 ; y = 0 ;
  }
  return d;
}
ll mod_inverse(ll a,ll m){
  ll x , y ;
  extgcd( a , m , x , y ) ;
  return ( m + x % m ) % m ;
}

ll combination(ll N,ll K){
  ll res = 1;
  for( int i = 0; i < K; i++ ) res = (res * ((N - i) % M )) % M;
  for( int i = 1; i <= K; i++ ) res = (res * mod_inverse(i,M)) % M;
  return res;
}

int main(){
  ll a,b;
  cin>>a>>b;
  cout<<combination(a+b-2,a-1)<<endl;
}