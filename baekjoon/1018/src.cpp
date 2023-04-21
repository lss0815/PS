#include <cstdio>
#include <algorithm>

int CountTrueBits(int64_t num) {
  int count = 0;
  while (num > 0) {
    count += num % 2;
    num = num >> 1;
  }
  return count;
}

int main() {
  int m, n;
  scanf("%d %d", &m, &n);

  int64_t board[m];
  for(int i=0; i<m; i++) {
    char c = getchar();
    int64_t line = 0;
    for (int j=0; j<n; j++) {
      c = getchar();
      line = line << 1;
      if (c == 'B') {
        line += 1;
      }
    }
    board[i] = line;
  }

  int min_paint = 987654321;

  int64_t checker_row[2];
  checker_row[0] = (1 << 6) + (1 << 4) + (1 << 2) + 1;
  checker_row[1] = checker_row[0] << 1;
  int64_t mask = (1 << 8) - 1;
  // i: col pos, j: row pos
  for (int i=7; i<n; i++) {
    // paint_row[0]: B is top-left, paint_row[1]: W is top-left
    int paint_row[2][m];
    for (int j=0; j<m; j++) {
      for (int k=0; k<2; k++) {
        paint_row[k][j] = CountTrueBits((board[j] & (mask << (n - i - 1))) ^ (checker_row[(j + k) % 2] << (n - i - 1)));
      }
    }

    int paint_sum[2] = {0};
    for (int j=0; j<8; j++) {
      for (int k=0; k<2; k++) {
        paint_sum[k] += paint_row[k][j];
      }
    }
    for (int k=0; k<2; k++) {
      min_paint = std::min(min_paint, paint_sum[k]);
    }

    for (int j=8; j<m; j++) {
      for (int k=0; k<2; k++) {
        paint_sum[k] -= paint_row[k][j - 8];
        paint_sum[k] += paint_row[k][j];
        min_paint = std::min(min_paint, paint_sum[k]);
      }
    }
  }
  printf("%d", min_paint);
  return 0;
}