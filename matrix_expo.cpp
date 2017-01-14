#include<bits/stdc++.h>
using namespace std;

const int MOD = (int)1e9+7;

void mul(long long  a[][2],long long  b[][2],long long c[][2])//multiply matrix a and b. put result in c
{
    int i,j,k;
    for(i=0;i<2;i++){
        for(j=0;j<2;j++){
            c[i][j]=0;
            for(k=0;k<2;k++){
                c[i][j]+=(a[i][k]*b[k][j]);
                c[i][j]=c[i][j]%MOD;
            }
        }
    }
}

void matpow(long long Z[][2],long long n,long long ans[][2])
//find ( Z^n )% M and return result in ans
{
    long long temp[2][2];
    //assign ans= the identity matrix
    ans[0][0]=1;
    ans[1][0]=0;
    ans[0][1]=0;
    ans[1][1]=1;
    int i,j;
    while(n){
        if(n&1LL){
            mul(ans,Z,temp);
            for(i=0;i<2;i++)
                for(j=0;j<2;j++)
                    ans[i][j]=temp[i][j];
        }
        mul(Z,Z,temp);
        for(i=0;i<2;i++)
            for(j=0;j<2;j++)
                Z[i][j]=temp[i][j];
        n>>=1LL;
    }
    return;
     
}

long long mat_expo(long long n){
    long long fib;
    if(n>2){
        long long int Z[2][2]={{1,1},{1,0}},result[2][2];//modify matrix a[][] for other recurrence relations
        matpow(Z,n-2LL,result);
        fib = (result[0][0]*1 + result[0][1]*0)%MOD;    //final multiplication of Z^(n-2) with the initial terms of the series
    }
    else
        fib=n-1LL;
    return fib;
}

int main(){
	int n;
	long long t;
	cin>>n;
	for(int i=0;i<n;i++){
		scanf("%lld",&t);
		cout<<mat_expo(t+1)<<endl;
	}
	return 0;
}


