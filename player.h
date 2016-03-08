#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "board.h"
using namespace std;

class Player {
private:
    Board b;
    Side side;
public:
    Player(Side side);
    ~Player();
    void mysetBoard(Board b1);
    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
