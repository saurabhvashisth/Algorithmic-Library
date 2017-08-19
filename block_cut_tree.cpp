#include <bits/stdc++.h>
using namespace std;

const int N = 2e5+5;//400005;
const int LOGN = 20;

int low[4*N], E[2*N][2], Cno, C[4*N], BCC[4*N], E_BCC[4*N], BCno, ar[4*N], T, isA[N];
vector<int> g[4*N],t[4*N],S;
bool vis[4*N];

void Gdfs(int v, int p){
	vis[v] = 1;
	low[v] = ar[v] = ++T;
	C[v] = Cno;
	for (int i = 0; i < g[v].size(); i++){
		int e = g[v][i];
		int w = E[e][0] ^ E[e][1] ^ v;
		if(!vis[w]){
			S.push_back(e);
			Gdfs(w, v);	
			int tmplow = low[w];
			low[v] = min (low[v], tmplow);
			if (ar[v] <= tmplow){
				if (i || ar[v]^1)  isA[v] = 1;
				BCno++;
				while (!S.empty()){
					int ee = S.back();
					E_BCC[ee] = BCno;
					S.pop_back();
					if (ee == e) break;
				}
			}
		}
		else if(w != p) {
			low[v] = min (low[v], ar[w]);
			S.push_back(e);
		}
	}
}

void compress(int n){
	for (int i = 1; i <= n; i++){
		vector<int> tmpe;
		for (int e: g[i]) tmpe.push_back(E_BCC[e]);
		sort(tmpe.begin(), tmpe.end());
		tmpe.erase(unique(tmpe.begin(),tmpe.end()),tmpe.end());
		if (isA[i]){
			BCno++;
			BCC[i] = BCno;
			for (int v: tmpe){
				t[v].push_back(BCC[i]);
				t[BCC[i]].push_back(v);
			}
		}
		else if (tmpe.size())  BCC[i] = tmpe[0];
		else { 
			BCno++;
			BCC[i] = BCno; 
		}
	}
}

int main(){
	int n, m;
	scanf("%d%d",&n,&m);
	for (int i = 0; i < m; i++){
		int u, v; scanf("%d%d",&u,&v);
		E[i][0] = u, E[i][1] = v;
		g[u].push_back(i);
		g[v].push_back(i);
	}
	for (int i = 1; i <= n; i++){
		if (!vis[i]) {
			Cno++;
			T = 0;
			Gdfs(i, -1);
		}
	}
	compress(n);
}
