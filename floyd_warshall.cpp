#include<stdio.h>
const int N = 50;
const long long INF = (long long)1e17;
long long dist[N][N];

//INITIALIZE DIST WITH INF AND WEIGHTS
//negative cycles => at least 1 negative diagonal 
void floydWarshall(int n){
	for (int k = 1; k <= n; k++){
		for (int i = 1; i <= n; i++){ 
			for (int j = 1; j <= n; j++)
				if (dist[i][k] + dist[k][j] < dist[i][j]) 
					dist[i][j] = dist[i][k] + dist[k][j];
		}
	}
}

int main(){
	int n;
	floydWarshall(n);
	return 0;
}
