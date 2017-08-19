/* Sparse Table */
#include<bits/stdc++.h>
using namespace std;
const int N = (int)1e5+11,LOGN = 20;
int SP[N][LOGN],a[N],n; // SP[i][j] stores the minimum value from i to i+2^j-1.

void build(void){
	for(int i=0;i<n;i++) SP[i][0]=a[i];
	for(int j=1;j<LOGN;j++){
		for(int i=0;i<n && i+(1<<j)-1<n;i++){
			SP[i][j]=min(SP[i][j-1],SP[i+(1<<(j-1))][j-1]);
		}
	}
}

int RMQ(int x,int y){
	int k = log2(y-x+1);
	return min(SP[x][k],SP[y-(1<<k)+1][k]);
}

int main(){
	cin>>n;
	for(int i=0;i<n;i++) cin>>a[i];
	build();
	cout<<RMQ(0,n-1)<<endl;
	return 0;
}
