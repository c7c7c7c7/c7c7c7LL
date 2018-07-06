#include <bits/stdc++.h>
#define r(i,n) for(int i=0;i<n;i++)
using namespace std;
typedef pair<int,int>P;
typedef pair<int,P>P2;
typedef pair<P,P>PP;
#define fi first
#define se second

struct Range_merge_query{
	set<pair<int,int> >st;
	set<pair<int,int> >::iterator it1,it2;
	void init(int N){ for(int i=0;i<N+1;i++)st.insert(make_pair(i,i)); }
	bool query(int l,int r){
		it1 = st.lower_bound( make_pair(l,-1) );
		it2 = st.lower_bound( make_pair(r,-1) );
		return it1 == it2;
	}
	void merge(int l,int r){
		it1 = st.lower_bound( make_pair(l,-1) );
		it2 = st.lower_bound( make_pair(r,-1) );
		int L=it1->second;
		int R=it2->first;
		it2++;
		st.erase(it1,it2);
		st.insert( make_pair(R,L) );
	}
};


bool ans[100009];

int main(){
	Range_merge_query R;
	vector<P2>vm;
	vector<PP>vq;
	int n,m,q,a,b,c,idx=0;
	cin>>n>>m>>q;
	r(i,m+q){
		cin>>a>>b>>c;
		if(i<m)vm.push_back(P2(a,P(b,c)));
		else vq.push_back(PP(P(a,i-m),P(b,c)));
	}
	R.init(n);
	sort(vm.begin(),vm.end());
	sort(vq.begin(),vq.end());
	r(i,q){
		PP p=vq[i];
		int l=p.se.fi;
		int r=p.se.se;
		if(r<=l){
			ans[vq[i].fi.se]=1;
			continue;
		}
		while(idx<m&&vm[idx].fi<p.fi.fi){
			R.merge(vm[idx].se.fi,vm[idx].se.se);
			idx++;
		}
		if(R.query(p.se.fi,p.se.se))ans[p.fi.se]=1;
	}
	r(i,q)cout<<(ans[i]?"Yes":"No")<<endl;
}