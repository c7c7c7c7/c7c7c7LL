#include <bits/stdc++.h>
using namespace std;
#define r(i,n) for(int i=0;i<n;i++)


typedef pair<int,int>P;
typedef pair<int,P>P3;
P3 next_day(int y,int m,int d){
  int f=0;
  int uru=0;
  if( y&400==0 || ( y%4==0 && y%100!=0) ) uru=1;
  if( m==1  && d==31)f++;
  if( ( uru==0 && m==2  && d==28) || ( uru==1 && m==2  && d==29) )f++;
  if( m==3  && d==31)f++;
  if( m==4  && d==30)f++;
  if( m==5  && d==31)f++;
  if( m==6  && d==30)f++;
  if( m==7  && d==31)f++;
  if( m==8  && d==31)f++;
  if( m==9  && d==30)f++;
  if( m==10 && d==31)f++;
  if( m==11 && d==30)f++;
  if( m==12 && d==31)f++;

  if(!f)return P3(y,P(m,d+1));

  if( m==12 )return P3(y+1,P(1,1));
  else return P3(y,P(m+1,1));
}

int main(){
  int y,m,d;
  scanf("%d/%d/%d",&y,&m,&d);
  while(1){
    if(y%m==0&&(y/m)%d==0){
      printf("%d/%02d/%02d\n",y,m,d);
      break;
    }
    P3 p=next_year(y,m,d);
    y=p.first;
    m=p.second.first;
    d=p.second.second;
  }
}