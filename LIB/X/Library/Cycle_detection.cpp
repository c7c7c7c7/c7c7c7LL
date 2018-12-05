#include<bits/stdc++.h>
using namespace std;
bool used[101],flag;
vector<int>v[101];
void dfs(){

}
int main(){
  int n,m;
  cin>>n>>m;
  while(m--){
    int a,b;
    cin>>a>>b;
    v[a].push_back(b);
  }
  dfs();
}
