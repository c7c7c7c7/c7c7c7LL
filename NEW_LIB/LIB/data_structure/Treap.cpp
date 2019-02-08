#include <bits/stdc++.h>
#define r(i,n) for(int i=0;i<n;i++)
using namespace std;



unsigned long long xor128() {
    static unsigned long long rx = 123456789, ry = 362436069, rz = 521288629, rw = 88675123;
    unsigned long long rt = (rx ^ (rx << 11));
    rx = ry;
    ry = rz;
    rz = rw;
    return (rw = (rw ^ (rw >> 19)) ^ (rt ^ (rt >> 8)));
}


template<class T> class treap{
public:
 
    struct node{
        T val,sum,mini,maxi;
        node *left , *right;
        bool init;
        int pri;
        unsigned sz;
        node(){
            sum = 0;
            mini = INT_MAX;
            maxi = INT_MIN;
            sz = 1;
            init=true;
            pri=xor128();
            left = right = NULL;
        }
        node(T val,int pri):val(val),pri(pri),sz(1){
            init = false;
            sum = val;
            mini = val;
            maxi = val;
            left = right = NULL;
        }
    };
 
    node *root;
 
    treap():root(NULL){}
 
    treap(int n):root(NULL){
        for(int i=0;i<n;i++){
            init_insert();
        }
    }
 
    unsigned size(){ return size(root); }
    unsigned size(node *v){ return !v?0:v->sz; }
    T sum(node *v){ return !v  ?    0    : v->sum  ; }
    T MIN(node *v){ return !v  ? INT_MAX : v->mini ; }
    T MAX(node *v){ return !v  ? INT_MIN : v->maxi ; }
 
    node *update(node *v){
        v->sz = size(v->left)+size(v->right)+1;
        //v->sum = sum(v->left)+sum(v->right)+ (v->init?0:v->val);
        v->mini = min( v->init?INT_MAX:v->val , min( MIN(v->left) , MIN(v->right) ) ) ;
        //v->maxi = max( v->init?INT_MIN:v->val , max( MAX(v->left) , MAX(v->right) ) ) ;
        return v;
    }
 
    node *merge(node *s , node *t){
        if( !s || !t )return s?s:t;
        //update(s);
        //update(t);
        if( s->pri > t->pri){
            s->right = merge( s->right , t );
            return update(s);
        }
        else{
            t->left = merge( s, t->left);
            return update(t);
        }
    }
 
    pair<node*,node*> split(node *v,unsigned k){
         
        if(!v)return pair<node*,node*>(NULL,NULL);

        //update(v);

        if( k <= size(v->left) ){
            pair<node*,node*> s = split( v->left, k );
            v->left = s.second;
            return make_pair( s.first , update(v) );
        }
 
        else{
            pair<node*,node*> s = split( v->right, k-size(v->left)-1 );
            v->right = s.first;
            return make_pair( update(v) , s.second );
        }
    }
 
    node *find(unsigned k){
        node *v=root;
        while(v){
            unsigned s = size(v->left);
            if( s > k ) v = v->left;
            else if( s == k )break;
            else{
                v = v->right;
                k -= s+1;
            }
        }
        return v;
    }
 
    void point_add( int k , T val ) { point_add( root , k , val ) ; }
    void point_add( node *v ,int k , T val ) {
        if( k < size( v->left ) ) point_add( v->left , k , val );
        else if( k > size( v->left ) ) point_add( v->right , k-size(v->left)-1 , val);
        else v->val += val, v->init = false ;
        update( v );
    }

    // 点更新
    void point_update(int k,T val){ point_update(root,k,val); }
    void point_update(node *v,int k,T val){
        if( k < size(v->left) )point_update(v->left,k,val);
        else if( k > size(v->left) )point_update(v->right,k-size(v->left)-1,val);
        else v->val = val, v->init = false ;
        update( v );
    }
 
    // [ l , r ) のクエリ
    int range_query( unsigned l , unsigned r , int Q ){

        T val;

        pair<node*,node*> R = split( root , r );
        pair<node*,node*> L = split( R.first , l );
        node *M = L.second;

        if( Q == 1 ) val = M->mini ;
        if( Q == 2 ) val = M->maxi ;
        if( Q == 3 ) val = M->sum  ;

        root = merge( merge( L.first , M ) , R.second );

        return val;
    }

    // 単位元の要素を先頭に追加　O( logn )
    void init_insert(){
        node *t = root;
        int k = 0;
        pair<node*,node*> s = split( t , k );
        t = merge( s.first , new node() );
        t = merge( t , s.second );
        root = update( t );
    }

    // k番目に要素を挿入　O( logn )
    void insert( unsigned k , T val ){ root = insert( root , k , val , xor128() ); }
    node *insert( node *t , unsigned k , T val , int pri ){
        pair<node*,node*> s = split(t,k);
        t = merge( s.first , new node(val,pri));
        t = merge( t , s.second );
        return update( t );
    }

    // k番目の要素の削除　O( logn )
    void erase(int k){ root = root->sz==1?NULL:erase( root, k );}
    node *erase(node *t, unsigned k){
        pair<node*,node*>u,v;
        u = split(t,k+1);
        v = split(u.first,k);
        t = merge(v.first,u.second);
        return update(t);
    }
 
    void range_erase(int l,int r){ root = range_erase( root , l , r );}
    node range_erase(node *t,unsigned k){
        pair<node*,node*>u,v;
    }

    // [L1,R1) [L2,R2) の２つの区間をswap O( logn )
    void range_swap( int L1 , int R1 , int L2 , int R2 ){

        pair<node*,node*> X1 = split( root     , R2 );
        pair<node*,node*> X2 = split( X1.first , L2 );
        pair<node*,node*> X3 = split( X2.first , R1 );
        pair<node*,node*> X4 = split( X3.first , L1 );
        node             *X5 = X4.first;

        root = merge( merge( merge( merge( X5 , X2.second ) , X3.second ) , X4.second ) , X1.second  );
    }

    // [ l , r )  区間を左に１ずらす O( logn )
    void circular_L_shift( int l , int r ){
        range_swap(l,l+1,l+1,r);
    }

    // [ l , r )  区間を左にKずらす O( logn )
    void circular_L_shift_K( int l , int r ){
        range_swap(l,l+1,l+1,r);
    }

    // [ l , r )　区間を右に１ずらす O( logn )
    void circular_R_shift( int l , int r ){
        range_swap(l,r-1,r-1,r);
    }

    // 配列に要素の挿入 O( logn )
    void push_back(T val){ insert(root?root->sz:0,val); }
    void pop_back(){ erase(root->sz-1); }
    void push_front(T val){ insert(0,val); }
    void pop_front(){ erase(0); }

    // 現在の配列を出力 O( n )
    void print_array(){
        int k = root->sz ;
        cout << "root value = " << root->val << endl ;
        cout << "size of array = " << k << endl ;
        for(int i = 0; i < k ; i++ ){
            if( i ) cout<<" ";
            cout << find(i)->val ;
        }
        cout << endl ;
    }

    // 現在の木の状態を出力 O( logn )
    void print_tree(){
        for(int i=0;i<root->sz;i++){
            cout << i << ' ' << endl;
            node *v = find( i );
            cout << "left = "  << ( !v->left?9:v->left->val )   << endl ;
            cout << "right = " << ( !v->right?9:v->right->val ) << endl ;
        }
    }
};
 
int main(){
    int n,q;
    cin>>n>>q;
    treap<int> tri(n);
    r(i,n){
        int a;
        scanf("%d",&a);
        tri.point_update(i,a);
    }
    while(q--){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        if(a==0){
            c++;
            tri.circular_R_shift(b,c);
        }
        else if(a==1){
            c++;
            cout<<tri.range_query(b,c,1)<<endl;
        }
        else{
            tri.point_update(b,c);
        }
        //tri.print_tree();
    }
}