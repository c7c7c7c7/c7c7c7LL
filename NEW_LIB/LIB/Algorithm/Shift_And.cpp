#include<bits/stdc++.h>
using namespace std;


//  sにtが何回含まれるか
int Shift_And(string &s,string &t){
    int n=s.size(),m=t.size();
    int M[0x1000]; fill(M,M+0x100,0);
    int cnt=0;
    for(int i=0;i<m;i++)M[t[i]]|=(1<<i);
    for(int i=0,S=0;i<n;i++){
        S=((S<<1)|1)&M[s[i]];
        if(S&(1<<(m-1)))cnt++;
    }
    return cnt;
}

int main(){
    string s,t;
    cin>>s>>t;
    cout<<Shift_And(s,t)<<endl;
}