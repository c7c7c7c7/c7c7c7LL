#include <bits/stdc++.h>
using namespace std;
struct Maximum_sum_circular{
  long long n;
  vector<long long>v;
  Maximum_sum_circular(int sz):n(sz),v(sz){}
  void Innput(){ for( int i=0 ; i<n ; i++ ) cin>>v[i]; }
  long long check(){
    long long ans = 0, sum = 0;
    for( int i=0 ; i<n ; i++ ){
      sum += v[i];
      sum = max( sum , 0LL );
      ans = max( ans , sum );
    }
    return ans;
  }
  long long solve(){
    for( int i=0 ; i<n ; i++ ) v[i] = -v[i];
    int tmp = check();
    for( int i=0 ; i<n ; i++ ) v[i] = -v[i];
    return max( check() , accumulate(v.begin(),v.end(),0LL)+tmp);
  }
};
int main(){
  int n;
  cin>>n;
  Maximum_sum_circular M(n);
  M.Innput();
  cout<<M.solve()<<endl;
}