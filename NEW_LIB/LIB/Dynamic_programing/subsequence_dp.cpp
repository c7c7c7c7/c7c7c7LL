#include <bits/stdc++.h>
using namespace std;

vector<vector<int> > calcNext(const string &S) {
    int n = (int)S.size();
    vector<vector<int> > res(n+1, vector<int>(26, n));
    for (int i = n-1; i >= 0; --i) {
        for (int j = 0; j < 26; ++j) res[i][j] = res[i+1][j];
        res[i][S[i]-'a'] = i;
    }
    return res;
}
z
int main(){
    string s;
    cin>>s;
    int n=s.size();

    vector<vector<int> >next=calcNext(s);

    int dp[n+1]={};
    dp[0]=1;

    for(int i=0;i<n;i++){
        for(int j=0;j<26;j++){
            if(next[i][j]>=n)continue;

            dp[next[i][j]+1] += dp[i];
            dp[next[i][j]+1] %= 1000000007;
        }
    }

    int ans=0;
    for(int i=0;i<=n;i++) ans+=dp[i] , ans%=1000000007;
    cout<<ans<<endl;
}