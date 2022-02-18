#include <cstdio>

int main(void){
    long long rangeStart, rangeEnd;
    bool isSquaredNoNo[1000001];
    scanf("%lld %lld", &rangeStart, &rangeEnd);
    long long rangeSize = rangeEnd - rangeStart + 1;

    for(int i=0; i<rangeSize; i++){
        isSquaredNoNo[i] = true;
    }

    for(long long i=2; i<1000001; i++){
        long long squaredI = i * i;
        long long currentNum = (rangeStart / squaredI) * squaredI;
        while(currentNum <= rangeEnd){
            if(currentNum >= rangeStart){
                isSquaredNoNo[currentNum - rangeStart] = false;
            }
            currentNum += squaredI;
        }
    }

    int result = 0;
    for(int i=0; i<rangeSize; i++){
        if(isSquaredNoNo[i] == true){
            result++;
        }
    }

    printf("%d", result);

    return 0;
}