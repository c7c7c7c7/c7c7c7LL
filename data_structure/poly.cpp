#include <bits/stdc++.h>
#define rep(i,n) for(int i=0;i<n;i++)
using namespace std;
struct Poly {
  vector<int> c;
  Poly() : c(1, 1) {;}
  Poly(int s, int i) : c(s, i) {;}
  Poly(vector<int> v) {c = v;}
  int size() const { return c.size(); }
  void print(){
    int flag = 0;
    for(int i=size()-1;i>=1;i--){
      if( c[i] ){
        flag = 1;
        if( c[i] > 0 && i != size() - 1 ) cout<<'+';
        if( c[i] == -1 ) cout<<'-';
        else if( c[i] != 1 ) cout<<c[i];
        cout<<'x';
        if( i != 1 ) cout<<"^"<<i;
      }
    }
    if( c[0] ){
      if( flag && c[0] > 0 ) cout<<"+";
      cout<<c[0];
    }
    cout<<endl;
  }
  void normalize() {
    int s = 1;
    for (int i = size() - 1; i >= 0; i--)
      if (c[i] != 0) { s = i + 1; break; }
    c.resize(s);
  }
  int operator[](int idx) const {
    assert(idx >= 0 && idx < size());
    return c[idx];
  }
  int &operator[](int idx) {
    assert(idx >= 0 && idx < size());
    return c[idx];
  }
  Poly operator+(const Poly &c7) const {
    Poly ret = *this;
    ret.c.resize(max(size(), c7.size()));
    rep(i,c7.size()) ret[i] = ret[i] + c7[i];
    ret.normalize();
    return ret;
  }
  Poly operator-() const {
    Poly ret = *this;
    rep(i,ret.size()) ret[i] = -ret[i];
    return ret;
  }
  Poly operator-(const Poly &c7) const { return *this + (-c7); }
  Poly operator*(const Poly &c7) const {
    Poly ret(size() + c7.size(), 0);
    rep(i,size()) rep(j,c7.size()) ret[i+j] += c[i] * c7[j];
    ret.normalize();
    return ret;
  }
  Poly operator/(const Poly &c7) const { return divmod(c7).first; }
  Poly operator%(const Poly &c7) const { return divmod(c7).second; }
  Poly operator+=(const Poly &c7) { return *this = *this + c7; }
  Poly operator-=(const Poly &c7) { return *this = *this - c7; }
  Poly operator*=(const Poly &c7) { return *this = *this * c7; }
  Poly operator/=(const Poly &c7) { return *this = *this / c7; }
  Poly operator%=(const Poly &c7) { return *this = *this % c7; }
  void minus() {
    int g = abs(c.back());
    if (g > 0) {
      for (int j: c)
        if (j != 0) g = __gcd(g, abs(j));
      if (c.back() < 0) g = -g;
      for (int &j: c) j /= g;
    }
  }
  pair<Poly, Poly> divmod(const Poly &c7) const {
    int ls = size(), rs = c7.size(), s = ls - rs + 1;
    if (s < 0) { return make_pair(Poly(1, 0), *this); }
    Poly div(s, 0), rest = *this;
    assert(c7[rs-1] != 0);
    rep(i,s) {
      if (rest[ls-i-1] % c7[rs-1] != 0)      //
        for (auto &j: rest.c) j *= c7[rs-1]; //
      int d = rest[ls-i-1] / c7[rs-1];
      div[s - i - 1] = d;
      rep(j,rs) rest[ls-i-j-1] -= c7[rs-j-1] * d;
    }
    div.normalize(); rest.normalize();
    rest.minus(); //
    return make_pair(div, rest);
  }
  Poly pow(int power) const {
    Poly base = *this;
    Poly ret;
    while (power > 0) {
      if (power & 1) ret *= base;
      base *= base; power >>= 1;
    }
    return ret;
  }
  Poly differential() const {
    if (c.size() == 1) return Poly(1, 0);
    Poly ret(c.size() - 1, 0);
    for (int i = 1; i < (int)c.size(); ++i) ret[i-1] = c[i] * i;
    return ret;
  }
  int calc(int x) const {
    int ans = 0;
    for (int i = c.size() - 1; i >= 0; i--) ans *= x, ans += c[i];
    return ans;
  }
  Poly PolyGCD(Poly a, Poly b) {
    if (b.size() == 1 && b[0] == 0) { a.minus(); return a; }
    return PolyGCD(b, a % b);
  }
  Poly Poly_GCD(Poly a){
    Poly b=*this;
    return PolyGCD(a,b);
  }
};
struct Poly_parse{
  int p;
  string s;
  Poly g_A(){
    if(s[p]=='('){
      p++;
      Poly res = bnf1();
      p++;
      int num2=0;
      if(s[p]=='^'){
        p++;
        while('0'<=s[p]&&s[p]<='9') num2 = num2 * 10 + s[p++] - '0';
      }
      if(num2)res = res.pow(num2);
      return res;
    }
    else{
      int num = 0;
      while('0'<=s[p]&&s[p]<='9') num = num * 10 + s[p++] - '0';
      if( p <s.size() && s[p] == 'x' ){
        if(num==0) num = 1;
        p++;
        int num2 = 0;
        vector<int>v;
        if(p<s.size()&&s[p]=='^'){
          p++;
          while('0'<=s[p]&&s[p]<='9') num2 = num2 * 10 + s[p++] - '0';
        }
        if(num2==0){
          v.resize(2,0);
          v[1]=num;
          Poly res(v);
          return res;
        }
        else{
          v.resize(num2+1,0);
          v[num2] = num;
          Poly res(v);
          return res;
        }
      }
      else{
        Poly res(1,num);
        return res;
      }
    }
  }
  Poly bnf2(){
    Poly res=g_A();
    while(p<s.size()&&s[p]=='*'){
      int t=p++;
      if(s[t]=='*')res = res*g_A();
    }
    return res;
  }
  Poly bnf1(){
    Poly res=bnf2();
    while(p<s.size()&&s[p]=='+'||s[p]=='-'){
      int t=p++;
      if(s[t]=='+')res = res+bnf2();
      if(s[t]=='-')res = res-bnf2();
    }
    return res;
  }
  string convert(string ss){
    for(int i=0;i<(int)ss.size()-1;i++){
      if(ss[i+1]=='('&&!(ss[i]=='+'||ss[i]=='-'||ss[i]=='*')){
        ss= ss.substr(0,i+1)+'*'+ss.substr(i+1);
      }
    }
    if(ss[0]=='-'){
      ss="0"+ss;
    }
    return ss;
  }
  Poly parse(string x){
    s=convert(x);
    p=0;
    return bnf1();
  }
};

int main(){
  string s;
  Poly_parse A;
  while(cin>>s,s!="."){
    Poly a=A.parse(s);
    cin>>s;
    Poly b=A.parse(s);
    Poly c=a.Poly_GCD(b);
    c.print();
  }
}
