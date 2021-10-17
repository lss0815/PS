#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>

int binarySearchAvailableMap(const std::vector<std::pair<int, int>>& availableMap, int target, int startIndex, int endIndex)
{
    int mid = (startIndex + endIndex)/2;
    if(availableMap[mid].first == target){
        return mid;
    }
    if(startIndex >= endIndex - 1){
        return -1;
    }
    if(availableMap[mid].first < target){
        return binarySearchAvailableMap(availableMap, target, startIndex, mid);
    } else {
        return binarySearchAvailableMap(availableMap, target, mid+1, endIndex);
    }
}

int binarySearchTargetMap(const std::vector<int>& targetMap, int target, int startIndex, int endIndex)
{
    int mid = (startIndex + endIndex)/2;
    if(targetMap[mid] == target){
        return mid;
    }
    if(startIndex >= endIndex - 1){
        return -1;
    }
    if(targetMap[mid] < target){
        return binarySearchTargetMap(targetMap, target, startIndex, mid);
    } else {
        return binarySearchTargetMap(targetMap, target, mid+1, endIndex);
    }
}

int convertMapToCode(const std::vector<int>& sculpturePosition)
{
    int currentMapCode = 0;
    for(int i=0; i<sculpturePosition.size(); i++){
        currentMapCode |= 1 << (24 - sculpturePosition[i]);
    }
    return currentMapCode;
}

std::vector<int> convertCodeToMap(const int& sculptureCode){
    std::vector<int> currentMap;
    for(int i=0; i<25; i++){
        if(sculptureCode & (1 << (24 - i))){
            currentMap.push_back(i);
        }
    }
    return currentMap;
}

bool isSculpturesConnected(const std::vector<int>& sculpturePosition)
{
    std::vector<bool> isSculptureConnected;
    isSculptureConnected.resize(25);
    for(int i=0; i< 25; i++){
        isSculptureConnected[i] = false;
    }
    int connectedCount = 1;
    std::queue<int> positionQueue;
    positionQueue.push(sculpturePosition[0]);
    isSculptureConnected[sculpturePosition[0]] = true;

    int currentMapCode = convertMapToCode(sculpturePosition);
    while(!positionQueue.empty()){
        int curPosition = positionQueue.front();
        positionQueue.pop();
        if(curPosition%5 != 4 && (currentMapCode & (1 << (24 - (curPosition + 1)))) && !isSculptureConnected[curPosition + 1]){
            isSculptureConnected[curPosition + 1] = true;
            positionQueue.push(curPosition + 1);
            connectedCount++;
        }
        if(curPosition%5 != 0 && (currentMapCode & (1 << (24 - (curPosition - 1)))) && !isSculptureConnected[curPosition - 1]){
            isSculptureConnected[curPosition - 1] = true;
            positionQueue.push(curPosition - 1);
            connectedCount++;
        }
        if(curPosition > 4 && (currentMapCode & (1 << (24 - (curPosition - 5)))) && !isSculptureConnected[curPosition - 5]){
            isSculptureConnected[curPosition - 5] = true;
            positionQueue.push(curPosition - 5);
            connectedCount++;
        }
        if(curPosition < 20 && (currentMapCode & (1 << (24 - (curPosition + 5)))) && !isSculptureConnected[curPosition + 5]){
            isSculptureConnected[curPosition + 5] = true;
            positionQueue.push(curPosition + 5);
            connectedCount++;
        }
    }
    return connectedCount == sculpturePosition.size();
}

void registerAvailableMapAndTargetMap(std::vector<std::pair<int, int>>& availableMap, std::vector<int>& targetMap,
                                      const std::vector<int>& sculpturePosition)
{
    int currentMapCode = convertMapToCode(sculpturePosition);
    if(isSculpturesConnected(sculpturePosition)){
        targetMap.push_back(currentMapCode);
    }
    availableMap.push_back(std::pair<int, int>(currentMapCode, 0));
}

