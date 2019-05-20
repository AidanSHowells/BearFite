#ifndef BEARBATTLE_H
#define BEARBATTLE_H

#include "HUD.h"
#include "Bear.h"

enum class TurnOf {player, bear, neither};
enum class Winner {player, bear, neither};

//Currently returns Winner::player if the player wins, and similarly for the
//bear. Returns Winner::neither if neither wins. Will eventually
//handle the effects of player or bear winning by calling helper functions


//Parameter fakeBear is currently here only so that BattleTest.cpp can display
//information about the bear that you just killed.
Winner BearBattle(BattleHUD& theHUD, Bear& fakeBear);

#endif
