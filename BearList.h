#ifndef BEARLIST_H
#define BEARLIST_H

#include "Bear.h"
#include "RollDice.h"
#include <algorithm>//for std::max and std::min

//Babby Bear
class BabbyBear : public Bear{
  public:
    BabbyBear(){
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
      canBeFought = true;
    }
};

//Black Bear
class BlackBear : public Bear{
  public:
    BlackBear(){
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
      canBeFought = true;
    }
};

//Brown Bear
class BrownBear : public Bear{
  public:
    BrownBear(){
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
      canBeFought = true;
    }
};

//Polar Bear
class PolarBear : public Bear{
  public:
    PolarBear(){
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
      canBeFought = true;
    }
};



//TEMP: Belongs in FindBear.cpp
#include "HUD.h"

void FindBear(sf::Keyboard::Key& theKey, HUD& theHUD){
  Bear theBear[4];
  bool isRandom = (sf::Keyboard::Z == theKey);
  if(isRandom){
    const int tempInt = Roll(1,4);
    if(tempInt == 1){
      theKey = sf::Keyboard::Q;
    }
    if(tempInt == 2){
      theKey = sf::Keyboard::W;
    }
    if(tempInt == 3){
      theKey = sf::Keyboard::E;
    }
    if(tempInt == 4){
      theKey = sf::Keyboard::R;
    }
  }
  if(sf::Keyboard::Q == theKey){
    BabbyBear bear;
    theBear[0] = bear;
  }
  else if(sf::Keyboard::W == theKey){
    BlackBear bear;
    theBear[0] = bear;
  }
  else if(sf::Keyboard::E == theKey){
    BrownBear bear;
    theBear[0] = bear;
  }
  else if(sf::Keyboard::R == theKey){
    PolarBear bear;
    theBear[0] = bear;
  }
  else if(sf::Keyboard::A == theKey){
    for(int i = 0; i < 4; i++){
      BabbyBear bear;
      theBear[i] = bear;
    }
    theHUD.AddEnemyBears(theBear, 4);
    return;//This is gross, but this whole part of the function is temporary
  }
  else{
    theHUD.messages.Update(sf::String("Whoops! That key is"),
                           sf::String("not supported."));
  }
  if(isRandom){
    int randInt = Roll(1, int(ModifierIs::SIZE)) - 1;
    if(1 == Roll(1,3)){
      randInt = 0;
    }
    Modifier mod = GetModifier(ModifierIs(randInt));

    //Functions can't return C-style arrays, so we have to get "creative":
    std::array<Bear, 4> bears = theBear[0].ApplyModifier(mod);
    for(int i = 0; i < 4; i++){
      theBear[i] = bears.at(i);
    }

    int numBears = 1 + mod.numTwins;//For the moment
    //int numBears = 1 + mod.numCompanians + mod.numTwins;//Eventually
    theHUD.AddEnemyBears(theBear, numBears);
  }
  else{
    theHUD.AddEnemyBears(theBear, 1);
  }
}
//Eventual Algorithm:
//Make vector of bears whose base level is small enough
//Choose a bear from the vector at random
//Some (25% ?) chance of no modifier. Else:
  //Make vector of modifiers whose effective level is small enough (none, etc.)
  //Choose a modifier from the vector at random


//end TEMP (Belongs in FindBear.cpp)


//TEMP: Belongs in ModifierList.cpp
#include <iostream> //for std::cerr
#include "ModifierList.h"

Modifier GetModifier(ModifierIs identifier){
  Modifier theModifier;
  if(ModifierIs::none == identifier){
    //Do nothing
  }
  else if(ModifierIs::beefy == identifier){
    Beefy tempMod;
    theModifier = tempMod;
  }
  else if(ModifierIs::exact == identifier){
    Exact tempMod;
    theModifier = tempMod;
  }
  else if(ModifierIs::sturdy == identifier){
    Sturdy tempMod;
    theModifier = tempMod;
  }
  else if(ModifierIs::genious == identifier){
    Genious tempMod;
    theModifier = tempMod;
  }
  else if(ModifierIs::socrates == identifier){
    Socrates tempMod;
    theModifier = tempMod;
  }
  else if(ModifierIs::handsome == identifier){
    Handsome tempMod;
    theModifier = tempMod;
  }
  else if(ModifierIs::numerous == identifier){
    Numerous tempMod;
    theModifier = tempMod;
  }
  else if(ModifierIs::experienced == identifier){
    Experienced tempMod;
    theModifier = tempMod;
  }
  else if(ModifierIs::keen == identifier){
    Keen tempMod;
    theModifier = tempMod;
  }
  else if(ModifierIs::crictal == identifier){
    Crictal tempMod;
    theModifier = tempMod;
  }
  else if(ModifierIs::SIZE == identifier){
    std::cerr << "Warning! ";
    std::cerr << "Attempted use of ModifierIs::SIZE in GetModifier() function.";
    std::cerr << std::endl;
  }
  else{
    std::cerr << "Warning! ";
    std::cerr << "Attempted use of modifier unknown to GetModifier() function.";
    std::cerr << std::endl;
  }
  return theModifier;
}


//end TEMP (Belongs in ModifierList.cpp)

#endif
