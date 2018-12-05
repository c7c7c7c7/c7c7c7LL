#include <bits/stdc++.h>
using namespace std;

struct CHT{
    deque<pair<int,int>>ls;
    inline bool check(const pair<int,int>&a,const pair<int,int>&b,const pair<int,int>&c){
        return (b.first-a.first)*(c.second-b.second)>=(b.second-a.second)*(c.first-b.first);
    }
    void add(int a,int b){
        pair<int,int>l(a,b);
        while(ls.size()>=2&&check(ls[ls.size()-2],ls[ls.size()-1],l))ls.pop_back();
        ls.push_back(l);
    }
    int query(int x){
        assert(ls.size());
        while(ls.size()>1&&ls[0].first*x+ls[0].second>=ls[1].first*x+ls[1].second)ls.pop_front();
        return ls[0].first*x+ls[0].second;
    }
};

// query が　単調増加のときだけ

int main(){
  CHT C;
  C.add(1,0);
  C.add(-1,0);
  int n;
  while(cin>>n)cout<<C.query(n)<<endl;
}