#include <cstdio>
#include <cstdint>

int main() {
    int n;
    scanf("%d", &n);

    uint64_t result;
    if(n % 2 == 1) {
        result = 0;
    } else {
        result = 1 << (n / 2);
    }
    printf("%llu", result);

    return 0;
}