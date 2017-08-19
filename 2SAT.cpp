#include<bits/stdc++.h>
using namespace std;

const int N = 211196;
vector<int> order,g[N],rg[N],cmpno[N];
int curr,compo[N],vis[N],value[N];

void dfs1(int v) {
	vis[v]=1;
	for (auto w:g[v]) if(!vis[w]) dfs1(w);
	order.push_back(v);
}

void dfs2(int v){
	vis[v] = 1 , compo[v]=curr;
	cmpno[curr].push_back(v);
	for (auto w:rg[v]) if(!vis[w]) dfs2(w);
}

void SCC(int vars) {
	for (int i = 0; i < vars; i++)  if(!vis[i]) dfs1(i);
	reverse(order.begin(),order.end());
	memset(vis,0,sizeof(vis));
	for(auto w:order) {
		if(!vis[w]) {
			dfs2(w);
			curr++;
		}
	}
}

void assign(void){
	memset(value,-1,sizeof(value));
	for (int i = 0; i < curr; i++) {
		for (auto w:cmpno[i]) {
			if (value[w>>1]!=-1) break;
			value[w>>1] = w&1?1:0;
		}
	}
}

bool solve(int v){
	SCC(2*v);
	for (int i = 0; i < v; i++) if (compo[i<<1] == compo[i<<1^1]) return false;
	/* assign(); */
	return true;
}

// If there are equiv and xor , we just need to 
// find if x and ~x exists in same component or not
// as x -> y && y -> x will always exist
void add_edge(int x,int y) { g[x].emplace_back(y), rg[y].emplace_back(x);}
void add_imp(int x,int y) { add_edge(x,y), add_edge(y^1,x^1);} 
void add_equiv(int x,int y) { add_imp(x,y) , add_imp(y,x); }
void add_or(int x,int y){ add_imp(x^1,y);}
void add_xor(int x,int y) { add_or(x,y) , add_or(x^1,y^1); }
void add_true(int x) { add_edge(x^1,x); }
void add_and(int x,int y) { add_true(x), add_true(y);}

int main(){
	//solve(n);
	return 0;
}
