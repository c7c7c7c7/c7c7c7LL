#include <bits/stdc++.h>
#define r(i,n) for(int i=0;i<n;i++)
using namespace std;
const double EPS=1E-8;
typedef vector<double> vec;
typedef vector<vec> mat;
vec gauss_jordan(const mat& A,const vec& b){
  int n=A.size();
  mat B(n,vec(n+1));
  for(int i=0;i<n;i++)
    for(int j=0;j<n;j++)
      B[i][j]=A[i][j];
  for(int i=0;i<n;i++) B[i][n]=b[i];
  for(int i=0;i<n;i++){
    int pivot=i;
    for(int j=i;j<n;j++) if(abs(B[j][i])>abs(B[pivot][i])) pivot=j;
    swap(B[i],B[pivot]);
    if(abs(B[i][i])<EPS) return vec();
    for(int j=i+1;j<=n;j++) B[i][j]/=B[i][i];
    for(int j=0;j<n;j++){
      if(i!=j){
		for(int k=i+1;k<=n;k++) B[j][k]-=B[j][i]*B[i][k];
      }
    }
  }
  vec x(n);
  for(int i=0;i<n;i++) x[i]=B[i][n];
  return x;
}
main(){
	int d;
	while(cin>>d,d){
		double a[d+3];
		mat A(d+3,vec(d+2));
		for(int i=0;i<d+3;i++)cin>>a[i];
		for(int i=0;i<d+3;i++){
			for(int j=0;j<d+1;j++){
				A[i][j]=pow(1.0*i,j);
			}
		}
		double eps = 1e-5;
		for(int i=0;i<d+3;i++){
			for(int j=i+1;j<d+3;j++){
				int cnt=0;
				vec ans(d+1);
				mat B(d+1,vec(d+1));
				for(int k=0,l=0;k<d+3;k++){
					if(k!=i&&k!=j){
						B[cnt]   = A[k];
						ans[cnt] = a[k];
						cnt++;
					}
				}
				vec v=gauss_jordan(B,ans);
				//cout<<v.size()<<endl;
				double res[2]={};
				for(int k=0;k<d+1;k++){
					res[0] += v[k]*A[i][k];
					res[1] += v[k]*A[j][k];
				}
				if(abs(res[0]-a[i])>eps&&abs(res[1]-a[j])<eps){
					cout<<i<<endl;
					goto L;
				}
				if(abs(res[1]-a[j])>eps&&abs(res[0]-a[i])<eps){
					cout<<j<<endl;
					goto L;
				}
			}
		}L:;
	}
}