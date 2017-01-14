#include<bits/stdc++.h>
using namespace std;

const int N = (int)1e5+11, LOGN = 20;
const int NL = N*LOGN;
int a[N];

int rootct,rtn[N],L[NL],R[NL],st[NL];

int insert(int p,int l,int r,int id){
	if(p<l || p>r)
		return id;
	int ID = rootct++;
	if(l==r){
		st[ID]=st[id]+1;
		return ID;
	}
	int m = (l+r)>>1;
	L[ID]=insert(p,l,m,L[id]);
	R[ID]=insert(p,m+1,r,R[id]);
	st[ID]=st[L[ID]]+st[R[ID]];
	return ID;
}

int qu(int k,int l,int r,int lid,int id){
	if(l==r){
		return l;
	}
	int nums = st[L[id]]-st[L[lid]];
	int m = (l+r)>>1;
	if(nums<k)
		return qu(k-nums,m+1,r,R[lid],R[id]);
	return qu(k,l,m,L[lid],L[id]);
}

int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	
	rtn[0]=rootct++;
	
	for(int i=1;i<=n;i++)
		rtn[i]=insert(a[i],1,N,rtn[i-1]);
	
	//printf("%d\n",qu(k,1,N,rtn[x-1],rtn[y]));
	return 0;
}
