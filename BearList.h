#ifndef BEARLIST_H
#define BEARLIST_H

#include "Bear.h"


//Babby Bear
class BabbyBear : public Bear{
  public:
    BabbyBear(){
      name = sf::String("Babby ");
      health = 20;
      baseAttackBonus = 0;
      baseAC = 30;
      armor = 0;
    }
};

//Black Bear
class BlackBear : public Bear{
  public:
    BlackBear(){
      name = sf::String("Black ");
      health = 40;
      baseAttackBonus = 5;
      baseAC = 30;
      armor = 0;
    }
};

//Brown Bear
class BrownBear : public Bear{
  public:
    BrownBear(){
      name = sf::String("Brown ");
      health = 50;
      baseAttackBonus = 0;
      baseAC = 30;
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
  else{
    BrownBear bear;
    return bear;
  }
}
//end TEMP

#endif
