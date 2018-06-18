#include "Body.h"
#include "RollDice.h"

int Body::UpdateHealth(int newHealth, int newLevel, int newCON, int newVirgin){
  health = newHealth;

  if(level < newLevel){
    //Roll any missing hit dice
    for(int i = hitDice.size(); i < newLevel; i++){
      hitDice.push_back(Roll(1,hitDieSize));
    }
    for(int i = level; i < newLevel; i++){
      health += hitDice.at(i);
    }
  }
  if(level > newLevel){
    for(int i = newLevel; i < level; i++){
      health -= hitDice.at(i);
    }
  }
  health = health - HealthBonus(CON) + HealthBonus(newCON);
  health = health - (-2) * numVirgin + (-2) * newVirgin;//newVirgin default is 0

  level = newLevel;
  CON = newCON;
  numVirgin = newVirgin;
  return health;
}
