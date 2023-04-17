#include <cstdio>
#include <cmath>
#include <vector>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    std::vector<int> jewel;
    jewel.reserve(m);
    int high = 0;
    for (int i=0; i<m; i++){
        int temp;
        scanf("%d", &temp);
        jewel.push_back(temp);
        if (high < temp) {
            high = temp;
        }
    }

    // Max of jewel
    int min_jeal = high;
    int low = 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        int64_t min_children = 0;
        for (int i=0; i<m; i++){
            min_children += (jewel[i] + mid - 1) / mid;
        }

        if (min_children <= n) {
            min_jeal = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    printf("%d\n", min_jeal);
    return 0;
}