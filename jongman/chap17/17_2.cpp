#include <cstdio>
#include <vector>
#include <algorithm>

#define ZERO_INCLUDE_MAX_SIZE 200001
#define MAX_SIZE 200000

int n, m[ZERO_INCLUDE_MAX_SIZE], k;
int psum[ZERO_INCLUDE_MAX_SIZE];
int sub_max[ZERO_INCLUDE_MAX_SIZE];

// k related
int prev[MAX_SIZE];
int64_t count[MAX_SIZE];

void GetInput() {
    scanf("%d %d", &n, &k);
    for (int i=1; i<=n; i++) {
        scanf("%d", &(m[i]));
    }
}

void BuildPartSum() {
    psum[0] = 0;
    for (int i=1; i<=n; i++) {
        psum[i] = (psum[i-1] + m[i]) % k;
    }
}

int SolveOneOrder() {
    for (int i=0; i<k; i++) {
        count[i] = 0;
    }

    for (int i=0; i<=n; i++) {
        count[psum[i]]++;
    }

    int64_t result = 0;
    for (int i=0; i<k; i++) {
        result += (count[i] * (count[i] - 1)) / 2;
    }
    return result % 20091101;
}

int SolveMultipleOrder() {
    // -1 is not visited
    for(int i=0; i<k; i++) {
        prev[i] = -1;
    }
    prev[psum[0] % k] = 0;

    sub_max[0] = 0;
    for (int i=1; i<=n; i++) {
        if (prev[psum[i]] < 0) {
            sub_max[i] = sub_max[i-1];
        } else {
            sub_max[i] = std::max(sub_max[i-1], sub_max[prev[psum[i]]] + 1);
        }
        prev[psum[i]] = i;
    }
    return sub_max[n];
}

int main(void) {
    int c;
    scanf("%d", &c);
    for (int i=0; i<c; i++) {
        GetInput();
        BuildPartSum();
        printf("%d %d\n", SolveOneOrder(), SolveMultipleOrder());
    }
    return 0;
}