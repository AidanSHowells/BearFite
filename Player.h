#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include "Messages.h"
#include "Abilities.h"

class Bear;
enum class SpellID;
enum class SpellSchool;


class Player{
  public:
    void SetMessageBox(MessageBox& theMessages);
    int GetHealth();
    int GetMaxHealth();
    int GetNumDranks();
    int GetAbil(int i){return abil.at(i);}
    void SetAbil(std::array<int,int(Abil::NUM_ABIL)> newAbil);
    int AC(); //Combines all AC-affecting factors
    void Hurt(int); //How the bear injures the player
    bool IsDead(){return(health <= 0);}//Add extra death conditions to this func
    TurnOf TakeAction(Action theAction, Bear& theBear);
    int GetSpellcastingLevel(){return spellcastingLevel;}
    int GetSpellSchoolBonus(const SpellSchool school);
    int GetNumSpellTrees(){return 7;/*TEMP*/}
    sf::String GetSpellName(const int index);
    int GetNumSpell(const int index);
    int GetMaxNumSpell(const int index);
    bool TouchAttack(Bear bear);
    void MakeSweetLove();
    void Heal(){Quaff();}//TEMP
    void Replenish(){numDranks++;}//TEMP
  private:
    MessageBox* Messages; //So damage statements know where to print
    std::array<int, int(Abil::NUM_ABIL)> abil = {10,10,10,10,10,10};
    int HealthBonus(); //Calculates increased health from intrinsics
    int maxHealth = 50 + HealthBonus();
    int health = maxHealth;
    int numDranks = 5;
    int numVirginities = 0;
    int baseAttackBonus = 0; //This will be level-based
    int baseAC = 30; //This will be level-based
    int armor = 0; //This will be determined by equipped items and magic
    int legCritThreat = 1;
    int eyeCritThreat = 3;
    int spellcastingLevel;
    int LegAttackBonus(); //Calculates attack bonus with abilities etc.
    int LegDamageBonus(); // Same for damage
    int EyeAttackBonus();
    int EyeDamageBonus();
    int TouchAttackBonus();
    TurnOf LegPunch(Bear& bear);
    TurnOf EyePunch(Bear& bear);
    TurnOf Quaff();
};

#endif
