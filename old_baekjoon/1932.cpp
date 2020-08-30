#include <cstdio>
#include <algorithm>

using namespace std;


int M[500][500];

int main(void){
	int n;
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		for(int j=0; j<=i; j++){
			scanf("%d",&M[i][j]);
		}
	}
	for(int i=n-2; i>=0; i--){
		for(int j=0; j<=i; j++){
			M[i][j] += max(M[i+1][j], M[i+1][j+1]);
		}
	}
	printf("%d\n",M[0][0]);
	return 0;
}
