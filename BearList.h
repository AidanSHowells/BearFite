#ifndef BEARLIST_H
#define BEARLIST_H

#include "Bear.h"
#include "RollDice.h"


//Babby Bear
class BabbyBear : public Bear{
  public:
    BabbyBear(){
      name = sf::String("Babby ");
      SetAbil(6, 12, 7, 1, 3, 6);
      level = std::max(0, Roll(1,6) - 4); //babby occasionally has a level
      health = 20 + Roll(level,6) + HealthBonus();
      baseAttackBonus = level;
      baseAC = 35 + level;
      armor = 0;
    }
};

//Black Bear
class BlackBear : public Bear{
  public:
    BlackBear(){
      name = sf::String("Black ");
      SetAbil(10, 17, 12, 7, 5, 8);
      level = std::max(1, Roll(1,6) - 3);
      health = 20 + Roll(level,6) + HealthBonus();
      baseAttackBonus = level;
      baseAC = 30 + level;
      armor = 0;
    }
};

//Brown Bear
class BrownBear : public Bear{
  public:
    BrownBear(){
      name = sf::String("Brown ");
      SetAbil(16, 7, 16, 5, 5, 10);
      level = std::max(1, Roll(1,6) - 3);
      health = 20 + Roll(level,6) + HealthBonus();
      baseAttackBonus = level;
      baseAC = 30 + level;
      armor = 0;
    }
};

//Polar Bear
class PolarBear : public Bear{
  public:
    PolarBear(){
      name = sf::String("Polar ");
      SetAbil(16, 2, 21, 3, 3, 4);
      level = std::max(1, Roll(1,6) - 3);
      health = 30 + Roll(level,8) + HealthBonus();
      baseAttackBonus = -15 + level;
      baseAC = 25 + level;
      armor = 0;
    }
};



//TEMP: Belongs in its own file
Bear FindBear(sf::Keyboard::Key theKey){
  if(sf::Keyboard::Q == theKey){
    BabbyBear bear;
    return bear;
  }
  else if(sf::Keyboard::W == theKey){
    BlackBear bear;
    return bear;
  }
  else if(sf::Keyboard::E == theKey){
    BrownBear bear;
    return bear;
  }
  else{
    PolarBear bear;
    return bear;
  }
}
//end TEMP

#endif
