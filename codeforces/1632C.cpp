#include <cstdio>
#include <algorithm>

int FindMSB(int n) {
  if (n == 0) return 0;
  int k = 1;
  while (k <= n) {
    k = k << 1;
  }
  return k >> 1;
}

int main() {
  int test_case;
  scanf("%d", &test_case);

  while(test_case--) {
    int a, b;
    scanf("%d %d", &a, &b);
    int result = b - a; // Zero OR
    for (int a2 = a; a2 <= b; a2++) {
      int k = a2 - (a2 & b);
      int p;
      if (k == 0) { // k is 0
        p = 0;
      } else {
        p = (b - (a2 & b)) & (FindMSB(k) - 1); // p can't have k's MSB
      }
      int b2 = b + k - p;
      result = std::min(result, a2 + (a2 | b2) - a - b + 1);
    }
    printf("%d\n", result);
  }
  return 0;
}