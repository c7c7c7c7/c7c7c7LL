#include <bits/stdc++.h>
using namespace std;
#define MAX 1010
int N;
int bit[MAX][MAX];
void add(int a,int b,int w){
  for (int x=a; x<=N; x += x & -x )
    for (int y=b; y<=N; y += y & -y )
      bit[x][y] += w;
}
int sum(int a,int b){
  int res = 0;
  for (int x=a; x>0; x-= x& -x)
    for (int y=b; y>0; y-= y& -y)
      res += bit[x][y];
  return res;
}
int get sum(int x1,int y1,int x2 int y2){
  return sum(x2,y2) + sum(x1,y1) - sum(x1,y2) - sum(x2,y1);
}
int main(){
  
}