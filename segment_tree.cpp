//Segment tree with lazy propagation
#include<bits/stdc++.h>
using namespace std;

const int N = int(1e5)+5;
int a[N],seg[N<<2],push[N<<2];

//build segment tree
void build(int l,int r,int id){
	if(l==r){ 
		seg[id]=a[l];
		return;
	}
	int m=(l+r)>>1;
	build(l,m,id<<1);
	build(m+1,r,id<<1|1); 
	seg[id]=seg[id<<1]+seg[id<<1|1]; 
}

//push lazy values
void pusher(int id){
	push[id<<1]+=push[id];
	push[id<<1|1]+=push[id];
	seg[id<<1]+=push[id];
	seg[id<<1|1]+=push[id];
	push[id]=0;
}

//range update from l to r
void update(int l,int r,int val,int L,int R,int id){
	if(L==R){
		push[id]+=val;
		seg[id]+=val;
		return;
	}
	if(L!=R && push[id])
		pusher(id);
	int m=(L+R)>>1;
	if(!(r<L || m<l))
		update(l,r,val,L,m,id<<1); 
	if(!(r<m+1 || R<l))
		update(l,r,val,m+1,R,id<<1|1); 

	seg[id]=seg[id<<1]+seg[id<<1|1]; 
}

//output from l to r 
int output(int l,int r,int L,int R,int id){
	if(l<=L && R<=r)
		return seg[id];
	if(L!=R && push[id])
		pusher(id);
	int m=(L+R)>>1;
	int x=0,y=0;
	if(!(r<L || m<l))
		x = output(l,r,L,m,id<<1);
	if(!(r<m+1 || R<l))
		y = output(l,r,m+1,R,id<<1|1);
	return x+y;
}

int main()
{
	int n,q;
	scanf("%d%d",&n,&q);
	for(int i=0;i<n;i++)
		scanf("%d",a+i);
	build(0,n-1,1);
	//cout<<output(x-1,y-1,0,n-1,1)<<endl;
	return 0;
}
