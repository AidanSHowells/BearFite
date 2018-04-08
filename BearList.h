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
void FindBear(sf::Keyboard::Key& theKey, HUD& theHUD){
  Bear theBear[4];
  if(sf::Keyboard::Z == theKey){
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
    theHUD.AddEnemyBears(theBear, 1);
  }
  else if(sf::Keyboard::W == theKey){
    BlackBear bear;
    theBear[0] = bear;
    theHUD.AddEnemyBears(theBear, 1);
  }
  else if(sf::Keyboard::E == theKey){
    BrownBear bear;
    theBear[0] = bear;
    theHUD.AddEnemyBears(theBear, 1);
  }
  else if(sf::Keyboard::R == theKey){
    PolarBear bear;
    theBear[0] = bear;
    theHUD.AddEnemyBears(theBear, 1);
  }
  else if(sf::Keyboard::A == theKey){
    for(int i = 0; i < 4; i++){
      BabbyBear bear;
      theBear[i] = bear;
    }
    //theHUD.AddEnemyBears(&theBear[0], &theBear[1], &theBear[2], &theBear[3]);
    theHUD.AddEnemyBears(theBear, 4);
  }
  else{
    theHUD.messages.Update(sf::String("Whoops! That key is"),
                           sf::String("not supported."));
  }
}
//end TEMP

#endif
