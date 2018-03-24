#ifndef BEAR_H
#define BEAR_H

#include "HUD.h"

class Player;

class BearOutline{
  public:
    void SetAbil(int STR, int DEX, int CON, int INT, int WIS, int CHA);
    sf::String name = sf::String("Klepto");
    int abil[6] = {10, 10, 10, 10, 10 ,10};
    int maxHealth = 40;
    int baseAttackBonus = 0;
    int baseAC = 10;
    int armor = 0;
};

class Bear{
  public:
    Bear(){}
    Bear(BearOutline theBearOutline);
    /*
    void SetMaxHealth(int newMaxHealth);
    void SetBaseAttackBonus(int newBaseAttackBonus);
    void SetBaseAC(int newBaseAC);
    void SetArmor(int newArmor);
    void SetName(sf::String newName);
    */
    void SetMessageBox(MessageBox& theMessages);
    int AC();
    sf::String GetName();
    void Bash(Player& thePlayer);
    void Hurt(int); //how the player lowers the bear's health
    int GetHealth();
    void ShowHealth(); //TEMP
  private:
    MessageBox* Messages; //So damage statements know where to print
    sf::String name = sf::String("Klepto");
    int abil[6] = {10, 10, 10, 10, 10 ,10};
    int maxHealth = 40;
    int health = maxHealth;
    int baseAttackBonus = 0;
    int baseAC = 10;
    int armor = 0;
    int AttackBonus();
    int DamageBonus();
};

#endif