void searchAvailableMapAndTargetMap(int sculptureNum, std::vector<std::pair<int, int>>& availableMap, std::vector<int>& targetMap)
{
    std::vector<int> sculpturePosition;
    for(int i=0; i<sculptureNum; i++){
        sculpturePosition.push_back(i);
    }
    registerAvailableMapAndTargetMap(availableMap, targetMap, sculpturePosition);

    bool isNotFinal = true;
    while(isNotFinal){
        isNotFinal = false;
        for(int i=sculpturePosition.size()-1; i>=0; i--){
            if(sculpturePosition[i] < (25 - sculpturePosition.size() + i)){
                sculpturePosition[i]++;
                for(int j=i+1; j<sculpturePosition.size(); j++){
                    sculpturePosition[j] = sculpturePosition[j-1] + 1;
                }
                registerAvailableMapAndTargetMap(availableMap, targetMap, sculpturePosition);
                isNotFinal = true;
                break;
            }
        }
    }
}

int main(void)
{
    char initialMap[25], tempMap[6];
    int sculptureNum = 0;
    std::vector<int> initialSculpturePosition;
    for(int i=0; i<5; i++){
        scanf("%s", tempMap);
        for(int j=0; j<5; j++){
            if(tempMap[j] == '.'){
                initialMap[i*5 + j] = 0;
            } else {
                initialMap[i*5 + j] = 1;
                initialSculpturePosition.push_back(i*5 + j);
                sculptureNum++;
            }
        }
    }

    std::vector<std::pair<int, int>> availableMap;
    std::vector<int> targetMap;

    searchAvailableMapAndTargetMap(sculptureNum, availableMap, targetMap);

    std::queue<std::pair<int, int>> mapCodeQueue;
    mapCodeQueue.push(std::make_pair<int, int>(convertMapToCode(initialSculpturePosition), 0));
    int initialIndex = binarySearchAvailableMap(availableMap, convertMapToCode(initialSculpturePosition), 0, availableMap.size());
    availableMap[initialIndex].second++;

    while(!mapCodeQueue.empty()){
        std::pair<int, int> currentMapInfo = mapCodeQueue.front();
        std::vector<int> currentPosition = convertCodeToMap(currentMapInfo.first);
        mapCodeQueue.pop();
        if(binarySearchTargetMap(targetMap, currentMapInfo.first, 0, targetMap.size()) != -1){
            printf("%d", currentMapInfo.second);
            break;
        }

        for(int i=0; i<currentPosition.size(); i++){
            if(currentPosition[i]%5 != 0){
                currentPosition[i]--;
                int nextIndex = binarySearchAvailableMap(availableMap, convertMapToCode(currentPosition), 0, availableMap.size());
                if(nextIndex != -1 && availableMap[nextIndex].second == 0){
                    mapCodeQueue.push(std::make_pair<int, int>(convertMapToCode(currentPosition), currentMapInfo.second + 1));
                    availableMap[nextIndex].second++;
                }
                currentPosition[i]++;
            }
            if(currentPosition[i] >= 5){
                currentPosition[i] -= 5;
                int nextIndex = binarySearchAvailableMap(availableMap, convertMapToCode(currentPosition), 0, availableMap.size());
                if(nextIndex != -1 && availableMap[nextIndex].second == 0){
                    mapCodeQueue.push(std::make_pair<int, int>(convertMapToCode(currentPosition), currentMapInfo.second + 1));
                    availableMap[nextIndex].second++;
                }
                currentPosition[i] += 5;
            }
            if(currentPosition[i]%5 != 4){
                currentPosition[i]++;
                int nextIndex = binarySearchAvailableMap(availableMap, convertMapToCode(currentPosition), 0, availableMap.size());
                if(nextIndex != -1 && availableMap[nextIndex].second == 0){
                    mapCodeQueue.push(std::make_pair<int, int>(convertMapToCode(currentPosition), currentMapInfo.second + 1));
                    availableMap[nextIndex].second++;
                }
                currentPosition[i]--;
            }
            if(currentPosition[i] < 20){
                currentPosition[i] += 5;
                int nextIndex = binarySearchAvailableMap(availableMap, convertMapToCode(currentPosition), 0, availableMap.size());
                if(nextIndex != -1 && availableMap[nextIndex].second == 0){
                    mapCodeQueue.push(std::make_pair<int, int>(convertMapToCode(currentPosition), currentMapInfo.second + 1));
                    availableMap[nextIndex].second++;
                }
                currentPosition[i] -= 5;
            }
        }
    }

    return 0;
}
