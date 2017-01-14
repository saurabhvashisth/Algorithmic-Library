// Generating Bridge tree of a graph
#include<bits/stdc++.h>
using namespace std;

const int N = (int)1e5+11;

vector<int> g[N],t[N]; //adjacency list of graph and bridge tree
vector<pair<int,int> > edg; // edge list of graph
int ar[N],tme=1,n,m,cmpno=1,cmpos[N],tree[N],cm=1,vis[N]; //cmpno = no of components, 
bool isb[N];

// cmpos = to which component node belongs to 
// tree = to which bride tree node , a node belongs to

int dfs(int v,int E){
	vis[v]=1;
	ar[v]=tme++;
	cmpos[v]=cmpno;
	int dbe = ar[v];
	for(int e:g[v]){
		int w = v==edg[e].first?edg[e].second:edg[e].first;
		if(!vis[w])
			dbe=min(dbe,dfs(w,e));
		else if(E!=e)
			dbe=min(dbe,ar[w]);
	}
	if(dbe==ar[v] && E!=-1)
		isb[E]=1;
	return dbe;
}

void compress(int v){
	vis[v]=1;
	for(int e:g[v]){
		int w = v==edg[e].first?edg[e].second:edg[e].first;
		if(!vis[w]){
			if(!isb[e])
				tree[w]=tree[v];
			else{
				cm++;
				t[tree[v]].push_back(cm);
				t[cm].push_back(tree[v]);
				tree[w]=cm;
			}
			compress(w);
		}
	}
}

int main()
{
	cin>>n>>m;
	for(int i=0;i<m;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		edg.push_back({u,v});
		g[u].push_back(i);
		g[v].push_back(i);
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			dfs(i,-1);
			cmpno++;
		}
	}
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			tree[i]=cm;
			compress(i);
			cm++;
		}
	}
	return 0;
}
