/*
   最大支配集合
*/

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int V,E,ans;
ll edge[64];
ll sum_edge[64];
void MDS(int cur,int cost,ll mask){
	if(cost>=ans)return;
	if(mask==(1LL<<V)-1){
		ans=cost;
		return;
	}
	if(cur>=V)return;
	if((mask|sum_edge[cur])!=(1LL<<V)-1)return;
	MDS(cur+1,cost+1,mask|edge[cur]);
	MDS(cur+1,cost,mask);
}
int main(){
	while(cin>>V>>E,V){
		for(int i=0;i<V;i++)edge[i]=(1LL<<i);
		for(int i=0;i<E;i++){
			int A,B;
			cin>>A>>B;
			edge[A]|=(1LL<<B);
			edge[B]|=(1LL<<A);
		}
		for(int i=V-1;i>=0;i--) sum_edge[i] = edge[i];
		for(int i=V-2;i>=0;i--) sum_edge[i] |= sum_edge[i+1];
		ans=1e9;
		MDS(0,0,0);
		cout<<ans<<endl;
	}
}