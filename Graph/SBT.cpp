#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//  x/y < p  を満たす最大の既約分数を　x<=n y<=n で返す

void SBT_MAX(ll n,ll p,ll &x,ll&y,ll pl=0,ll ql=1,ll pr=1,ll qr=0){
	ll pm = pl + pr , qm = ql + qr ;
	if( pm > n || qm > n ) return ;
	if( p*qm >= pm ){
		x=pm,y=qm;
		SBT_MAX( n , p , x , y , pm , qm , pr , qr );
	}
	if( p*qm < pm ){
		SBT_MAX( n , p , x , y , pl , ql , pm , qm );
	}
}
//   p < x/y を満たす最小の既約分数を　x<=n y<=n で返す

void SBT_MIN(ll n,ll p,ll &x,ll&y,ll pl=0,ll ql=1,ll pr=1,ll qr=0){
	ll pm = pl + pr , qm = ql + qr ;
	if( pm > n || qm > n ) return ;
	if( p*qm > pm ){
		SBT_MIN( n , p , x , y , pm , qm , pr , qr );
	}
	if( p*qm <= pm ){
		x=pm,y=qm;
		SBT_MIN( n , p , x , y , pl , ql , pm , qm );
	}
}

//  x/y < √p  を満たす最大の既約分数を　x<=n y<=n で返す

void SBT_MAX_Sqrt(ll n,ll p,ll &x,ll&y,ll pl=0,ll ql=1,ll pr=1,ll qr=0){
	ll pm = pl + pr , qm = ql + qr ;
	if( pm > n || qm > n ) return ;
	if( p*qm*qm > pm*pm ){
		x=pm,y=qm;
		SBT_MAX_Sqrt( n , p , x , y , pm , qm , pr , qr );
	}
	if( p*qm*qm < pm*pm ){
		SBT_MAX_Sqrt( n , p , x , y , pl , ql , pm , qm );
	}
}
//   √p < x/y を満たす最小の既約分数を　x<=n y<=n で返す

void SBT_MIN_Sqrt(ll n,ll p,ll &x,ll&y,ll pl=0,ll ql=1,ll pr=1,ll qr=0){
	ll pm = pl + pr , qm = ql + qr ;
	if( pm > n || qm > n ) return ;
	if( p*qm*qm > pm*pm ){
		SBT_MIN_Sqrt( n , p , x , y , pm , qm , pr , qr );
	}
	if( p*qm*qm < pm*pm ){
		x=pm,y=qm;
		SBT_MIN_Sqrt( n , p , x , y , pl , ql , pm , qm );
	}
}

int main(){
	ll n,p;
	while(cin>>p>>n,p){
		ll a1,b1,a2,b2;
		SBT_MIN_Sqrt(n,p,a1,b1);
		SBT_MAX_Sqrt(n,p,a2,b2);
		cout<<a1<<'/'<<b1<<' '<<a2<<'/'<<b2<<endl;
	}
}