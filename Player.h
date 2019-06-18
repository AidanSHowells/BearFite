#ifndef PLAYER_H
#define PLAYER_H

#include <array>
#include <vector>
#include <SFML/System/String.hpp>
#include "Abilities.h"
#include "Body.h"
#include "Feats.h"

class Bear;
class BattleHUD;
class MessageBox;
enum class BearID;
enum class SpellID;
enum class SpellSchool;
enum class TurnOf;
enum class FeatID;

enum class Action {nothing, leg, eye, john_hopkins, quaff, cast, flee};

struct SpellTree{//NOTE: See SpellList.cpp for function definitions
  SpellTree(const SpellID spellID);
  std::array<SpellID, 3> spellIDList;
  std::array<int, 3> numSpells = {3,0,0};
  std::array<int, 3> maxSpells = {3,0,0};
  void IncrementCount(int index);
};

class Player{
  public:
    Player();
    void SetMessageBox(MessageBox& theMessages);
    int GetHealth();
    int GetMaxHealth();
    int GetNumDranks() const {return numDranks;}
    int GetExpNeeded() const {return expNeeded;}
    int GetLevel() const {return level;}
    int GetBaseAttackBonus() const {return baseAttackBonus;}
    int GetBodyCount() const {return bodyCount;}
    void IncrementBodyCount() {bodyCount++;}
    int GetNumVirginities() const {return numVirginities;}
    sf::String GetLastBear() const {return lastBear;}
    void SetLastBear(const sf::String bearName){lastBear = bearName;}
    int GetAbil(const int index, const bool isCheckingDeath = false) const;
    void BuffAbil(const int index, const int buff);
    int GetAC(const BearID attacker) const; //Combines all AC-affecting factors
    void Hurt(int); //How the bear injures the player
    bool IsDead();
    TurnOf TakeAction(const Action theAction,
                      Bear& theBear,
                      std::vector<Bear*> enemyBears);
    TurnOf Cast(const int index, BattleHUD& environment);
    int GetSpellcastingLevel(){return spellcastingLevel;}
    int GetSpellSchoolBonus(const SpellSchool school);
    int GetNumSpellTrees(){return spellList.size();}
    sf::String GetSpellName(const int index);
    int GetNumSpell(const int index);
    int GetMaxNumSpell(const int index);
    bool HasSpell(const SpellID theSpell) const;
    void UnlockSpellTree(SpellTree tree);
    bool TouchAttackSucceeds(const Bear& bear) const;
    void MakeSweetLove();
    void TimerTick();

    void AddExp(int exp){expNeeded -= exp;}
    void LevelUp();
    void IncrementBaseAttackBonus(){baseAttackBonus++;}
    void IncrementSpellcastingLevel(){spellcastingLevel++;}
    void FindDranks(int dranks){numDranks += dranks;}
    void PostBattleReset();

    void AddFeat(const FeatID theFeat, const BearID theBear);
    int GetNumRegularFeats() const {return mainFeatList.size();}
    int GetNumExtraFeats() const {return extraFeatList.size();}
    sf::String GetRegularFeat(const int index) const;
    sf::String GetExtraFeat(const int index) const;
    bool FeatIsToggleable(const int index) const;
    int FeatCost(const int index) const {return mainFeatList.at(index).cost;}
    int GetPower() const {return power;}
    int GetPowerPoolSize() const {return powerPoolSize;}
    bool ShowPower() const {return mainFeatList.size() > 0 && FeatCost(0) > 0;}
    TurnOf ActivateFeat(const int index);
    void ToggleFeat(const int index);
    bool FeatIsActive(const int index) const;
    bool HasFeat(FeatID theFeat, bool checkIfActive) const;
    bool HasFeat(FeatID theFeat, BearID theBear, bool checkIfActive) const;

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
    void ClearFeats(){mainFeatList.clear(); extraFeatList.clear();}//TEMP
    void SetLevel(int newLevel){level = newLevel;}//TEMP
    void SetBaseAttackBonus(int newBAB){baseAttackBonus = newBAB;}//TEMP
    void SetSpellcastingLevel(int newLevel){spellcastingLevel = newLevel;}//TEMP
    void SetAbil(std::array<int,int(Abil::NUM_ABIL)> newAbil);//TEMP
  private:
    MessageBox* Messages; //So damage statements know where to print
    std::array<int, int(Abil::NUM_ABIL)> baseAbil = {10,10,10,10,10,10};
    std::array<int, int(Abil::NUM_ABIL)> abilBuff = {0,0,0,0,0,0};
    std::vector<SpellTree> spellList;
    std::vector<Feat> mainFeatList;
    std::vector<Feat> extraFeatList;

    Body body;
    int maxHealth;
    int health;

    int numDranks = 5;
    int level = 0;
    const int baseExp = 20;
    int expNeeded = baseExp;
    int bodyCount = 0;
    int numVirginities = 0;
    int baseAttackBonus = 0; //This will be level-based
    int baseAC = 30; //This will be level-based
    int armor = 0; //This will be determined by equipped items and magic
    int legCritThreat = 1;
    int eyeCritThreat = 3;
    int spellcastingLevel = 0;
    int power = 4;
    int powerPoolSize = 4;

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
    void LegPunch(Bear& bear);
    void EyePunch(Bear& bear);
    TurnOf Quaff();
    TurnOf Flee(Bear& bear);

    void Toggle(const FeatID theFeat);
    void Toggle(const FeatID theFeat, const BearID theBear);

    sf::String lastBear = sf::String("None ");
};

#endif
