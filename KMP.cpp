/* KMP String Matching Algorithm */
#include<bits/stdc++.h>
using namespace std;

const int N = (int)1e5+11;
string txt,pat;
int lps[N];

void preprocess(void){
	int len=0,i=1,m=pat.size();
	while(i<m){
		while(i<m && pat[i]==pat[len]) lps[i++] = ++len;
		if(i<m) len?len=lps[len-1]:i++;
	}
}

void KMP(void){
	int m = pat.size() , n = txt.size();
	preprocess();
	int i=0,j=0;
	while(i<n){
		while(i<n && j<m && pat[j]==txt[i]) j++ , i++;
		if(j==m) j = lps[j-1] , cout<<i-m<<endl; //pattern at i-m
		else if(i<n) j?j=lps[j-1]:i++;
	}
}

int main()
{
	cin>>txt>>pat;
	KMP();
	return 0;
}
