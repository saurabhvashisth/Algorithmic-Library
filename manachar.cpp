//Manachar's Algorithm for Longest Palindromic substring in O(n)

#include<bits/stdc++.h>
using namespace std;

const int N = (int)2e5+11;

int P[N];
int main(){
	string s;
	cin>>s;
	int n = s.size();
	string b = "#";
	
	for(int j=0;j<n;j++){
		string c(1,s[j]);
		b+=c+"#";
	} // pad the string with # for even length palindromes
	int C=0,R=0; //center , rightmost pointer
	int maxval = 0, indx;
	for (int j = 0; j < 2*n+1; j++) {
		int i_mirror = 2*C-j;
		if(R>j) //because when j>R => wrong values 
			P[j] = min(R-j+1, P[i_mirror]);

		while( j+P[j]<2*n+1 && j-P[j]>=0 && b[j+P[j]]==b[j-P[j]]) //expanding the palindrome about the center j 
			P[j]++;

		if(j+P[j]-1>R){ //when rightmost palindromic pointer changes update center and right pointer
			C=j;
			R=j+P[j]-1;
		}
		if(P[j]>maxval){
			maxval = P[j];
			indx = j;
		}
	}
	/* Length of Max Palin : maxval - 1; */
	/* Center of Max Palin : indx; */
	/* Starting index of Max Palin : indx/2 - (maxval-1)/2; */ 
	return 0;
}
