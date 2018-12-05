#include <bits/stdc++.h>
using namespace std;

struct color_3{
    int n , adj[44][44] , color[44] ,ans ;
    vector<int> v[44];

    color_3(int sz){
        n = sz;
        memset(adj,0,sizeof(adj));
        for(int i=0;i<44;i++)v[i].clear();
    }

    void add_edge(int a,int b){
        adj[a][b] = adj[b][a] = 1;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    int dfs(int x){
        for(int i=0;i<v[x].size();i++){
            int nex = v[x][i];
            if(nex<x && color[x]==color[nex])return 0;
        }
        if(n-1==x)return 1;
        for(int c=0;c<3;c++){
            if(adj[x][x+1]&&c==color[x])continue;
            color[x+1]=c;
            if(dfs(x+1))return 1;
        }
        return 0;
    }
    bool build(){
        color[0]=0;
        return dfs(0);
    }
};

signed main(){
    int t;
    cin>>t;
    while(t--){
        int n,p;
        cin>>n>>p;
        color_3 C(n);
        while(p--){
            int x,y;
            cin>>x>>y;
            C.add_edge(x,y);
        }
        cout<<(C.build()?"Y":"N")<<endl;
    }
}