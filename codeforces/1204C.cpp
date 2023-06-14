#include <cstdio>
#include <exception>
#include <vector>

#define MAX_N 100
#define MAX_M 1000000

int n;
bool edge[MAX_N][MAX_N];
int distance[MAX_N][MAX_N];

int m;
int p[MAX_M];

int k;
int v[MAX_M];

void GetInput() {
  scanf("%d", &n);
  for (int i=0; i<n; i++) {
    char input[MAX_N + 1];
    scanf("%s", input);
    for (int j=0; j<n; j++) {
      if (input[j] == '0') {
        edge[i][j] = false;
      } else if(input[j] == '1') {
        edge[i][j] = true;
      } else {
        printf("Wrong input %s", input);
        throw std::exception();
      }
    }
  }
  scanf("%d", &m);
  for (int i=0; i<m; i++) {
    scanf("%d", &(p[i]));
    p[i]--; // Real world vertex index -1 => program world vertex index
  }
}

void PrintInput() {
  printf("%d\n", n);
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      printf("%c", edge[i][j] ? '1' : '0');
    }
    printf("\n");
  }
  printf("%d\n", m);
  for (int i=0; i<m; i++) {
    printf("%d ", p[i] + 1);
  }
  printf("\n");
}

void BuildDistance() {
  std::vector<std::pair<int, int>> updated_pairs;
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      if (edge[i][j]) {
        distance[i][j] = 1;
        updated_pairs.emplace_back(i, j);
      }
    }
  }

  while (!updated_pairs.empty()) {
    std::vector<std::pair<int, int>> updating_pairs = std::move(updated_pairs);
    updated_pairs.clear(); // Just in case
    for (const auto& pair : updating_pairs) {
      for (int i=0; i<n; i++) {
        if (distance[pair.first][i] == 0 && edge[pair.second][i]) {
          distance[pair.first][i] = distance[pair.first][pair.second] + 1;
          updated_pairs.emplace_back(pair.first, i);
        }
      }
    }
  }

  for (int i=0; i<n; i++) {
    distance[i][i] = 0; // For a trick to prevent any two consecutive numbers
  }
}

void PrintDistance() {
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      printf("%d ", distance[i][j]);
    }
    printf("\n");
  }
}

void CalculateV() {
  v[k++] = p[0]; // 0 is always inserted
  int head = 0;
  int tail = head + 1;
  while (tail < m-1) { // m-1 wil be always inserted
    if (tail - head <= distance[p[head]][p[tail]]) {
      tail++;
    } else {
      v[k++] = p[tail - 1];
      head = tail - 1;
    }
  }
  if (tail - head > distance[p[head]][p[tail]]) {
    v[k++] = p[tail - 1];
  }
  v[k++] = p[m-1];
}

void PrintV() {
  printf("%d\n", k);
  for (int i=0; i<k; i++) {
    if (i != 0) printf(" ");
    printf("%d", v[i] + 1);
  }
  printf("\n");
}

int main() {
  GetInput();
  //PrintInput();
  BuildDistance();
  //PrintDistance();
  CalculateV();
  PrintV();
  return 0;
}