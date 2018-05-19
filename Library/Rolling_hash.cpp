typedef unsigned long long ull;
const ull M=1000000007;
//aにbが含まれるか
bool Rolling_hash(string a,string b){
  int a1=a.length(),b1=b.length();
  if(a1>b1)return false;
  ull t=1;
  for(int i=0;i<a1;i++)t*=M;
  ull ah=0,bh=0;
  for(int i=;i<a1;i++)ah=ah*M+a[i];
  for(int i=0;i<a1;i++)bh=bh*M+b[i];
  for(int i=0;i+a1<=b1;i++){
    if(ah==bh)return true;
    if(i+a1<b1)bh=bh*B+b[i+a1]-b[i]*t;
  }
  return false;
}
//ハッシュテーブルの生成
void Roliha(string &s){
  ull B=1000000007;
  int sz=s.size();
  hashh.assign(sz+1,0);
  power.assign(sz+1,0);
  power[0]=1;
  for(int i=1;i<=sz;i++)power[i]=power[i-1]*B;
  for(int i=1;i<=sz;i++)hashh[i]=(hashh[i-1]+s[i-1])*B;
}
//ハッシュの取得
ull get_hash(int l,int r){return hashh[r]-hashh[l]*power[r-l];}