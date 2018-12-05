#include <bits/stdc++.h>
#define r(i,n) for(int i=0;i<n;i++)
using namespace std;
typedef pair<int,int>P;
typedef pair<int,P>P2;

struct PrimalDual{
  const int INF = 1<<28;
  typedef pair<int,int> P;
  struct edge{
    int to,cap,cost,rev;
    edge(){}
    edge(int to,int cap,int cost,int rev):to(to),cap(cap),cost(cost),rev(rev){}
  };

  int n,ans;
  vector<vector<edge> > G;
  vector<int> h,dist,prevv,preve,D;

  PrimalDual(){}
  PrimalDual(int sz):n(sz),G(sz),h(sz),dist(sz),prevv(sz),preve(sz),D(sz){ans=0;}
  
  void add_edge(int from,int to,int cap,int cost){
    if(cost<0){
      D[from]-=cap;
      D[to]+=cap;
      ans-=cost;
      G[from].push_back(edge(to,0,cost,G[to].size()));
      G[to].push_back(edge(from,cap,-cost,G[from].size()-1));
    }
    else{
      G[from].push_back(edge(to,cap,cost,G[to].size()));
      G[to].push_back(edge(from,0,-cost,G[from].size()-1));
    }
  }

  int flow(int s,int t,int f){ cout<<ans<<endl;

    if(ans){
      D[s]+=f;
      D[t]-=f;
      f=0;
      for(int i=0;i<n;i++){//cout<<D[i]<<endl;
        if(D[i]>0){
          f+=D[i];
          add_edge(n-2,i,D[i],0);
        }
        if(D[i]<0){
          add_edge(i,n-1,-D[i],0);
        }
      }
      cout<<f<<endl;
      s=n-2;
      t=n-1;
    }

    int res=0;
    fill(h.begin(),h.end(),0);
    while(f>0){
      priority_queue<P,vector<P>,greater<P> > que;
      fill(dist.begin(),dist.end(),INF);
      dist[s]=0;
      que.push(P(0,s));
      while(!que.empty()){
        P p=que.top();que.pop();
        int v=p.second;
        if(dist[v]<p.first) continue;
        for(int i=0;i<(int)G[v].size();i++){
          edge &e=G[v][i];
          if(e.cap>0&&dist[e.to]>dist[v]+e.cost+h[v]-h[e.to]){
            dist[e.to]=dist[v]+e.cost+h[v]-h[e.to];
            prevv[e.to]=v;
            preve[e.to]=i;
            que.push(P(dist[e.to],e.to));
          }
        }
      }
      if(dist[t]==INF) return -1;
      for(int v=0;v<n;v++) h[v]+=dist[v];
      int d=f;
      for(int v=t;v!=s;v=prevv[v]){
        d=min(d,G[prevv[v]][preve[v]].cap);
      }
      f-=d;
      res+=d*h[t];
      for(int v=t;v!=s;v=prevv[v]){
        edge &e=G[prevv[v]][preve[v]];
        e.cap-=d;
        G[v][e.rev].cap+=d;
      }
    }
    if(ans)return res-ans;
    return res;
  }
};

int dx[]={0,1,0,-1};
int dy[]={-1,0,1,0};
int D[4];
int H=10,W=19;
char c[]={'U','R','D','L'};
map<char,int>M;
int GRI[11][20][6];
P2 GGR[11*20*6*2];


int X[10],Y[10],N;
bool USED[13][23][4];

int cc=0;

struct MAP{
    char s[11][20];
    bool used[11][20];
    int score;
    MAP(){
        memset(used,0,sizeof(used));
        score=0;
    }
    void init(){
        r(i,H)r(j,W){
            if(isalpha(s[i][j]))used[i][j]=1;
            if(s[i][j]=='#')used[i][j]=1;
        }
    }
    int calc_score(){
        int sco=0;
        unordered_set<int>st,stt;
        r(i,1){
            i=cc;
            st.clear();
            memset(USED,0,sizeof(USED));
            int x=X[i],y=Y[i],d=D[i];
            USED[y][x][d]=1;
            while(1){
                if(isalpha(s[y][x])){
                    d=M[s[y][x]];
                }
                x+=dx[d]+W; x%=W;
                y+=dy[d]+H; y%=H;
                if(USED[y][x][d])break;
                USED[y][x][d]=1;
                if(s[y][x]=='#')break;
                //st.insert((y<<10)|x);
                stt.insert((y<<10)|x);
                if(cc)st.insert((y<<10)|x|(d<<20));
                else st.insert((y<<10)|x);
            }
            //sco+=st.size();
        }
        sco+=stt.size();
        score=sco;
        return sco;
    }
};

void Input(MAP &A);
void SCORE(MAP &A,MAP &ANS);
void UPDATE(MAP &A,MAP &ANS);
void UPDATE2(MAP &A,MAP &ANS);
void PRIN(MAP &ANS);
void make_graph(int idx,MAP &A);

int main(){
    MAP A;
    Input(A);
    MAP ANS;
    make_graph(0,A);
    ANS=A;
    r(i,H){
      r(j,W){
        cout<<ANS.s[i][j];
      }
      cout<<endl;
    }
    r(i,H)r(j,W){
        if(isalpha(ANS.s[i][j])){
            cout<<j<<' '<<i<<' '<<ANS.s[i][j]<<' ';
        }
    }
    cout<<endl;
}

