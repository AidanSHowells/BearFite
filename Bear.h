#ifndef BEAR_H
#define BEAR_H

#include "HUD.h"

class Player;

class Bear{
  public:
    void SetMessageBox(MessageBox& theMessages);
    int AC();
    sf::String GetName();
    void Bash(Player& thePlayer);
    void Hurt(int); //how the player lowers the bear's health
    int GetHealth();
    void ShowHealth(); //TEMP
  protected:
    MessageBox* Messages; //So damage statements know where to print
    sf::String name = sf::String("Klepto");
    int abil[6] = {10, 10, 10, 10, 10, 10};
    //int maxHealth = 420;
    int health = 420;
    int baseAttackBonus = 0;
    int baseAC = 10;
    int armor = 0;
    int AttackBonus();
    int DamageBonus();
};

#endif
