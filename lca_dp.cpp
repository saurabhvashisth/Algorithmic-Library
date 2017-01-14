#include<bits/stdc++.h>
using namespace std;

const int N = (int)1e5+11,LOGN=18;
vector<int> t[N];
int dp[N][LOGN],n,level[N];

void build_dp(void){
	for(int i=1;i<=LOGN;i++){
		for(int j=1;j<=n;j++)
			dp[j][i]=dp[dp[j][i-1]][i-1];
	}
}

void dfs(int v,int p){
	dp[v][0]=p;
	level[v]=1+level[p];
	for(int w:t[v]){
		if(w!=p)
			dfs(w,v);
	}
}

int lca(int u,int v){
	if(level[u]>level[v])
		swap(u,v);
	int d = level[v]-level[u];
	for(int i=0;i<=LOGN;i++){
		if(d&(1<<i))
			v=dp[v][i];
	}
	if(v==u)
		return v;
	for(int i=LOGN;i>=0;i--){
		if(dp[v][i]!=dp[u][i]){
			v=dp[v][i];
			u=dp[u][i];
		}
	}
	return dp[u][0];
}

int main()
{
	cin>>n;
	for(int i=0;i<n-1;i++){
		int u,v;
		scanf("%d%d",&u,&v);
		t[u].push_back(v);
		t[v].push_back(u);
	}
	dfs(1,0);
	build_dp();
	return 0;
}
