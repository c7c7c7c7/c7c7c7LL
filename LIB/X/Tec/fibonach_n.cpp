#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef vector<int>vec;
typedef vector<vec>mat;
const int M=1000000007;
mat mul(mat A,mat B){
    mat C(A.size(),vec(B[0].size()));
    for(int i=0;i<A.size();i++){
        for(int j=0;j<B[0].size();j++){
            for(int k=0;k<A[0].size();k++){
                C[i][j]=(C[i][j]+A[i][k]*B[k][j])%M;
            }
        }
    }
    return C;
}
 
mat matpow(mat A,int k){
    mat B(A.size(),vec(A.size()));
    for(int i=0;i<A.size();i++)B[i][i]=1;
    while(k){
        if(k&1)B=mul(B,A);
        A=mul(A,A);
        k>>=1;
    }
    return B;
}
 
int sol(int n){
    mat A(2,vec(2));
    A[0][0]=1;A[0][1]=1;
    A[1][0]=1;A[1][1]=0;
    A=matpow(A,n);
    return A[1][0];
}

void out(int x,int y){
    cout<<(sol(x+1)*sol(y+1))%M<<endl;
    exit(0);
}

signed main(){
    int K;
    cin>>K;
    int l=0,r=(1e9)*4;
    while(l<r){
        int mid=(l+r)/2;
        if(mid*(mid+1)>=K)r=mid;
        else l=mid+1;
    }
    l--;
    int cnt=0;
    K-=l*(l+1);
    int x=r*2-1,p=0;
    if(K>r)K-=r,x++,p++;
    int y=1;
    while(x>=y){
        cnt++;
        if(cnt==K)out(x,y);
        x-=2;y+=2;
    }
    x+=2;
    y-=2;
   // cout<<r<<endl;
   // cout<<x<<' '<<y<<endl;
    if(!p){
        if((x==r+1&&y==r-1))x--,y++;
        else x++,y--;
    }
    else{
        if(x==y+x/2)x++,y--;
        else x--,y++;
    }
    //cout<<x<<' '<<y<<endl;

    while(1){
        cnt++;
        if(cnt>=100000000)exit(1);
        if(cnt==K)out(x,y);
        x+=2;y-=2;
    }
    //cout<<K<<' '<<l<<endl;
}