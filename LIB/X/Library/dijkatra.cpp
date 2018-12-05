#define INF 1<<28
struct edge {int to,cost;};
typedef pair<int,int>P;
int V;
vector<edge>G[MAX_V];
int d[MAX_V];
void dijkstra(){
	priority_queue<P,vector<P>,greater<P>>que;
	fill(d,d+V,INF);
	d[s]=0;
	que.push(P(0,s));
	while(!que.empty()){
		P p=que.top;que.pop;
		int v=p.second;
		if(d[v]<p.firsst)continue;
		for(int i=0;i<G[v].size();i++){
			edge e=G[v][i];
			if(d[e.to]>d[v]+e.cost){
				d[e.to]=d[v]+e.cost;
				que.push(P(d[e.to],e.to));
			}
		}
	}
}
