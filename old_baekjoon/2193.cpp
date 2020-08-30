#include <cstdio>

long long M[91];

int main(void){
	int n;
	scanf("%d",&n);
	M[0] = 1;
	M[1] = 1;
	for(int i = 2; i <= n; i++){
		M[i] = 0;
		for(int j = 2; i-j >=0; j++){
			M[i] += M[i-j];
		}
	} 
	printf("%lld\n",M[n]);
	return 0;
}
