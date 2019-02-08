#include <bits/stdc++.h>
using namespace std;

struct Ahocora{
 
  int idx=0;
 
  struct PMA {
      int state;
      PMA* next[256];
      vector<int> matched;
      PMA(int idx) { memset(next, 0, sizeof(next)); state = idx ; }
      ~PMA() { for(int i = 0; i < 256; i++) if(next[i]) delete next[i]; }
  };
  vector<int> set_uni(const vector<int> &a,const vector<int> &b) {
      vector<int> res;
      set_union(a.begin(),a.end(),b.begin(),b.end(), back_inserter(res));
      return res;
  };
 
  PMA *root;
 
  map<int,PMA*>M;
 
  Ahocora(vector<string> &pattern) {
      root = new PMA(idx++);
      M[idx-1]=root;
      PMA *now;
      root->next[0] = root;
      for(int i = 0; i < pattern.size(); i++) {
          now = root;
          for(int j = 0; j < pattern[i].size(); j++) {
              if(now->next[(int)pattern[i][j]] == 0){
                  now->next[(int)pattern[i][j]] = new PMA(idx++);
                  M[idx-1] = now->next[(int)pattern[i][j]];
                }
              now = now->next[(int)pattern[i][j]];
          }
          now->matched.push_back(i);
      }
 
      queue<PMA*> que;
 
      for(int i=1;i<256;i++){
          if(!root->next[i]) root->next[i] = root;
          else{
              root->next[i]->next[0] = root;
              que.push(root->next[i]);
          }
      }
 
      while(!que.empty()) {
          now = que.front(); que.pop();//cout<<1;
          for(int i = 1; i < 256; i++) {
              if(now->next[i]){
                  PMA *nxt = now->next[0];
                  while(!nxt->next[i]) nxt = nxt->next[0];
                  now->next[i]->next[0] = nxt->next[i];
                  now->next[i]->matched = set_uni(now->next[i]->matched, nxt->next[i]->matched);
                  que.push(now->next[i]);
              }
          }
      }
 
  }
  void match( const string s, vector<int> &res) {
    PMA *pma=root;
      for(int i = 0; i < s.size(); i++){
          int c = s[i];
          while(!pma->next[c]) pma = pma->next[0];
          pma = pma->next[c];
          for(int j = 0; j < pma->matched.size(); j++)
              res[pma->matched[j]] = true;
      }
  }
  typedef pair<string,int>Pi;

 
  vector<int> match( const string &s,int S) {
    PMA *pma=M[S];
    int res=0;
    vector<int>V;
      for(int i = 0; i < s.size(); i++){
          int c = s[i];
          while(!pma->next[c]) pma = pma->next[0];
          pma = pma->next[c];
          for(int j = 0; j < pma->matched.size(); j++) V.push_back(pma->matched[j]);
      }
    return V;
  }
 
  //http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2212
  int NG( string s,int S) {
    PMA *pm = M[S];
    for(int i = 0; i < s.size(); i++){
        int c = s[i];
        while(!pm->next[c]) pm = pm->next[0];
        pm = pm->next[c];
        for(int j = 0; j < pm->matched.size(); j++) return -1;
    }
    return pm->state;
  }
  
};
 
#define r(i,n) for(int i=0;i<n;i++)
typedef pair<int,int>P;
typedef pair<P,P>P2;

int dp[210009];
string s;
vector<string>v;
string a;
int n,w[5005];
 
int main(){
  cin>>s>>n;
  r(i,n){
    cin>>a;
    v.push_back(a);
  }
  r(i,n)cin>>w[i];

  Ahocora AHO(v);

  r(i,s.size()){
    string p;
    r(j,200){
      if(i+j>=s.size())break;
      p+=s[i+j];
    }
    //cout<<p<<endl;
    vector<int> A = AHO.match(p,0);

    r(j,A.size()) {
      dp[A[j]+i] = max(dp[A[j]+i],dp[i]+w[A[j]]);
    }
  }
  int ans=0;
  r(i,210000) ans=max(ans,dp[i]);
  cout<<ans<<endl;
}


