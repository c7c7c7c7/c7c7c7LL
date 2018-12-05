#include <bits/stdc++.h>
#define int long long
using namespace std;

int POW(int a,int b){
  int res=1;
  for(int i=0;i<60;i++){
    if(b>>i&1)res=(res*a)%1000000007;
    a=(a*a)%1000000007;
  }
  return res;
}

int beki(int x){
  int y=(x*(x-1))/2,p=1;
  return POW(2,y);
}

int bbeki(int s,int t){
  int p=POW(2,s);
  p--;
  int c=POW(p,t);
  return c;
}

main(){
  int n;
  cin>>n;
  int a[n];
  for(int i=0;i<n;i++) cin>>a[i];
  if(a[0]){
    cout<<0<<endl;
    return 0;
  }
  sort(a,a+n);
  for(int i=1;i<n;i++){
    if(a[i-1]+1<a[i]||a[1]==0){
      cout<<0<<endl;
      return 0;
    }
  }
  a[n]=1e9;
  int ans=1;
  int pre=1,now=0;
  for(int i=1;i<n;i++){
    now=1;
    while(a[i]==a[i+1])now++,i++;
    ans*=beki(now);
    ans%=1000000007;
    ans*=bbeki(pre,now);
    //cout<<pre<<now<<' '<<ans<<endl;
    ans%=1000000007;
    pre=now;
  }
  cout<<ans<<endl;
}