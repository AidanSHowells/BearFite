#ifndef BEAR_H
#define BEAR_H

#include <array>//For std::array
#include "Messages.h"
#include "Modifier.h"
#include "Abilities.h"

class Player;

//List of all bears that can appear (plus NUM_BEARS, which MUST be last):
enum class BearID{Babby, Black, Brown, Polar, NUM_BEARS};

enum class SaveType;

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
    void DrainAbil(int ability, int drain);
    bool IsDead(){return(health <= 0);}//Add extra death conditions to this func
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
    bool canBeFought = true;
    void SetAbil(int STR, int DEX, int CON, int INT, int WIS, int CHA);
};

#endif
