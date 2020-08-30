#include <cstdio>

long long M[46];

int main(void){
	int n;
	scanf("%d",&n);
	M[0] = 0;
	M[1] = 1;
	for(int i = 2; i <= n; i++){
		M[i] = M[i-1] + M[i-2];
	}
	printf("%lld\n",M[n]);
	return 0;
}
