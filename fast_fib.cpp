// nth fibonacci in log(n) time in O(1) space
#include<bits/stdc++.h>
using namespace std;

const int N = (int)1e5+11,mod=(int)1e9+7;

void fib(long long  n, long long &x, long long &y){
    if(n==0){
        x = 0;
        y = 1;
        return ;
    }
     
    if(n&1){
        fib(n-1, y, x);
        y=(y+x)%mod;
    }else{
        long long  a, b;
        fib(n>>1, a, b);
        y = (a*a+b*b)%mod;
        x = (a*b + a*(b-a+mod))%mod;
    }
}

int main()
{
	int t;
	cin>>t;
	for(int i=0;i<t;i++){
		long long int n,x,y;
		scanf("%lld",&n);
		fib(n,x,y);
		printf("%lld\n",x);
	}
	return 0;
}
