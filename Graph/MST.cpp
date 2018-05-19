#include <bits/stdc++.h>
using namespace std;
#define REP(i,a,n) for(int i=a;i<n;i++)
#define mat vector<vector<int> >
struct Minimum_Steiner_Tree{
	mat V;
	vector<int>T;
	int n,numT,Inf=1e8;
	Minimum_Steiner_Tree(int sz):n(sz),numT(0),V(sz,vector<int>(sz)){
		REP(i,0,sz)REP(j,0,sz)V[i][j]=(i==j?0:Inf);
	}
	void add_edge(int a,int b,int c){ V[a][b]=V[b][a]=c; }
	void add_vertex(int a){ T.push_back(a); numT++;}
	int build(){
		if(numT<=1)return 0;
		mat d(V);
		REP(k,0,n)REP(i,0,n)REP(j,0,n)d[i][j]=min( d[i][j], d[i][k] + d[k][j] );
		int OPT[(1<<numT)][n];
		REP(i,0,(1<<numT))REP(j,0,n)OPT[i][j]=Inf;
		REP(i,0,numT)REP(j,0,n)OPT[1<<i][j]=d[T[i]][j];
		REP(S,1,(1<<numT))if(S&(S-1)){
			REP(i,0,n)REP(j,0,S)if((S|j)==S) OPT[S][i] = min( OPT[S][i], OPT[j][i] + OPT[S-j][i] );
			REP(i,0,n)REP(j,0,n) OPT[S][i] = min( OPT[S][i], OPT[S][j] + d[i][j] );
		}
		int ans=Inf;
		REP(i,0,(1<<numT))REP(j,0,n)ans = min(ans, OPT[i][j] + OPT[((1 << numT)-1)-i][j]);
		return n-ans-1;
	}
};
int dx[]={1,-1,0,0};
int dy[]={0,0,1,-1};
int main(){
	int h,w,t;
	while(cin>>h>>w,h){
		Minimum_Steiner_Tree M(h*w);
		REP(i,0,h)REP(j,0,w){
			cin>>t;
			if(t)M.add_vertex(i*w+j);
			REP(k,0,4){
				int y=i+dy[k];
				int x=j+dx[k];
				if(y<0||x<0||y>=h||x>=w)continue;
				M.add_edge(i*w+j,y*w+x,1);
			}
		}
		cout<<M.build()<<endl;
	}
}