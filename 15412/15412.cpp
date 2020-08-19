#include <cstdio>

int n, m, r;
int x[50], y[50];
int a[15], b[15], c[15];
int chk[50];

void init();
int count_piece();
bool divide_piece();


int main(void){
	init();
	if(n != count_piece())printf("no\n");
	else if(divide_piece())printf("yes\n");
	else printf("no\n");
	return 0;
}

void init(){
	scanf("%d %d %d", &n, &m, &r);
	for(int i=0; i<n; i++)scanf("%d %d", x+i, y+i);
	for(int i=0; i<m; i++)scanf("%d %d %d", a+i, b+i, c+i);
	for(int i=0; i<n; i++)chk[i]=0;
}

int count_piece(){
	
	return result;
}

bool divide_piece(){
	for(int i=0; i<m; i++){
		if(a[i] == 0){
			double t = (double)c[i]/b[i]*(-1);	
			for(int j=0; j<n; j++)
				if(y[j] > t)chk[j] += 1<<i;
		}
		else if(b[i] == 0){
			double t = (double)c[i]/a[i]*(-1);
			for(int j=0; j<n; j++)
				if(x[j] > t)chk[j] += 1<<i;
		}
		else{
			for(int j=0; j<n; j++){
				double t = ((double)b[i]*y[j]+c[i])/a[i]*(-1);
				if(x[j] > t)chk[j] += 1<<i;
			}
		}
	}
	bool suc = true;
	for(int i=0; i<n-1; i++){
		for(int j=i+1; j<n; j++){
			if(chk[i] == chk[j]){
				suc = false;
				break;
			}
		}
		if(suc == false)break;
	}
	
	return suc;
}