void make_graph(int idx,MAP &A){
  PrimalDual p(19*10*6+5);
  int n=19*10*6+5;
  int S=19*10*6+1;
  int T=19*10*6+2;
  for(int i=0;i<H;i++){
    for(int j=0;j<W;j++){
      if(A.s[i][j]=='#')continue;
      //if(i==Y[idx]&&j==X[idx])continue;

      if(isalpha(A.s[i][j])){

        int d=M[A.s[i][j]];
        int y=(i+dy[d]+H)%H;
        int x=(j+dx[d]+W)%W;
        int from=GRI[i][j][d];

        if(A.s[y][x]=='#')continue;

        int dd=d;
        if(isalpha(A.s[y][x]))dd=M[A.s[y][x]];
        int to=GRI[y][x][dd];
        int to2=GRI[y][x][5]; //cout<<y<<endl;
        //p.add_edge(from,to,1,-1);
        p.add_edge(from,to2,1,-1);

      }

      else{
        r(d,4){
          int y=(i+dy[d]+H)%H;
          int x=(j+dx[d]+W)%W;
          int from=GRI[i][j][d];

          if(A.s[y][x]=='#')continue;

          int dd=d;
          if(isalpha(A.s[y][x]))dd=M[A.s[y][x]];
          int to=GRI[y][x][dd];
          int to2=GRI[y][x][5]; 
          //p.add_edge(from,to,1,-1);
          p.add_edge(from,to2,1,-1);

        }
      }

      int U=GRI[i][j][5];
      int V=GRI[i][j][4];
      p.add_edge(U,V,1,0);
      if(isalpha(A.s[i][j])){
        int dd=M[A.s[i][j]];
        r(d,4){
          if(d!=dd)continue;
          int to=GRI[i][j][d]; //cout<<V<<' '<<to<<endl;
          p.add_edge(V,to,1,0);
        }
      }
      else{
        r(d,4){
          int to=GRI[i][j][d]; //cout<<V<<' '<<to<<endl;
          p.add_edge(V,to,1,0);
        }
      }
    }
  }

  for(int i=0;i<H;i++){
    for(int j=0;j<W;j++){
      if(A.s[i][j]=='#')continue;
      int d=4;
      int to=GRI[i][j][d];
      p.add_edge(to,T,1,0);
    }
  }

  int fro=GRI[Y[idx]][X[idx]][5]; // cout<<D[idx]<<endl;

  p.add_edge(S,fro,1,0);

  int x=p.flow(S,T,1);
//15+8
  r(i,n){
    int f=0;
    P2 pp=GGR[i];
    int y=pp.first;
    int x=pp.second.first;
    int k=pp.second.second;
    if(A.s[y][x]=='#')continue;
    if(A.s[y][x]=='.'||A.s[y][x]))continue;
    //cout<<y<<' '<<x<<' '<<k<<endl;
    if(k==4||k==5)continue;
    int yy,xx,DD;
    r(j,p.G[i].size()){
      //if(p.G[i].size()==4){
      if(p.G[i][j].cap==0){
        int XX=p.G[i][j].to;
        P2 ppp=GGR[XX];//f++;
        yy=ppp.first;
        xx=ppp.second.first;
        DD=ppp.second.second;
        if(DD!=5)continue;
        f++;
        cout<<y<<' '<<x<<' '<<k<<' '<<yy<<' '<<xx<<' '<<DD<<' '<<' '<<p.G[i][j].cap<<endl;
      //}
      }
    }
    if(f){
      A.s[y][x]=c[k];
      cout<<y<<' '<<x<<' '<<k<<endl;
    }
  }

  cout<<x<<endl;
}





void SCORE(MAP &A,MAP &ANS){
    int score=A.calc_score();
    if(ANS.score<=score){
        ANS=A;
    }
}

void PRIN(MAP &ANS){
    r(i,H){
        r(j,W)cout<<ANS.s[i][j];
        cout<<endl;
    }
}

void Input(MAP &A){
    M['U']=0;
    M['R']=1;
    M['D']=2;
    M['L']=3;
    r(i,H)scanf("%s",&A.s[i]);
    /*r(i,H){
        r(j,W){
            if(A.s[i][j]!='.')continue;
            int cc=0,d;
            r(k,4){
                int y=(i+dy[k]+H)%H;
                int x=(j+dx[k]+W)%W;
                if(A.s[y][x]=='.'||isalpha(A.s[y][x])){
                    cc++;
                    d=k;
                }
            }
            //PRIN(A);
            if(cc==1)A.s[i][j]=c[d];
            //PRIN(A);
        }
    }*/
    A.init();
    cin>>N;
    r(i,N){
        char d;
        cin>>X[i]>>Y[i]>>d;
        if(d=='U')D[i]=0;
        if(d=='R')D[i]=1;
        if(d=='D')D[i]=2;
        if(d=='L')D[i]=3;
    }
    r(i,H)r(j,W){
      int x=i*W+j;
      int y=x*6;
      r(k,6){
        GRI[i][j][k]=y+k;
      }
    }
    r(i,H*W*6+10){
      r(a,H)r(b,W)r(k,6){
        if(GRI[a][b][k]==i)GGR[i]=P2(a,P(b,k));
      }
    }
}