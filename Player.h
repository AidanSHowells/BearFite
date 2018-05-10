#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include "Messages.h"

class Bear;


class Player{
  public:
    void SetMessageBox(MessageBox& theMessages);
    int GetHealth();
    int GetMaxHealth();
    int GetNumDranks();
    int GetAbil(int i){return abil[i];}//FIXME:Should probably validate input
    void SetAbil(std::array<int,6> newAbil);
    //void Quaff();
    int AC(); //Combines all AC-affecting factors
    void Hurt(int); //How the bear injures the player
    bool IsDead(){return(health <= 0);}//Add extra death conditions to this func
    TurnOf TakeAction(Action theAction, Bear& theBear);
    void Heal(){Quaff();}//TEMP
    void Replenish(){numDranks++;}//TEMP
  private:
    MessageBox* Messages; //So damage statements know where to print
    int abil[6] = {10, 10, 10, 10, 10, 10}; //STR, DEX, CON, INT, WIS, CHR
    int HealthBonus(); //Calculates increased health from intrinsics
    int maxHealth = 50 + HealthBonus();
    int health = maxHealth;
    int numDranks = 5;
    int baseAttackBonus = 0; //This will be level-based
    int baseAC = 30; //This will be level-based
    int armor = 0; //This will be determined by equipped items and magic
    int legCritThreat = 1;
    int eyeCritThreat = 3;
    int LegAttackBonus(); //Calculates attack bonus with abilities etc.
    int LegDamageBonus(); // Same for damage
    int EyeAttackBonus();
    int EyeDamageBonus();
    TurnOf LegPunch(Bear& bear);
    TurnOf EyePunch(Bear& bear);
    TurnOf Quaff();
};

#endif
