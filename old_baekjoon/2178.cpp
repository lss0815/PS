#include <stdio.h>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

int INF = 987654321;
int MAP[100][100];

int main(void){
	int n, m, l, row, col, result;
	char c;
	queue<tuple<int,int,int>> Q;
	tuple<int,int,int> tp;
	scanf("%d %d",&n,&m);
	getchar();
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			c = getchar();
			MAP[i][j]=c-'0';
		}
		getchar();
	}
	Q.push(make_tuple(0,0,1));
	MAP[0][0]=0;
	while(!Q.empty()){
		tp = Q.front();
		l = get<2>(tp);
		row = get<0>(tp);
		col = get<1>(tp);
		Q.pop();
		if(row == n-1 && col == m-1){
			result = l;
			break;
		}
		if(row>0&&MAP[row-1][col]==1){
			MAP[row-1][col]=0;
			Q.push(make_tuple(row-1,col,l+1));
		}
		if(col>0&&MAP[row][col-1]==1){
			MAP[row][col-1]=0;
			Q.push(make_tuple(row,col-1,l+1));
		}
		if(row<n-1&&MAP[row+1][col]==1){
			MAP[row+1][col]=0;
			Q.push(make_tuple(row+1,col,l+1));
		}
		if(col<m-1&&MAP[row][col+1]==1){
			MAP[row][col+1]==0;
			Q.push(make_tuple(row,col+1,l+1));
		}
	}
	printf("%d\n",result);
	return 0;
}
