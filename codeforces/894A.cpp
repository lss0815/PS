#include <cstdio>
#include <cstring>

int main() {
	char str[101];
	scanf("%s", str);
	
	int qaq[101][3] = {0};

	if (str[0] == 'Q') {
		qaq[0][0] = 1;
	}

	int len = strlen(str);
	for(int i=1; i<len; i++) {
		if (str[i] == 'Q') {
			qaq[i][0] = qaq[i-1][0] + 1;
			qaq[i][1] = qaq[i-1][1];
			qaq[i][2] = qaq[i-1][2] + qaq[i-1][1];
		} else if (str[i] == 'A') {
			qaq[i][0] = qaq[i-1][0];
			qaq[i][1] = qaq[i-1][1] + qaq[i-1][0];
			qaq[i][2] = qaq[i-1][2];
		} else {
			qaq[i][0] = qaq[i-1][0];
			qaq[i][1] = qaq[i-1][1];
			qaq[i][2] = qaq[i-1][2];
		}
	}

	printf("%d", qaq[len-1][2]);
	return 0;
}