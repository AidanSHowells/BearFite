#ifndef BODY_H
#define BODY_H

#include <vector>

class Body{
  public:
    int baseHealth = 420;
    int hitDieSize = 0;
    int UpdateHealth(int newHealth,
                     int newLevel,
                     int newCON,
                     int newVirgin = 0);
  private:
    int health;
    int level = 0;
    int CON = 10;
    int numVirgin = 0;
    std::vector<int> hitDice;
    int HealthBonus(int constitution){return (constitution - 10) * 2;}
};

#endif
