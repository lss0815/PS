#include <cstdio>

int n, m, r;
double x[50], y[50];
double a[15], b[15], c[15];
int chk[50];

void init();
int count_piece();
bool divide_piece();
double abs_val(double);

int main(void){
	init();
	if(n != count_piece())printf("no\n");
	else if(divide_piece())printf("yes\n");
	else printf("no\n");
	return 0;
}

void init(){
	scanf("%d %d %d", &n, &m, &r);
	for(int i=0; i<n; i++)scanf("%lf %lf", x+i, y+i);
	for(int i=0; i<m; i++)scanf("%lf %lf %lf", a+i, b+i, c+i);
	for(int i=0; i<n; i++)chk[i]=0;
}

int count_piece(){
	int result = 1;
	double xarr[15], yarr[15];
	for(int i=0; i<m; i++){
		int cnt = 0;
		double tx, ty;
		for(int j=0; j<i; j++){
			if(a[i]==0){
				ty = c[i]/b[i]*(-1);
				if(a[j]==0) continue;
				else if(b[j]==0) tx = c[j]/a[j]*(-1);
				else tx = (b[j]*ty+c[j])/a[j]*(-1);
			}
			else if(b[i]==0){
				tx = c[i]/a[i]*(-1);
				if(b[j]==0) continue;
				else if(a[j]==0) ty = c[j]/b[i]*(-1);
				else ty = (a[j]*tx+c[j])/b[j]*(-1);
			}
			else{
				if(a[j]==0){
					ty = c[j]/b[j]*(-1);
					tx = (b[i]*ty+c[i])/a[i]*(-1);
				}
				else if(b[j]==0){
					tx = c[j]/a[j]*(-1);
					ty = (a[i]*tx+c[i])/b[i]*(-1);
				}
				else{
					if(a[i]*b[j] == a[j]*b[i]) continue;
					ty = (a[i]*c[j] - a[j]*c[i])/(a[j]*b[i] - a[i]*b[j]);
					tx = (b[i]*ty+c[i])/a[i]*(-1);
				}
			}
			bool dup = false;
			for(int k=0; k<cnt; k++){
				if(abs_val(xarr[k] - tx) <= 0.0002 && abs_val(yarr[k] - ty) <= 0.0002){
					dup = true;
					break;
				}
			}
			if(!dup && (tx*tx + ty*ty) < (double)r*r) {
				xarr[cnt] = tx;
				yarr[cnt] = ty;
				cnt++;
			}
		}
		result += cnt + 1;
	}
	return result;
}

bool divide_piece(){
	for(int i=0; i<m; i++){
		if(a[i] == 0){
			double t = c[i]/b[i]*(-1);	
			for(int j=0; j<n; j++)
				if(y[j] > t)chk[j] += 1<<i;
		}
		else if(b[i] == 0){
			double t = c[i]/a[i]*(-1);
			for(int j=0; j<n; j++)
				if(x[j] > t)chk[j] += 1<<i;
		}
		else{
			for(int j=0; j<n; j++){
				double t = (b[i]*y[j]+c[i])/a[i]*(-1);
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

double abs_val(double t){
	if(t < 0) t *= (-1);
	return t;
}
