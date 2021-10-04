#include <cstdio>

long long digitWeight[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 10000000000};

long long getDigitNumber(long long num){
    long long digitNum = -1;
    while(num){
        num /= (long long) 10;
        digitNum++;
    }
    if(digitNum == -1){
        digitNum = 0;
    }
    return digitNum;
}

void countDigitFromChildNumber(long long currentNum, long long digitNum, long long* digitCount)
{
    if(digitNum == 0){
        for(int i=0; i<=currentNum; i++){
            digitCount[i]++;
        }
        return;
    }
    long long topDigitValue = currentNum / digitWeight[digitNum];
    digitCount[topDigitValue] += currentNum % digitWeight[digitNum] + 1;
    for(int i=0; i<topDigitValue; i++){
        digitCount[i] += digitWeight[digitNum];
    }
    for(int i=0; i<10; i++){
        digitCount[i] += topDigitValue * digitNum * (digitWeight[digitNum-1]);
    }
    countDigitFromChildNumber(currentNum % digitWeight[digitNum], digitNum-1, digitCount);
}

void countDigitFromNormalNumber(long long currentNum, long long digitNum, long long* digitCount)
{
    if(digitNum == 0){
        for(int i=1; i<=currentNum; i++){
            digitCount[i]++;
        }
        return;
    }
    long long topDigitValue = currentNum / digitWeight[digitNum];
    digitCount[topDigitValue] += currentNum % digitWeight[digitNum] + 1;
    for(int i=1; i<topDigitValue; i++){
        digitCount[i] += digitWeight[digitNum];
    }
    for(int i=0; i<10; i++){
        digitCount[i] += (topDigitValue - 1) * digitNum * (digitWeight[digitNum-1]);
    }
    countDigitFromNormalNumber(digitWeight[digitNum] - 1, digitNum-1, digitCount);
    countDigitFromChildNumber(currentNum % digitWeight[digitNum], digitNum-1, digitCount);
}

int main(void){
    long long page, digitCount[10] = {};
    scanf("%lld", &page);

    countDigitFromNormalNumber(page, getDigitNumber(page), digitCount);

    for(int i=0; i<10; i++){
        printf("%lld", digitCount[i]);
        if(i != 9){
            printf(" ");
        }
    }
}