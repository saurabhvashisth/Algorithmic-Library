// Trie operation insert, delete, find
#include<bits/stdc++.h>
using namespace std;

const int N = (int)1e5+5,SZ = (int)12;
int a[N],n,trie[N*SZ][SZ],cnt[N*SZ],id;

//SZ =  character set size 

// return no of occurances of num in trie
int find(int num){
	int idd=0;
	for(int i=SZ;i>=0;i--){
		int next = ((1<<i)&num)>>i;
		idd=trie[idd][next];
		if(idd==0 || cnt[idd]==0)
			return 0;
	}
	return cnt[idd];
}

// inserts ct occurances of num in trie
void insert(int num,int ct){
	int idd=0;
	cnt[idd]+=ct;
	for(int i=SZ;i>=0;i--){
		int next = ((1<<i)&num)>>i;
		if(!trie[idd][next])
			trie[idd][next]=++id;
		idd=trie[idd][next];
		cnt[idd]+=ct;
	}
}

//deletes ct occurances of num from trie
//evaluate find , before deleting
void del(int num,int ct){
	int idd=0;
	cnt[idd]-=ct;
	for(int i=SZ;i>=0;i--){
		int next = ((1<<i)&num)>>i;
		if(!trie[idd][next])
			trie[idd][next]=++id;
		idd=trie[idd][next];
		cnt[idd]-=ct;
	}
}

int main()
{
	return 0;
}
