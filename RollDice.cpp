#include <cstdlib>//include random number generator
#include <array>//for std::array
#include <algorithm>//for std::sort, for std::max, and std::min
#include <iostream>//for std::cout in debug mode
#include "RollDice.h"

const bool inDebugMode = true;

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
  else if(RollMod::maximized == modifier){
    total = diceNumber * diceType;
  }
  else if(RollMod::advantage == modifier){
    total = std::max(Roll(diceNumber,diceType),Roll(diceNumber,diceType));
  }
  else if(RollMod::disadvantage == modifier){
    total = std::min(Roll(diceNumber,diceType),Roll(diceNumber,diceType));
  }
  if(inDebugMode){
    std::cout << "Roll(" << diceNumber << ", " << diceType << ") = " << total;

    if(modifier == RollMod::wild){
      std::cout << "  Note: Using modifier \"wild\"";
    }
    else if(modifier == RollMod::consistant){
      std::cout << "  Note: Using modifier \"consistant\"";
    }
    else if(modifier == RollMod::maximized){
      std::cout << "  Note: Using modifier \"maximized\"";
    }
    else if(modifier == RollMod::advantage){
      std::cout << "  Note: Using modifier \"advantage\"";
    }
    else if(modifier == RollMod::disadvantage){
      std::cout << "  Note: Using modifier \"disadvantage\"";
    }

    std::cout << "\n";
  }
  return (total);
}
