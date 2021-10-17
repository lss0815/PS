#include <cstdio>
#include <deque>

bool compareNumber(const std::deque<int>& number1, const std::deque<int>& number2)
{
    bool result = true;
    if(number1.size() < number2.size()){
        result = false;
    }
    else if(number1.size() == number2.size()){
        for(int i=number1.size()-1; i>=0; i--){
            if(number1[i] == number2[i]){
                continue;
            } else if(number1[i] > number2[i]){
                break;
            } else {
                result = false;
                break;
            }
        }
    }
    return result;
}

std::deque<std::deque<int>> convertDigitToZ(const std::deque<std::deque<int>>& originalNumbers, const int& targetDigit)
{
    std::deque<std::deque<int>> resultNumbers = originalNumbers;
    for(int i=0; i<resultNumbers.size(); i++){
        for(int j=0; j<resultNumbers[i].size(); j++){
            if(resultNumbers[i][j] == targetDigit){
                resultNumbers[i][j] = 35;
            }
        }
    }
    return resultNumbers;
}

std::deque<int> getSummedNumber(const std::deque<int>& number1, const std::deque<int>& number2)
{
    std::deque<int> result;
    result = number1;
    int lastUpDigit = 0;
    for(int i=0; i<number1.size(); i++){
        if(i < number2.size()){
            result[i] = (number1[i] + number2[i] + lastUpDigit) % 36;
            lastUpDigit = (number1[i] + number2[i] + lastUpDigit) / 36;
        } else {
            result[i] = (number1[i] + lastUpDigit) % 36;
            lastUpDigit = (number1[i] + lastUpDigit) / 36;
        }
    }
    for(int i=number1.size(); i<number2.size(); i++){
        result.push_back((number2[i] + lastUpDigit) % 36);
        lastUpDigit = (number2[i] + lastUpDigit) / 36;
    }
    if(lastUpDigit == 1){
        result.push_back(lastUpDigit);
    }
    return result;
}

std::deque<int> getAbstractedNumber(const std::deque<int>& number1, const std::deque<int>& number2)
{
    std::deque<int> result;
    if(!compareNumber(number1, number2)){
        return result;
    }
    int lastUpDigit = 0;
    result.resize(number1.size());
    for(int i=0; i<number1.size(); i++){
        if(i < number2.size()){
            result[i] = (number1[i] - number2[i] + lastUpDigit + 36) % 36;
            if(number1[i] - number2[i] + lastUpDigit < 0){
                lastUpDigit = -1;
            } else {
                lastUpDigit = 0;
            }
        } else {
            result[i] = (number1[i] + lastUpDigit + 36) % 36;
            if(number1[i] + lastUpDigit < 0){
                lastUpDigit = -1;
            } else {
                lastUpDigit = 0;
            }
        }
    }
    for(int i=result.size() - 1; i>=0; i--){
        if(result[i] == 0){
            result.pop_back();
        } else {
            break;
        }
    }
    return result;
}

void printNumber(std::deque<int> number){
    for(int i=number.size() - 1; i >=0; i--){
        if(number[i] < 10){
            printf("%c", '0' + number[i]);
        } else {
            printf("%c", 'A' + number[i] - 10);
        }
    }
}

std::deque<int> getNumberDeque(char *number){
    std::deque<int> result;
    int iter = 0;
    while(number[iter] != '\0'){
        if(number[iter] >= '0' && number[iter] <= '9'){
            result.push_front(number[iter] - '0');
        } else {
            result.push_front(number[iter] - 'A' + 10);
        }
        iter++;
    }
    return result;
}

int main(void){
    int wordNum, convertNum;
    char numberString[50][51];
    scanf("%d", &wordNum);
    for(int i=0; i<wordNum; i++){
        scanf("%s", numberString[i]);
    }
    scanf("%d", &convertNum);

    std::deque<std::deque<int>> numbers;
    for(int i=0; i<wordNum; i++){
        numbers.push_back(getNumberDeque(numberString[i]));
    }
    std::deque<int> sumOriginalNumber = numbers[0];
    for(int i=1; i<wordNum; i++){
        sumOriginalNumber = getSummedNumber(sumOriginalNumber, numbers[i]);
    }

    std::deque<std::deque<int>> convertedSumDiffNumbers;
    for(int i=0; i<36; i++){
        auto convertedNumbers = convertDigitToZ(numbers, i);
        std::deque<int> sumConvertedNumber = convertedNumbers[0];
        for(int j=1; j<wordNum; j++){
            sumConvertedNumber = getSummedNumber(sumConvertedNumber, convertedNumbers[j]);
        }
        convertedSumDiffNumbers.push_back(getAbstractedNumber(sumConvertedNumber, sumOriginalNumber));
    }

    std::deque<int> emptyNumber;
    std::deque<int> resultNumber = sumOriginalNumber;
    for(int i=0; i<convertNum; i++){
        int maxIndex = 0;
        for(int i=1; i<36; i++){
            if(compareNumber(convertedSumDiffNumbers[i], convertedSumDiffNumbers[maxIndex])){
                maxIndex = i;
            }
        }
        resultNumber = getSummedNumber(resultNumber, convertedSumDiffNumbers[maxIndex]);
        convertedSumDiffNumbers[maxIndex] = emptyNumber;
    }

    printNumber(resultNumber);

    return 0;
}