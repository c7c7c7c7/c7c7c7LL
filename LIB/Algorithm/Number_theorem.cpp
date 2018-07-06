#include <bits/stdc++.h>
using namespace std;


typedef long long ll;
struct NT{
  ll m;  // mod
  vector<bool>ismrime;
  vector<ll> euler;
  vector<ll> fact;

  NT(ll MOD){
    m=MOD;
    fact.resize(500005);
    fact[0]=1;
    for(ll i=1;i<500005;i++){
      fact[i]=(fact[i-1]*i)%MOD;
    }
  }

  void eratos(int n){
    ismrime.resize(n+1);
    for(int i=0;i<=n;i++) ismrime[i]=true;
    ismrime[0]=0;
    ismrime[1]=0;
    for(int i=2;i<=n;i++){
      if(ismrime[i]){
        for(int j=i+i;j<=n;j+=i) ismrime[j]=false;
      }
    }
  }

  // 因数分解 √N
  vector<int> mrime_decommosition(ll x){
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

  // 約数列挙 √N
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
  ll mod_inverse(ll a){
    ll x , y ;
    extgcd( a , m , x , y ) ;
    return ( m + x % m ) % m ;
  }

  // オイラー関数√N
  ll euler_mhi(ll n){
    ll res = n;
    for(ll i=2; i*i <= n ; i++){
      if( n%i == 0 ){
        res = res/i*(i-1);
        for(;n%i==0;n/=i);
      }
    }
    if(n!=1)res=res/n*(n-1);
    return res;
  }

  void make_euler_table(int n){
    euler.resize(n+1);
    for(int i=0;i<n;i++) euler[i]=i;
    for(int i=2;i<n;i++){
      if(euler[i]==i){
        for(int j=i;j<n;j+=i){
          euler[j]=euler[j]/i*(i-1);
        }
      }
    }
  }

  // n! と nCr 
  // mはmod
  ll mod_fact(ll n,ll& e){
    e=0;
    if(n==0)return 1;

    int res = mod_fact(n/m,e);
    e+=n/m;

    if(n/m%2 != 0)return res*(m-fact[n%m])%m;
    return res*fact[n%m]%m;
  }

  ll combination(ll n,ll k){
    if(n==k||k==0)return 1;
    if(n<0 || k<0 || n<k)return 0;
    ll e1,e2,e3;
    ll a1 = mod_fact(n,e1);
    ll a2 = mod_fact(k,e2);
    ll a3 = mod_fact(n-k,e3);
    return a1*mod_inverse(a2*a3%m)%m;
  }

  ll stupid_combination(ll n,ll k){
    if(n==k||k==0)return 1;
    if(n<0 || k<0 || n<k)return 0;
    ll res=1;
    for(ll i=0;i<k;i++){
      res*=(n-i);
      res%=m;
      res*=mod_inverse(i+1);
      res%=m;
    }
    return res;
  }

  ll mod_mult(ll a, ll b,ll m) {
    ll res = 0;
    ll exm = a % m;
    while (b) {
      if (b & 1) {
        res += exm;
        if (res > m) res -= m;
      }
      exm <<= 1;
      if (exm > m) exm -= m;
      b >>= 1;
    }
    return res;
  }

  ll mod_exm(ll a, ll b,ll m) {
    ll res = 1;
    ll exm = a % m;
    while (b) {
      if (b & 1) res = mod_mult(res, exm,m);
      exm = mod_mult(exm, exm,m);
      b >>= 1;
    }
    return res;
  }

  // 確率的高速素数判定　
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
      ll x = mod_exm(a, q, n);
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

int main(){
  NT A(1000000007);
  cout<<A.combination(10,1)<<endl;

  while(1){
    ll a,b;
    cin>>a>>b;
    cout<<A.stupid_combination(a,b)<<endl;
  }
}
