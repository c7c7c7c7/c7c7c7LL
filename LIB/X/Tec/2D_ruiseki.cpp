#include <bits/stdc++.h>
using namespace std;
#define r(i,n) for(int i=0;i<n;i++)
int a[111][111],b[111][111];
int main(){
	int h,w,ans=0;
	cin>>h>>w;
	r(i,h)r(j,w){
		int x;
		cin>>x;
		if((i%2)==(j%2))a[i+1][j+1]=x;
		else b[i+1][j+1]=x;
	}
	for(int i=1;i<=h;i++){
		for(int j=1;j<w;j++){
			a[i][j+1]+=a[i][j];
			b[i][j+1]+=b[i][j];
		}
	}
	for(int i=1;i<=w;i++){
		for(int j=1;j<h;j++){
			a[j+1][i]+=a[j][i];
			b[j+1][i]+=b[j][i];
		}
	}
	for(int i=0;i<h;i++){
		for(int j=0;j<w;j++){
			for(int k=i+1;k<=h;k++){
				for(int l=j+1;l<=w;l++){
					int A=a[k][l]-a[k][j]-a[i][l]+a[i][j];
					int B=b[k][l]-b[k][j]-b[i][l]+b[i][j];
					if(A==B)ans=max(ans,(k-i)*(l-j));
				}
			}
		}
	}
	cout<< ans <<endl;
}