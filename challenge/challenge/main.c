//
//  main.c
//  challenge
//
//  Created by vlad on 9/18/17.
//  Copyright © 2017 vlad. All rights reserved.
//

#include <stdio.h>

#define NUM_OF_PAIRS 5
#define NOT_CONNECTED -1
typedef enum {FALSE,TRUE} bool;

typedef enum{
    PAIR,
    CONNECTION_LEVEL,
    MAX_TRACK
}ConnectionTrack;

int buyer[NUM_OF_PAIRS][NUM_OF_PAIRS] = {   0, 4, 3, 2, 1,
                                            1, 4, 0, 3, 2,
                                            4, 2, 3, 1, 0,
                                            3, 2, 4, 0, 1,
                                            3, 2, 0, 4, 1};
int seller[NUM_OF_PAIRS][NUM_OF_PAIRS] = {  1, 2, 4, 3, 0,
                                            3, 2, 1, 4, 0,
                                            2, 0, 1, 3, 4,
                                            3, 4, 3, 1, 0,
                                            0, 1, 3, 4, 2};

int buyersConnected[NUM_OF_PAIRS] = {[0 ... NUM_OF_PAIRS - 1] = NOT_CONNECTED};
int sellersConnected[NUM_OF_PAIRS][MAX_TRACK] = {[0 ... NUM_OF_PAIRS - 1] = NOT_CONNECTED};

bool isDone(){
    
    for(int i = 0; i < NUM_OF_PAIRS; i++){
        if(buyersConnected[i] == NOT_CONNECTED || sellersConnected[i][PAIR] == NOT_CONNECTED)
            return FALSE;
    }
    return TRUE;
}
void connectPairs(){
    int currentPreferenceLevelBuyer = 0;
    int currentPreferenceLevelSeller = 0;
    int currentProposal = NOT_CONNECTED;
    
    while(isDone() != TRUE){
        
        if(currentPreferenceLevelBuyer > 4){
            currentPreferenceLevelBuyer = 0;
            currentPreferenceLevelSeller++;
            if(currentPreferenceLevelSeller > 4){
                currentPreferenceLevelSeller = 0;
            }
        }
        
        for(int i = 0; i < NUM_OF_PAIRS; i++)
        {
            if(buyersConnected[i] == NOT_CONNECTED)
            {
                currentProposal = buyer[i][currentPreferenceLevelBuyer];
                
                if (seller[currentProposal][currentPreferenceLevelSeller] == i)
                {
                    if( sellersConnected[currentProposal][PAIR] == NOT_CONNECTED)
                    {
                        buyersConnected[i]                                  = currentProposal;
                        sellersConnected[currentProposal][PAIR]             = i;
                        sellersConnected[currentProposal][CONNECTION_LEVEL] = currentPreferenceLevelSeller;
                        continue;
                    }
                    else if( sellersConnected[currentProposal][CONNECTION_LEVEL] > currentPreferenceLevelSeller){
                        int buyerToClean = sellersConnected[currentProposal][PAIR];
                        buyersConnected[buyerToClean]                       = NOT_CONNECTED;
                        
                        buyersConnected[i]                                  = currentProposal;
                        sellersConnected[currentProposal][PAIR]             = i;
                        sellersConnected[currentProposal][CONNECTION_LEVEL] = currentPreferenceLevelSeller;
                        continue;
                    }
                }
            }
        }
        currentPreferenceLevelBuyer++;
    }
}

void printPairs(){
    for(int i = 0; i < NUM_OF_PAIRS; i++){
        int sellerId = buyersConnected[i];
        printf("Buyer %d paired with seller %d, seller %d connected to buyer %d\n",
               i, sellerId, sellerId, sellersConnected[sellerId][PAIR]);
    }
}

int main(int argc, const char * argv[]) {
    
    
    connectPairs();
    
    printPairs();
    return 0;
}
