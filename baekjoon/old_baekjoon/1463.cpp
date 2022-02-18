#include <stdio.h>
#include <iostream>

int INF = 987654321;
int A[1000001];

int min_proc(int);

int main(){
	int n, result = 0;
	scanf("%d",&n);
	printf("%d\n",min_proc(n));
}

int min_proc(int a){
	for(int i=0; i<=a; i++)A[i]=INF;
	A[1]=0;
	for(int i=1; i<a; i++){
		if(i*3<=a)A[i*3]=std::min(A[i]+1,A[i*3]);
		if(i*2<=a)A[i*2]=std::min(A[i]+1,A[i*2]);
		A[i+1]=std::min(A[i]+1,A[i+1]);
	}
	return A[a];
}
