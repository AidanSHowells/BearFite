#include <iostream> //for std::cerr
#include <algorithm>//for std::max and std::min
#include "RollDice.h"
#include "Bear.h"

Bear::Bear(const BearID bearID){
  identifier = bearID;
  if(bearID == BearID::Babby){
    name = sf::String("Babby ");
    SetAbil(4, 12, 7, 1, 3, 6);
    level = std::max(0, Roll(1,6) - 4); //babby occasionally has a level
    body.hitDieSize = 6;
    body.baseHealth = 20;

    SetHealth();
    baseAttackBonus = level;
    baseAC = 35 + level;
    eyeACBonus = 20;
    armor = 0;
    critThreat = 0;
    critMult = 2;
  }
  else if(bearID == BearID::Black){
    name = sf::String("Black ");
    SetAbil(8, 17, 12, 7, 5, 8);
    level = std::max(1, Roll(1,6) - 3);
    body.hitDieSize = 6;
    body.baseHealth = 20;

    SetHealth();
    baseAttackBonus = level;
    baseAC = 30 + level;
    eyeACBonus = 20;
    armor = 0;
    critThreat = 3 + level/5;
    critMult = 2;
  }
  else if(bearID == BearID::Brown){
    name = sf::String("Brown ");
    SetAbil(14, 7, 16, 5, 5, 10);
    level = std::max(1, Roll(1,6) - 3);
    body.hitDieSize = 6;
    body.baseHealth = 20;

    SetHealth();
    baseAttackBonus = level;
    baseAC = 30 + level;
    eyeACBonus = 20;
    armor = 0;
    critThreat = 2;
    critMult = 3;
  }
  else if(bearID == BearID::Polar){
    name = sf::String("Polar ");
    SetAbil(14, 2, 21, 3, 3, 4);
    level = std::max(1, Roll(1,6) - 3);
    body.hitDieSize = 10;
    body.baseHealth = 30;

    SetHealth();
    baseAttackBonus = -15 + level;
    baseAC = 25 + level;
    eyeACBonus = 20;
    armor = 0;
    critThreat = 0;
    critMult = 5;
  }
  else if(bearID == BearID::NUM_BEARS){
    std::cerr << "Warning! ";
    std::cerr << "Attempted use of BearID::NUM_BEARS in constructor.\n\n";
  }
  else{
    std::cerr << "Warning! ";
    std::cerr << "Attempted use of BearID unknown to constructor.\n";
    std::cerr << "The number corresponding to the invalid BearID was ";
    std::cerr << int(bearID) << ".\n\n";
  }
}
