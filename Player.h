#ifndef PLAYER_H
#define PLAYER_H

#include "HUD.h"
#include <string>//For std::to_string

class Bear;

class Player{
  public:
    Player(MessageBox& theMessages);
    int AC(); //Combines all AC-affecting factors
    void LegPunch(Bear&);
    void Hurt(int); //How the bear injures the player
  private:
    MessageBox* Messages; //So damage statements know where to print
    int abil[6] = {10, 10, 10, 10, 10 ,10}; //STR, DEX, CON, INT, WIS, CHR
    int maxHealth = 40;
    int health = maxHealth;
    int BaseAttackBonus = 0; //This will be level-based
    int BaseAC = 10; //This will be level-based
    int Armor = 0; //This will be determined by equipped items and magic
    int LegAttackBonus(); //Calculates attack bonus with abilities etc.
    int LegDamageBonus(); // Same for damage
};

#endif
