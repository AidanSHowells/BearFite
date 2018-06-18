#ifndef BEAR_H
#define BEAR_H

#include <array>//For std::array
#include "Messages.h"
#include "Modifier.h"
#include "Abilities.h"
#include "Body.h"

class Player;

//List of all bears that can appear (plus NUM_BEARS, which MUST be last):
enum class BearID{Babby, Black, Brown, Polar, NUM_BEARS};

enum class SaveType;

class Bear{
  public:
    Bear(){canBeFought = false;}
    Bear(const BearID bearID);
    void SetMessageBox(MessageBox& theMessages);
    int AC(Action);
    sf::String GetName() const;
    BearID GetID(){return identifier;}
    sf::String GetModifier();
    void Bash(Player& thePlayer);
    void Hurt(int); //how the player lowers the bear's health
    int GetHealth();
    int GetSave(const SaveType saveType);
    int GetAbil(int index){return abil.at(index);}
    void DrainAbil(int ability, int drain);
    void MakeSweetLove(){isLove = true;}
    bool IsLove(){return isLove;}
    bool IsDead(){return(health <= 0);}//Add extra death conditions to this func
    bool IsSlowed(){return (slowedTime > 0);}
    bool IsParalyzed(){return (paralyzedTime > 0);}
    bool IsHasted(){return (hastedTime > 0);}
    void Slow(int time){slowedTime = time;}
    void Paralyze(int time){paralyzedTime = time;}
    void Haste(int time){hastedTime = time;}
    void TimerTick();
    bool CanBeFought(){return canBeFought;}
    std::array<Bear, 4> ApplyModifier(Modifier mod, bool isDerived = false);
  protected:
    MessageBox* Messages; //So damage statements know where to print
    sf::String name = sf::String("Klepto");
    BearID identifier;
    Modifier modifier;
    Modifier modifier2;
    std::array<int, int(Abil::NUM_ABIL)> abil = {10,10,10,10,10,10};

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
    bool isLove = false;
    int slowedTime = 0;
    int paralyzedTime = 0;
    int hastedTime = 0;
    bool canBeFought = true;
    void SetAbil(int STR, int DEX, int CON, int INT, int WIS, int CHA);
};

#endif
