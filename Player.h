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
enum class TurnOf;

enum class Action {nothing, leg, eye, john_hopkins, quaff, cast, flee};

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
    int GetAbil(const int index, const bool isCheckingDeath = false) const;
    void BuffAbil(const int index, const int buff);
    int GetAC() const; //Combines all AC-affecting factors
    void Hurt(int); //How the bear injures the player
    bool IsDead();
    TurnOf TakeAction(const Action theAction, Bear& theBear);
    TurnOf Cast(const int index, BattleHUD& environment);
    int GetSpellcastingLevel(){return spellcastingLevel;}
    int GetSpellSchoolBonus(const SpellSchool school);
    int GetNumSpellTrees(){return spellList.size();}
    sf::String GetSpellName(const int index);
    int GetNumSpell(const int index);
    int GetMaxNumSpell(const int index);
    void UnlockSpellTree(SpellTree tree);
    bool TouchAttackSucceeds(const Bear& bear) const;
    void MakeSweetLove();
    void TimerTick();
    void PostBattleReset();

    void Haste(int time){hastedTime = std::max(time, hastedTime);}
    void Slow(int time){slowedTime = std::max(time, slowedTime);}
    void Paralyze(int time){paralyzedTime = std::max(time, paralyzedTime);}
    void Rage(int time){ragingTime = std::max(time, ragingTime);}
    void WarCry(int time){warCryingTime = std::max(time, warCryingTime);}
    void BigFist(int time){bigFistTime = std::max(time, bigFistTime);}
    void EnterSantuary(int time){santuaryTime = std::max(time, santuaryTime);}
    void StopTime(int time){timeStopTime = std::max(time, timeStopTime);}

    bool IsHasted() const {return (hastedTime > 0);}
    bool IsSlowed() const {return (slowedTime > 0);}
    bool IsParalyzed() const {return (paralyzedTime > 0);}
    bool IsRaging() const {return (ragingTime > 0);}
    bool IsWarCrying() const {return (warCryingTime > 0);}
    bool HasBigFist() const {return (bigFistTime > 0);}
    bool IsSafe() const {return (santuaryTime > 0);}
    bool HasStoppedTime() const {return (timeStopTime > 0);}

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
    int spellcastingLevel = 0;

    int hastedTime = 0;
    int slowedTime = 0;
    int paralyzedTime = 0;
    int ragingTime = 0;
    int warCryingTime = 0;
    int bigFistTime = 0;
    int santuaryTime = 0;
    int timeStopTime = 0;

    int GetLegAttackBonus() const; //Calculates attack bonus with abilities etc.
    int GetLegDamageBonus() const; // Same for damage
    int GetEyeAttackBonus() const;
    int GetEyeDamageBonus() const;
    int GetTouchAttackBonus() const;
    TurnOf LegPunch(Bear& bear);
    TurnOf EyePunch(Bear& bear);
    TurnOf Quaff();
    TurnOf Flee(Bear& bear);
};

#endif
