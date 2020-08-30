#include <cstdio>
#include <queue>
#include <cstring>

using namespace std;

int main(void){
	char c[10];
	int t, test_case;
	queue<int> Q;
	scanf("%d",&test_case);
	while(test_case--){
		scanf("%s",c);
		if(strcmp(c,"push")==0){
			scanf("%d",&t);
			Q.push(t);
		}
		else if(strcmp(c,"pop")==0){
			if(Q.empty())printf("-1\n");
			else {
				printf("%d\n",Q.front());
				Q.pop();
			}
		}
		else if(strcmp(c,"size")==0){
			printf("%d\n",(int)Q.size());
		}
		else if(strcmp(c,"empty")==0){
			if(Q.empty())printf("1\n");
			else printf("0\n");
		}
		else if(strcmp(c,"front")==0){
			if(Q.empty())printf("-1\n");
			else printf("%d\n",Q.front());
		}
		else if(strcmp(c,"back")==0){
			if(Q.empty())printf("-1\n");
			else printf("%d\n",Q.back());
		}
	}
	return 0;
}
