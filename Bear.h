#ifndef BEAR_H
#define BEAR_H

#include "Messages.h"

class Player;
class HUD;


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

    int baseHealth = 420;
    std::vector<int> hitDice;
    int SumDice();
    int health = 420;
    int hitDieSize = 6;
    int MaxHealth();
    void SetHealth();

    int baseAttackBonus = 0;
    int baseAC = 30;
    int eyeACBonus = 0;
    int armor = 0;
    int level = 0;
    int HealthBonus();
    int AttackBonus();
    int DamageBonus();
    bool canBeFought = false;
    void SetAbil(int STR, int DEX, int CON, int INT, int WIS, int CHR);
};

#endif
