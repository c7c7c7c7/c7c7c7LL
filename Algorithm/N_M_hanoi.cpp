#include<bits/stdc++.h>
using namespace std;
struct N_M_hanoi{
  int M=555,N=555;
  long long INF = 1e17;
  long long han[555][555];
  N_M_hanoi(){
    for(int i=1;i<60;i++)
      han[3][i]=pow(2,i)-1;
    dfs(4);
  }
  void dfs(int d){
    if(d==N)return;
    for(int i=1;i<M;i++){
      long long x=INF;
      if(i>=d)for(int j=i-1,p=1;j>=0;j--,p++){
        long long t=han[d-1][p]+han[d][j]*2;
        if(x>=t)x=t;
        else break;
      }
      else x=i*2-1;
      han[d][i]=x;
    }
    dfs(d+1);
  }
  long long N_M(int a,int b){
    return han[a][b];
  }
};
int main(){
  N_M_hanoi A;
  int x,y;
  while(cin>>x>>y){
    cout<<A.han[x][y]<<endl;
  }
}
//ちーん。ニートニートヤクルトwwwwwwムックルクルwwwwwwヒェヒェヒt(←いずらいt)ェヒェwwwwポて。