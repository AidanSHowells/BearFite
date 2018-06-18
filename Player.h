#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include <vector>
#include "HUD.h"
#include "Abilities.h"
#include "Body.h"

class Bear;
enum class SpellID;
enum class SpellSchool;

struct SpellTree{
  SpellTree(const SpellID spellID);//NOTE: See SpellList.cpp for definition
  std::array<SpellID, 3> spellIDList;
  std::array<int, 3> numSpells = {3,0,0};
  std::array<int, 3> maxSpells = {3,0,0};
};

class Player{
  public:
    Player();
    void SetMessageBox(MessageBox& theMessages);
    int GetHealth();
    int GetMaxHealth();
    int GetNumDranks();
    int GetAbil(int index);
    void BuffAbil(int index, int buff);
    int AC(); //Combines all AC-affecting factors
    void Hurt(int); //How the bear injures the player
    bool IsDead(){return(health <= 0);}//Add extra death conditions to this func
    TurnOf TakeAction(Action theAction, Bear& theBear);
    TurnOf Cast(const int index, BattleHUD& environment);
    int GetSpellcastingLevel(){return spellcastingLevel;}
    int GetSpellSchoolBonus(const SpellSchool school);
    int GetNumSpellTrees(){return spellList.size();}
    sf::String GetSpellName(const int index);
    int GetNumSpell(const int index);
    int GetMaxNumSpell(const int index);
    void UnlockSpellTree(SpellTree tree);
    bool TouchAttack(Bear bear);
    void MakeSweetLove();

    //Temporary? methods used in BattleTest.cpp
    void Heal(){Quaff();}//TEMP
    void Replenish(){numDranks++;}//TEMP
    void ClearSpells(){spellList.clear();}//TEMP
    void SetSpellcastingLevel(int newLevel){spellcastingLevel = newLevel;}//TEMP
    void SetAbil(std::array<int,int(Abil::NUM_ABIL)> newAbil);//TEMP
  private:
    MessageBox* Messages; //So damage statements know where to print
    std::array<int, int(Abil::NUM_ABIL)> baseAbil = {10,10,10,10,10,10};
    std::array<int, int(Abil::NUM_ABIL)> abilBuff = {0,0,0,0,0,0};
    std::vector<SpellTree> spellList;

    Body body;
    int maxHealth;
    int health;

    int numDranks = 5;
    int level = 0;
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
