#ifndef BEARLIST_H
#define BEARLIST_H

#include "Bear.h"
#include "RollDice.h"
#include <algorithm>//for std::max and std::min

//List of all bears that can appear (plus NUM_BEARS, which MUST be last):
enum class BearID{Babby, Black, Brown, Polar, NUM_BEARS};

Bear GetBear(const BearID identifier);

//Babby Bear
class BabbyBear : public Bear{
  public:
    BabbyBear(){
      name = sf::String("Babby ");
      identifier = BearID::Babby;
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
      identifier = BearID::Black;
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
      identifier = BearID::Brown;
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
      identifier = BearID::Polar;
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
#include "Bear.h"
#include "ModifierList.h"

bool FindBear(const sf::Keyboard::Key theKey,
              BattleHUD& theHUD,
              const BearID bearID,
              const ModifierID modID)
{
  Bear theBear[4];
  Modifier theModifier = GetModifier(ModifierID::none);

  if(sf::Keyboard::Z == theKey){//Random Bear
    int randInt = Roll(1, int(BearID::NUM_BEARS)) - 1;
    theBear[0] = GetBear(BearID(randInt));

    randInt = Roll(1, int(ModifierID::SIZE)) - 1;
    if(1 == Roll(1,3)){
      randInt = 0;
    }
    theModifier = GetModifier(ModifierID(randInt));
  }
  else if(sf::Keyboard::Q == theKey){//Babby Party
    for(int i = 0; i < 4; i++){
      BabbyBear bear;
      theBear[i] = bear;
    }
    theHUD.AddEnemyBears(theBear, 4);
    return true;//This is gross, but this part of the function is temporary
  }
  else if(sf::Keyboard::F == theKey){//Special Bear
    theBear[0] = GetBear(bearID);
    theModifier = GetModifier(modID);
  }
  else{
    theHUD.messages.Update(sf::String("Whoops! That key is"),
                           sf::String("not supported."));
    return false;//Failure
  }

  //Functions can't return C-style arrays, so we have to get "creative":
  std::array<Bear, 4> bears = theBear[0].ApplyModifier(theModifier);
  for(int i = 0; i < 4; i++){
    theBear[i] = bears.at(i);
  }

  int numBears = 1 + theModifier.numTwins;//To be replaced with the next line
  //int numBears = 1 + theModifier.numCompanians + theModifier.numTwins;
  theHUD.AddEnemyBears(theBear, numBears);
  return true;//Success
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

Modifier GetModifier(ModifierID identifier){
  Modifier theModifier;
  if(ModifierID::none == identifier){
    //Do nothing
  }
  else if(ModifierID::beefy == identifier){
    theModifier = Beefy();
  }
  else if(ModifierID::exact == identifier){
    theModifier = Exact();
  }
  else if(ModifierID::sturdy == identifier){
    theModifier = Sturdy();
  }
  else if(ModifierID::genious == identifier){
    theModifier = Genious();
  }
  else if(ModifierID::socrates == identifier){
    theModifier = Socrates();
  }
  else if(ModifierID::handsome == identifier){
    theModifier = Handsome();
  }
  else if(ModifierID::numerous == identifier){
    theModifier = Numerous();
  }
  else if(ModifierID::experienced == identifier){
    theModifier = Experienced();
  }
  else if(ModifierID::keen == identifier){
    theModifier = Keen();
  }
  else if(ModifierID::crictal == identifier){
    theModifier = Crictal();
  }
  else if(ModifierID::SIZE == identifier){
    std::cerr << "Warning! ";
    std::cerr << "Attempted use of ModifierID::SIZE in GetModifier() function.";
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

//Begin TEMP (Belongs in BearList.cpp)
#include <iostream> //for std::cerr

Bear GetBear(const BearID identifier){
  Bear bear;
  if(identifier == BearID::Babby){
    bear = BabbyBear();
  }
  else if(identifier == BearID::Black){
    bear = BlackBear();
  }
  else if(identifier == BearID::Brown){
    bear = BrownBear();
  }
  else if(identifier == BearID::Polar){
    bear = PolarBear();
  }
  else if(identifier == BearID::NUM_BEARS){
    std::cerr << "Warning! ";
    std::cerr << "Attempted use of BearID::NUM_BEARS in GetBear() function.\n";
  }
  else{
    std::cerr << "Warning! ";
    std::cerr << "Attempted use of BearID unknown to GetBear() function.\n";
  }
  return bear;
}
//end TEMP (Belongs in BearList.cpp)

#endif
