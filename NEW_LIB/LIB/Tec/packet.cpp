#include <bits/stdc++.h>
using namespace std;

// 区間[l,r)をパケット分割

const int pac = 400;

int dat[200009] , DAT[500];


void add(int x,int y){
  dat[x] += y;
  DAT[x/pc] += y;
}

int packet(int l,int r){
  int res=0;
  while( l<r && l%pac) { res += dat[l]; l++; }
  while( l<r && r%pac) { r--; res += dat[r]; }
  while( l<r ) { res += DAT[l/pac];  l+=pac; }
  return res;
}


int main(){
  int n,m;
  cin>>n>>m;
  while(m--){
    int a,b,c;
    cin>>a>>b>>c;
    if(a)cout<<packet(b,c+1)<<endl;
    else add(b,c);
  }
}
