#ifndef BEAR_H
#define BEAR_H

#include "HUD.h"

class Player;

class Bear{
  public:
    void SetMessageBox(MessageBox& theMessages);
    int AC();
    sf::String GetName();
    void Bash(Player);
    void Hurt(int); //how the player lowers the bear's health
    int GetHealth();
    void ShowHealth(); //TEMP
  private:
    MessageBox* Messages; //So damage statements know where to print
    int abil[6] = {10, 10, 10, 10, 10 ,10};
    int maxHealth = 40;
    int health = maxHealth;
    int BaseAttackBonus = 0;
    int BaseAC = 10;
    int Armor = 0;
    int AttackBonus();
    int DamageBonus();
};

#endif
