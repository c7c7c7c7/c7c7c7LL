#include<bits/stdc++.h>
using namespace std;
#define P pair<int,int>
#define mk make_pair
int dx[]={1,1,1,0,0,-1,-1,-1};
int dy[]={1,0,-1,1,-1,1,0,-1};
int ddx[]={-2,-2,-2,-2,-2,-1,-1,0,0,1,1,2,2,2,2,2};
int ddy[]={-2,-1,0,1,2,-2,2,-2,2,-2,2,-2,-1,0,1,2};
int c[4];
int main(){
	map<P,int>s;
	vector<P>v1,v2;
	int n,w,h;
	cin>>w>>h>>n;
	for(int i=0;i<n;i++){
		int x,y;
		cin>>x>>y;
		if(x==0||y==h-1)v1.push_back(mk(x,y));
		if(y==0||x==w-1)v2.push_back(mk(x,y));
		s[mk(x,y)]=0;
	}
	if(s.find(mk(w-1,h-2))!=s.end())c[3]=1;
	if(s.find(mk(w-2,h-1))!=s.end())c[2]=1;
	if(s.find(mk(0,1))!=s.end())c[1]=1;
	if(s.find(mk(1,0))!=s.end())c[0]=1;
	if(c[0]&&c[1]||c[2]&&c[3])goto L0;
	for(vector<P>::iterator it=v1.begin();it!=v1.end();it++){
		int x=(*it).first,y=(*it).second;
		if(s[mk(x,y)]==0){
			queue<P>q;
			q.push(mk(x,y));
			if(s[mk(x,y)]==0){if(y==0||x==w-1)goto L0;}
			s[mk(x,y)]=1;
			while(!q.empty()){
				P po=q.front();q.pop();
				int xx=po.first,yy=po.second;
				for(int i=0;i<8;i++){
					int px=xx+dx[i],py=yy+dy[i];
					if(s.find(mk(px,py))!=s.end())if(s[mk(px,py)]==0){
						if(py==0||px==w-1)goto L0;
						s[mk(px,py)]=1;
						q.push(mk(px,py));
					}
				}
			}
		}
	}
	for(vector<P>::iterator it=v2.begin();it!=v2.end();it++){
		int x=(*it).first,y=(*it).second;
		if(s[mk(x,y)]==0){
			queue<P>q;
			q.push(mk(x,y));
			s[mk(x,y)]=2;
			if(s[mk(x,y)]==0){if(x==0||y==h-1)goto L0;}
			while(!q.empty()){
				P po=q.front();q.pop();
				int xx=po.first,yy=po.second;
				for(int i=0;i<16;i++){
					int px=xx+ddx[i],py=yy+ddy[i];
					if(s.find(mk(px,py))!=s.end()){
						if(s[mk(px,py)]==1)goto L1;
					}
				}
				for(int i=0;i<8;i++){
					int px=xx+dx[i],py=yy+dy[i];
					if(s.find(mk(px,py))!=s.end())if(s[mk(px,py)]==0){
						if(px==0||py==h-1)goto L0;
						s[mk(px,py)]=2;
						q.push(mk(px,py));
					}
				}
			}
		}
	}
	for(int i=0;i<4;i++)if(c[i])goto L1;
	goto L2;
	if(0)L0:cout<<0<<endl;
	if(0)L1:cout<<1<<endl;
	if(0)L2:cout<<2<<endl;
}