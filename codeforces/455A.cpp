#include <cstdio>
#include <cstdint>
#include <algorithm>

int main() {
	int n;
	constexpr int kMaxSize = 100001;
	int64_t count[kMaxSize] = {0};

	scanf("%d", &n);
	for(int i=0; i<n; i++) {
		int temp;
		scanf("%d", &temp);
		count[temp]++;
	}

	int64_t max_include[kMaxSize];
	int64_t max_exclude[kMaxSize];

	max_include[0] = 0;
	max_exclude[0] = 0;

	for (int64_t i=1; i<kMaxSize; i++) {
		max_include[i] = max_exclude[i-1] + i * count[i];
		max_exclude[i] = std::max(max_include[i-1], max_exclude[i-1]);
	}

	printf("%lld", std::max(max_exclude[kMaxSize-1], max_include[kMaxSize-1]));
	return 0;
}