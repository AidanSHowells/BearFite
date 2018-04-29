#ifndef BEARBATTLE_H
#define BEARBATTLE_H

#include "HUD.h"
#include "Bear.h"

//Currently returns true if the player wins, false otherwise. Will eventually
//handle the effects of player or bear winning by calling helper functions


//Parameter fakeBear is currently here only so that BattleTest.cpp can display
//information about the bear that you just killed.
bool BearBattle(BattleHUD& theHUD, Bear& fakeBear);

#endif
