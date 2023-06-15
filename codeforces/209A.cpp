#include <cstdio>

#define MOD 1000000007

int main() {
  int n;
  scanf("%d", &n);

  int r = 0;
  int b = 0;

  for (int i=0; i<n; i++) {
    if (i % 2 == 0) {
      b = (r + b + 1) % MOD;
    } else {
      r = (r + b + 1) % MOD;
    }
  }
  printf("%d\n", (r + b) % MOD);
  return 0;
}