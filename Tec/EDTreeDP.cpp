#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int>P;

int n,dis[100005];
vector<P>v[100005];

void dfs1(int idx,int pre){
	for(int i=0;i<v[idx].size();i++){
		int next=v[idx][i].first;
		int cost=v[idx][i].second;
		if(next==pre)continue;
		dfs1(next,idx);
		dis[idx]=max(dis[idx],dis[next]+cost);
	}
}

int dfs2(int idx,int d_pre,int pre){
	vector<P>child;
	child.push_back(P(0,-1));
	for(int i=0;i<v[idx].size();i++){
		int next=v[idx][i].first;
		int cost=v[idx][i].second;
		if(next==pre)child.push_back(P(d_pre+cost,next));
		else child.push_back(P(dis[next]+cost,next));
	}
	sort(child.begin(),child.end(),greater<P>());
	int res=child[0].first+child[1].first;
	for(int i=0;i<v[idx].size();i++){
		int next=v[idx][i].first;
		int cost=v[idx][i].second;
		if(next==pre)continue;
		res=max(res,dfs2(next,child[next==child[0].second].first,idx));
	}
	return res;
}

int main(){
	cin>>n;
	for(int i=0;i<n-1;i++){
		int a,b,w;
		cin>>a>>b>>w;
		v[a].push_back(P(b,w));
		v[b].push_back(P(a,w));
	}
	dfs1(n/2,-1);
	cout<<dfs2(n/2,0,-1)<<endl;
}