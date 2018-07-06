#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct LCT{
  struct T {
    ll val , sum , lz ; int y, sz ; T *l , *r , *p ;
    T ( int v ) { val = sum = v ; y = rand(); sz = 1; lz = 0 ; l = r = p = NULL ; }
  }; 
  typedef T* ptr;
  ptr L [ 100002 ] , R [ 100002 ] , t = 0; // t only aux
  int p[100002],H[100002];

  LCT(int sz,vector<int> &x){
    for( int i = 0 ; i < sz ; i++ ){
      L[i] = new T(x[i]) ; R[i] = new T(x[i]); merge ( t , L[i] , R[i] ) ; // init :v
    }
  }
  void build(vector<int> &H1,vector<int> &p1){
    for(int i=0;i<H1.size();i++){
      H[i]=H1[i];
      p[i]=p1[i];
    }
  }
  inline int sz ( ptr t ) { return t ? t->sz : 0 ; }
  inline ll sum ( ptr t ) { return t ? t->sum : 0LL ; } 
  inline void upd ( ptr t ) { if ( t ) t->sz = sz(t->l) + sz(t->r) + 1 ; }
  inline ptr root ( ptr t ) { return t->p ? root ( t->p ) : t ; }
  inline int pos ( ptr t , bool L = 1 ) {
    return !t ? 0 : (int)(L) * sz(t->l) + ( t->p ? pos(t->p, t->p->r==t ) + ( t->p->r==t ): 0 );
  }
  inline void pushLazy ( ptr t ) {
    if ( !t || !t->lz ) return ; upd ( t ) ;
    t->sum += sz(t) * t->lz ; t->val += t->lz ;
    if ( t->l ) t->l->lz += t->lz ;
    if ( t->r ) t->r->lz += t->lz ;
    t->lz = 0 ;
  }
  inline void push ( ptr t ) {
    if ( !t ) return ;
    upd ( t ) ; pushLazy ( t->l ) ; pushLazy ( t->r ) ;
    t->sum = t->val + sum ( t->l ) + sum ( t->r ) ;
  }
  void split ( ptr t , ptr &l , ptr &r , int s ) {
    pushLazy ( t ) ;
    if ( !t ) l = r = 0 ;
    else if ( sz ( t->l ) <= s ) {
      split ( t->r , t->r , r , s - sz ( t->l ) - 1 ) ; 
      l = t ; if ( l->r ) l->r->p = l ;
    }else{
      split ( t->l , l , t->l , s ) ; r = t ;
      if ( r->l ) r->l->p = r ;
    }
    push ( r ) ; push ( l ) ;
    if ( l ) l->p = 0 ; if ( r ) r->p = 0 ;
  }
  void merge ( ptr &t , ptr l , ptr r ) {
    pushLazy ( l ) ; pushLazy ( r ) ;
    if ( !l || !r ) t = r ? r : l ;
    else if ( l->y > r->y ) { merge ( l->r , l->r , r ) ; t = l ; if ( l->r ) l->r->p = t ; }
    else { merge ( r->l , l , r->l ) ; t = r ; if ( r->l ) r->l->p = t ; }
    push ( t ) ; if ( t ) t->p = 0 ;
  }
  void cut ( int x ) {
    if ( pos ( L[x] ) == 0 ) return ;
    ptr t3 = root ( L[x] ), t1 , t2 ;
    int l = pos ( L[x] ) , r = pos ( R[x] ) ;
    split ( t3 , t3 , t1 , l - 1 ) ; split ( t1 , t1 , t2 , r - l ) ;
    merge ( t3 , t3 , t2 ) ;
  }
  void link ( int x , int y ) { // p[x] = y in directed tree
    if ( root ( L[x] ) == root ( L[y] ) ) return ;
    ptr t1 = root ( L[x] ) , t2 = root ( L[y] ) , t3 ;
    split ( t2 , t2 , t3 , pos ( L[y] ) ) ;
    merge ( t2 , t2 , t1 ) ; merge ( t2 , t2 , t3 ) ;
  }
  ll query ( int x , ll u = 0 ) {
    int l = pos ( L[x] ) , r = pos ( R[x] ) ;
    ptr t1 , t2 , t0 = root ( L[x] ) , t3 ;
    split ( t0 , t1 , t2 , l - 1 ) ; split ( t2 , t0 , t3 , r - l ) ;
    if ( u == 0 ) u = t0->sum / 2LL ; else t0->lz += u ; // response or lazy propagation
    merge ( t2 , t0 , t3 ) ; merge ( t0 , t1 , t2 ) ;
    return u ;
  }
  bool valid( int a , int b , int c, int d ){
    if( a<=c && d<=b ) return 1;
    swap( a,c ) , swap( b,d ) ;
    if( a<=c && d<=b ) return 1;
    return 0;
  }
  int swap_subtree(int b,int c){
    int i1 = pos( L[ b ] ) , i2 = pos( R[ b ] ) , i3 = pos( L[ c ] ) , i4 = pos( R[ c ] ) ;
    if( valid( i1,i2,i3,i4 ) ) return -1;
    else{
      cut( b ) , cut( c );
      link( b , p[ c ] ) , link( c , p[ b ] );
      swap( p[c] , p[b] );
    }
    return 0;
  }
};
vector< int > G[ 100005 ] ;
vector<int> H , p;
int val;
void dfs( int u  , int v  , int h ){
  H[ u ] = h ;
  p[ u ] = v ;
  for( int i : G[ u ] ) if( i != v ) dfs( i , u , h+1 ) ;
  return ;
}
vector<int>x;
int main() {
  int n , m ;
  cin>> n >> m ;
  for( int i = 0 ; i < n ; i++ ){
    H.push_back(0);
    p.push_back(0);
    cin>>val;
    x.push_back(val);
  }
  LCT lct(n,x);
  for(int i = 1 , u , v ; i < n ; i++ ){
    cin >> u >> v ; u-- , v-- ;
    G[ u ].push_back( v ) ;
    G[ v ].push_back( u ) ;
  }
  dfs( 0 , -1 , 1 ) ;
  lct.build(H,p);
  for(int i = 1 ; i < n ; i ++ ){
    lct.link( i , lct.p[ i ] ) ;
  }
  for( int i = 0 , a , b ,c  ; i< m ;i ++ ){
    cin >> a ;
    if( a== 1 ){
      cin>> b ;
      cout<< lct.query( b-1 )<<endl;
    }
    else if( a==2 ){
      cin>> b >> c ;
      lct.query( b-1 , c ) ;
    }
    else{
      cin>> b >> c ;
      b-- , c -- ;
      int t=lct.swap_subtree(b,c);
      if(t==-1)cout<<-1<<endl;
    }
  }
 
}