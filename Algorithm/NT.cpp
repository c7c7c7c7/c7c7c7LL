#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int>P;

typedef long long ll;
struct NT{
  vector<bool>isprime;

  void eratos(int n){
    isprime.resize(n+1);
    for(int i=0;i<=n;i++) isprime[i]=true;
    isprime[0]=0;
    isprime[1]=0;
    for(int i=2;i<=n;i++){
      if(isprime[i]){
        for(int j=i+i;j<=n;j+=i) isprime[j]=false;
      }
    }
  }

  vector<int> prime_decomposition(ll x){
    vector<int>res;
    for(int i=2;i*i<=x;i++){
      while(x%i==0){
        x/=i;
        res.push_back(i);
      }
    }
    if(x!=1) res.push_back(x);
    return res;
  }

  vector<ll> divisor(ll x){
    vector<ll> res;
    for(ll i=1; i*i<=x ;i++)
      if(x%i==0){
        res.push_back(i);
        if(i*i!=x) res.push_back(x/i);
      }
    sort(res.begin(), res.end());
    return res;
  }

  // a*b>LONG_MAX ? 
  bool overflow(ll a,ll b,ll LONGMAX){return a > LONGMAX/b;}

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
  /*
  ll combination(ll N,ll K){
    ll res = 1;
    for( int i = 0; i < K; i++ ) res = (res * ((N - i) % M )) % M;
    for( int i = 1; i <= K; i++ ) res = (res * mod_inverse(i,M)) % M;
    return res;
  }*/

  ll mod_mult(ll a, ll b, ll m) {
    ll res = 0;
    ll exp = a % m;
    while (b) {
      if (b & 1) {
        res += exp;
        if (res > m) res -= m;
      }
      exp <<= 1;
      if (exp > m) exp -= m;
      b >>= 1;
    }
    return res;
  }

  ll mod_exp(ll a, ll b, ll m) {
    ll res = 1;
    ll exp = a % m;
    while (b) {
      if (b & 1) res = mod_mult(res, exp, m);
      exp = mod_mult(exp, exp, m);
      b >>= 1;
    }
    return res;
  }

  bool miller_rabin(ll n, ll times=10) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (!(n & 1)) return false;
    ll q = n-1;
    int k = 0;
    while (q % 2 == 0) {
      k++;
      q >>= 1;
    }
    for (int i = 0; i < times; i++) {
      ll a = rand() % (n-1) + 1;
      ll x = mod_exp(a, q, n);
      if (x == 1) continue;
      bool found = false;
      for (int j = 0; j < k; j++) {
        if (x == n-1) {
          found = true;
          break;
        }
        x = mod_mult(x, x, n);
      }
      if (found) continue;
      return false;
    }
    return true;
  }

  ll pollard_rho(ll n, int c) {
    ll x = 2;
    ll y = 2;
    ll d = 1;
    while (d == 1) {
      x = mod_mult(x, x, n) + c;
      y = mod_mult(y, y, n) + c;
      y = mod_mult(y, y, n) + c;
      d = __gcd((x-y >= 0 ? x-y : y-x), n);
    }
    if (d == n) return pollard_rho(n, c+1);
    return d;
  }
};
int s;
int main(){
  for(int i=1;i<1000;i++){
    if(i%3==0||i%5==0)s+=i;
  }
  cout<<s<<endl;
}
