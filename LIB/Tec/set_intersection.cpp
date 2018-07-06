#include <bits/stdc++.h>
#define r(i,n) for(int i=0;i<n;i++)
using namespace std;
int main(){
  int n,m;
  cin>>n>>m;
  set<int>s1,s2,s3,s4;
  r(i,n){
    int a;
    cin>>a;
    s3.insert(a);
    s1.insert(a);
  }
  r(i,n){
    int a;
    cin>>a;
    s3.insert(a);
    s2.insert(a);
  }
  set_intersection(s1.begin(),s1.end(),s2.begin(),s2.end(),inserter(s4,s4.end()));
  double x=s4.size();
  double y=s3.size();
  printf("%.9f\n",x/y);
}