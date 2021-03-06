#ifndef BEAR_H
#define BEAR_H

#include <array>//For std::array
#include <vector>//For std::vector
#include "Modifier.h"
#include "Abilities.h"
#include "Body.h"

class Player;
class MessageBox;

//List of all bears that can appear (plus NUM_BEARS, which MUST be last):
enum class BearID{Babby, Black, Brown, Polar, NUM_BEARS};

enum class SaveType;
enum class Action;  //Actions the player can take. Defined in player.h

class Bear{
  public:
    Bear(){canBeFought = false;}
    Bear(const BearID bearID);

    std::array<Bear, 4> ApplyModifier(const ModifierID modID);
    void SetMessageBox(MessageBox& theMessages);

    int GetAC(const Action attackType) const;
    sf::String GetName() const;
    BearID GetID(){return identifier;}
    sf::String GetModifier();
    int GetDifficulty() const {return difficulty;}
    int GetHealth();
    int GetSave(const SaveType saveType);
    int GetAbil(const int index, const bool isCheckingDeath = false) const;

    void TakeTurn(Player& target);
    void Hurt(int); //how the player lowers the bear's health
    int DrainAbil(const int ability, int drain, const bool canKill = false);
    void MakeSweetLove(){isLove = true;}

    bool IsLove(){return isLove;}
    bool IsDead();
    bool IsAngry();
    bool CanBeFought(){return canBeFought;}

    void Slow(int time){slowedTime = std::max(time, slowedTime);}
    void Paralyze(int time){paralyzedTime = std::max(time, paralyzedTime);}
    void Haste(int time){hastedTime = std::max(time, hastedTime);}
    void Cry(int time){cryingTime = std::max(time, cryingTime);}
    void FeedFish(int fishSize);

    int ExpReward();
  protected:
    MessageBox* messageBox = nullptr;
    void printMessage(const sf::String& message1,
                      const sf::String& message2 = sf::String("")) const;
    void printMessage(const sf::String& message1, const int message2) const;
    sf::String name = sf::String("Klepto");
    BearID identifier;
    ModifierID modifier = ModifierID::none;
    bool modifierNameVisible = true;
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
    int GetAttackBonus() const;
    int GetDamageBonus() const;
    bool isLove = false;
    bool isAngry = false;

    int slowedTime = 0;
    int paralyzedTime = 0;
    int hastedTime = 0;
    int cryingTime = 0;
    int eatingTime = 0;

    bool IsSlowed() const {return (slowedTime > 0);}
    bool IsParalyzed() const {return (paralyzedTime > 0);}
    bool IsHasted() const {return (hastedTime > 0);}
    bool IsCrying() const {return (cryingTime > 0);}
    bool IsEating() const {return (eatingTime > 0);}
    void Bash(Player& thePlayer);
    void TimerTick();

    int difficulty = 0;
    bool canBeFought = true;
    void SetAbil(int STR, int DEX, int CON, int INT, int WIS, int CHA);
};

#endif
