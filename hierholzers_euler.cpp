#include <bits/stdc++.h>
using namespace std;
const int N = 1e5, M = 5e5;

// Algorithm to find the euler path/circuit of a undirected graph
// For path, if 2 odd deg nodes then choose one else no path exits
// For circuit, if odd deg nodes exists then no circuit exists , choose any random vertex
// Check for graph connectivity

vector<int> g[N],path;
int dsu[N],ranks[N],edg[N][2],n,m,deg[N],vis[M];

void mrg(int u,int v) {
	if (ranks[u] <= ranks[v]) dsu[u] = v, ranks[v] += ranks[u];
	else mrg(v,u);
}

int F(int v) {
	int p = dsu[v];
	while(p) p = dsu[v = p];
	return v;
}

bool checkEuler (int var) {
	for (int i=0;i<m;i++) {
		int u = F(edg[i][0]), v = F(edg[i][1]);
		if(u!=v) mrg(u,v);
	}
	int hd = F(1), ct = 0;
	for (int i=1;i<=n;i++) {
		if (deg[i]&1) ct++;
		if (F(i) != hd)
			return false;
	}
	if (var && ct!=2)return false;
	if (!var && ct) return false;
	return true;
}


void findEuler (int var) {
	int cur = 1;
	if (var) {
		for (int i=1;i<=n;i++)
			if(deg[i]&1) {
				cur = i;
				break;
			}
	}
	stack<int> cur_path;
	cur_path.push(cur);
	
	while (!cur_path.empty()) {
		if (deg[cur]) {
			int e = g[cur].back();
			g[cur].pop_back();
			if (vis[e]) continue;
			vis[e] = 1;
			deg[edg[e][0]]--, deg[edg[e][1]]--;
			cur ^= edg[e][0]^edg[e][1];
			cur_path.push(cur);
			} else {
			cur = cur_path.top();
			path.push_back(cur);
			cur_path.pop();
		}
	}
}

int main() {
	cin >> n >> m;
	for (int i=1;i<=n;i++) ranks[i] = 1;
	for (int i=0;i<m;i++) {
		cin >> edg[i][0] >> edg[i][1];
		g[edg[i][0]].push_back(i);
		g[edg[i][1]].push_back(i);
		deg[edg[i][0]]++ , deg[edg[i][1]]++;
	}
	if(checkEuler(0)) { // 1 for path , 0 for circuit 
		findEuler(0); // 1 for path , 0 for circuit
		for (int i=0;i<path.size();i++)
			cout << path[i] << " ";
		cout << endl;
	}
	else 
		puts("Not Possible");
	return 0;
}
