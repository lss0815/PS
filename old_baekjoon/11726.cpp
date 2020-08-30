#include <cstdio>

using namespace std;

int M[1001], mod = 10007;

int main(void){
	int n;
	scanf("%d",&n);
	M[0] = 1;
	M[1] = 1;
	for(int i = 2; i <= n; i++){
		M[i] = M[i-1] + M[i-2];
		M[i] %= mod;
	}
	printf("%d\n",M[n]);
	return 0;
}
