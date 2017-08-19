/* Auxiliary Tree */
#include<bits/stdc++.h>
using namespace std;

const int N = (int)1e5+11,LOGN= 20;
vector<int> g[N];
vector<pair<int,int> > aux[N];
int k,times[N],edg[N][2],wts[N],lev[N],dist[N],tme,ar[N],dep[N],dp[N][LOGN],vert[N];

bool cmp(int l,int r){
	return ar[l]<ar[r];
}

void dfs(int v,int l,int E){
	ar[v]=++tme,lev[v]=l;
	if(E!=-1) dp[v][0]=edg[E][0]^edg[E][1]^v;
	for(int i = 1;i<LOGN ;i++) dp[v][i]=dp[dp[v][i-1]][i-1];
	for(int i=0;i<g[v].size();i++){
		int e = g[v][i] ,w = v^edg[e][0]^edg[e][1];
		if(E^e)  dist[w]=dist[v]+wts[e] , dfs(w,l+1,e); 
	}
	dep[v]=++tme;
}

int lca(int u,int v){
	if(lev[u]>lev[v]) swap(u,v);
	int d = lev[v]-lev[u];
	for(int i=0;i<LOGN;i++) if((1<<i)&d) v = dp[v][i];
	if(u==v) return u;
	for(int i=LOGN-1;i>=0;i--) if(dp[u][i]!=dp[v][i]) u=dp[u][i], v = dp[v][i];
	return dp[u][0];
}

void aux_tree(){
	sort(vert,vert+k,cmp);
	int K = k;
	for(int i=0;i<K-1;i++){
		int LCA = lca(vert[i],vert[i+1]);
		if(times[LCA]) continue;
		vert[k++]=LCA;
		times[LCA]=1;
	}
	for(int i=K;i<k;i++) times[vert[i]]=0;
	sort(vert,vert+k,cmp);
	stack<int> S ;
	S.push(vert[0]);
	for(int i=1;i<k;i++){
		while(!(ar[S.top()]<ar[vert[i]] && dep[S.top()]>dep[vert[i]])) S.pop();
		aux[S.top()].push_back({vert[i],dist[vert[i]]-dist[S.top()]});
		S.push(vert[i]);
	}
//	while(!S.empty())S.pop(); // IF MLE
}

int main(){
	int n,t;
	cin>>n>>t;
	for(int i=0;i<n-1;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		edg[i][0]=u, edg[i][1]=v , wts[i]=w;
		g[u].push_back(i) , g[v].push_back(i);
	}
	dfs(1,0,-1);
	while(t--){
		scanf("%d",&k);
		int i,j;
		for(i=0,j=0;i<k;i++){
			scanf("%d",&vert[j]);
			times[vert[j]]++;
			if(times[vert[j]]==1) j++;
		}
		k=j;
		aux_tree();
		for(int i=0;i<k;i++){
			times[vert[i]]=0;
			aux[vert[i]].clear();
		}
	}
	return 0;
}
