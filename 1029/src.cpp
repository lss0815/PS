#include <cstdio>
#include <algorithm>

int artistNum, tradePrice[15][15];
int initialState;
// un-calculated : -1, unreachable : -2
int minFinalPrice[32768][15];

int calculateMinFinalPrice(int state, int lastOwner){
    if(minFinalPrice[state][lastOwner] != -1){
        return minFinalPrice[state][lastOwner];
    }
    for(int i=1; i<artistNum; i++){
        if(i == lastOwner){
            continue;
        }
        if((initialState >> i) & state){
            int childState = state ^ (initialState >> lastOwner);
            int childPrice = calculateMinFinalPrice(childState, i);
            if(childPrice >= 0 && tradePrice[i][lastOwner] >= childPrice){
                if(minFinalPrice[state][lastOwner] >= 0){
                    minFinalPrice[state][lastOwner] = std::min(minFinalPrice[state][lastOwner], tradePrice[i][lastOwner]);
                } else {
                    minFinalPrice[state][lastOwner] = tradePrice[i][lastOwner];
                }
            }
        }
    }
    if(minFinalPrice[state][lastOwner] == -1){
        minFinalPrice[state][lastOwner] = -2;
    }
    return minFinalPrice[state][lastOwner];
}

int main(void){
    char tradePriceString[15][17];
    scanf("%d", &artistNum);
    for(int i=0; i<artistNum; i++){
        scanf("%s", tradePriceString[i]);
    }
    for(int i=0; i<artistNum; i++){
        for(int j=0; j<artistNum; j++){
            tradePrice[i][j] = tradePriceString[i][j] - '0';
        }
    }

    initialState = 1 << (artistNum - 1);
    for(int i=0; i<=(initialState << 1) - 1; i++){
        for(int j=0; j<artistNum; j++){
            if((initialState >> j) & i){
                minFinalPrice[i][j] = -1;
            } else {
                minFinalPrice[i][j] = -2;
            }
        }
    }
    minFinalPrice[initialState][0] = 0;
    for(int i=1; i<artistNum; i++){
        minFinalPrice[initialState | (initialState >> i)][i] = tradePrice[0][i];
    }


    for(int i=1; i<artistNum; i++){
        calculateMinFinalPrice((initialState << 1) - 1, i);
    }

    int result = 0;
    for(int i=initialState; i<(initialState << 1); i++){
        for(int j=0; j<artistNum; j++){
            if(minFinalPrice[i][j] >= 0){
                int count = 0;
                for(int k=0; k<artistNum; k++){
                    if((initialState >> k) & i){
                        count++;
                    }
                }
                result = std::max(result, count);
            }
        }
    }

    printf("%d", result);
    return 0;
}