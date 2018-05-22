#ifndef SPELL_H
#define SPELL_H

#include <array>//For std::array
#include <SFML/System/String.hpp>
#include "Abilities.h"

enum class SpellID{none, pain, death, NUM_SPELLS};

enum class SaveType{reflex, fort, will, COUNT};

enum class SpellSchool{STR,DEX,CON,INT,WIS,CHA,WIS_CHA};//FIXME: Better names

class BattleHUD;
class Bear;
class Player;

class Spell{
  public:
    Spell(const SpellID spellID = SpellID::none);
    void Cast(Player& player, BattleHUD& battleHUD);
  private:
    SpellID identifier;
    sf::String name;
    SpellSchool school;

    //Messages to print
    sf::String dodgeText = sf::String("Bear is dodger.");
    sf::String saveText = sf::String("Bear resists.");
    sf::String successText = sf::String("It is done.");
    sf::String spellEnds = sf::String("Spell Over.");

    //Saves
    int GetSaveDC(Player player);
    bool requiresTouchAttack = false;
    bool allowsSave = false;
    SaveType saveType;
    int saveBaseDC = 0;
    int saveLevelFactor = 0;
    int saveSchoolFactor = 0;

    //Helper spells
    SpellID castOnSuccess = SpellID::none;
    SpellID castIfBearSaves = SpellID::none;
    SpellID castIfPlayerMisses = SpellID::none;

    //General stuff that applies to the bear
    bool drainAbil[int(Abil::NUM_ABIL)] = {false,false,false,false,false,false};
    //bool makeLove = false;
    //bool givesFish = false;

    //Damage done to the bear
    int GetDamage(Player player, Bear bear);
    int baseDamage = 0;
    int bearHealthPercentDamage = 0;
    int spellSchoolBonusDamageFactor = 0;
    int baseNumDamageDice = 0;
    bool levelAffectsNumDamageDice = false;
    int spellLevelsPerExtraDamageDie;
    int damageDiceSize = 0;

    //Stuff that applies to the player
    bool abilBoost[int(Abil::NUM_ABIL)] = {false,false,false,false,false,false};

    //Stuff that applies to the environment
    //TimeStop stuff goes here
};

#endif
