#include <cstdlib>//include random number generator
#include <array>//for std::array
#include <algorithm>//for std::sort
#include "RollDice.h"

//Rolls diceNumber "d" diceType. modifier defaults to RollMod::none
int Roll(const int diceNumber, const int diceType, const RollMod modifier){
  int total = 0;
  if(RollMod::none == modifier){
    for (int i = 0; i < diceNumber; i++) {
      int tempNum = rand();
      while(tempNum >= RAND_MAX - (RAND_MAX % diceType)){
        tempNum = rand();
      }
      total += ((tempNum % diceType) + 1);
    }
  }
  else if(RollMod::wild == modifier){
    const int wildNum = 5;//Number of rolls from which max/min is choosen

    std::array<int, wildNum> numList;
    for(int i = 0; i < wildNum; i++){
      numList.at(i) = Roll(diceNumber, diceType);
    }
    std::sort(numList.begin(), numList.end());
    if(Roll(1,2) % 2 == 0){
      total = numList.at(0);
    }
    else{
      total = numList.at(wildNum - 1);
    }
  }
  else if(RollMod::consistant == modifier){
    const int consistantNum = 5;//Number of rolls from which median is choosen

    std::array<int, consistantNum> numList;
    for(int i = 0; i < consistantNum; i++){
      numList.at(i) = Roll(diceNumber, diceType);
    }
    std::sort(numList.begin(), numList.end());
    total = numList.at(consistantNum / 2);
  }
  return (total);
}
