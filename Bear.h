#ifndef BEAR_H
#define BEAR_H

#include "Messages.h"

class Player;

class Body{
  public:
    int baseHealth = 420;
    int hitDieSize = 0;
    int UpdateHealth(int newHealth, int newLevel, int newCON);
  private:
    int health;
    int level = 0;
    int CON = 10;
    std::vector<int> hitDice;
    int HealthBonus(int constitution){return (constitution - 10) * 2;}
};

class Bear{
  public:
    void SetMessageBox(MessageBox& theMessages);
    int AC(Action);
    sf::String GetName();
    sf::String GetModifier();
    void Bash(Player& thePlayer);
    void Hurt(int); //how the player lowers the bear's health
    int GetHealth();
    bool IsDead(){return(health <= 0);}//Add extra death conditions to this func
    bool CanBeFought(){return canBeFought;}
  protected:
    MessageBox* Messages; //So damage statements know where to print
    sf::String name = sf::String("Klepto");
    sf::String modifier = sf::String("Horse Defense");
    int abil[6] = {10, 10, 10, 10, 10, 10};

    int health;
    Body body;
    void SetHealth();

    int baseAttackBonus = 0;
    int baseAC = 30;
    int eyeACBonus = 0;
    int armor = 0;
    int level = 0;
    int critThreat = 0; //how likely the bear is to crit
    int critMult = 1; //how painful the bear criticals are
    int AttackBonus();
    int DamageBonus();
    bool canBeFought = false;
    void SetAbil(int STR, int DEX, int CON, int INT, int WIS, int CHR);
};

#endif
