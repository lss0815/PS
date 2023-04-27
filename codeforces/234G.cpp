#include <cstdio>
 
int main() {
    FILE *rfp = fopen("input.txt", "r");
    FILE *wfp = fopen("output.txt", "w");

    int n;

    fscanf(rfp, "%d", &n);
 
    int max_level = 0;
    while (n > (1 << max_level)) {
        max_level++;
    }
 
    fprintf(wfp, "%d\n", max_level);
    for (int i=max_level - 1; i >= 0; i--) {
        int left_num = 0;
        int mask = (1 << i);
        for (int j=0; j<n; j++) {
            if ((j & mask) == 0) {
                left_num++;
            }
        }
        fprintf(wfp, "%d", left_num);
        for (int j=0; j<n; j++) {
            if ((j & mask) == 0) {
                fprintf(wfp, " %d", j + 1);
            }
        }
        fprintf(wfp, "\n");
    }

    fclose(rfp);
    fclose(wfp);
    return 0;
}