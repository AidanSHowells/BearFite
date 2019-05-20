#ifndef SPELL_H
#define SPELL_H

#include <array>//For std::array
#include <SFML/System/String.hpp>
#include "Abilities.h"

enum class TurnOf;

enum class SpellID{none, pain, death, pleasure, leech, reversal, abilDrain,
                   inferno, blizzard, storm, rage, warCry, bigFist,
                   santuary, fish, refuge, slow, haste, timeStop,
                   NUM_SPELLS};

enum class SaveType{reflex, fort, will, COUNT};

enum class SpellSchool{STR,DEX,CON,INT,WIS,CHA,WIS_CHA};//FIXME: Better names

class BattleHUD;
class Bear;
class Player;

class Spell{
  public:
    Spell(const SpellID spellID = SpellID::none);
    TurnOf Cast(Player& player, BattleHUD& battleHUD);
    sf::String GetName(){return name;}
    bool IsOffensive(){return spellIsOffensive;}
  private:
    SpellID identifier;
    sf::String name;
    SpellSchool school;
    bool affectsAllBears = false;
    bool spellEndsBattle = false;
    bool spellIsOffensive = true;//if true, cannot be used during santuary

    //Messages to print
    sf::String alwaysText = sf::String("");
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

    //Function for actually doing the stuff if casting is successful
    void ApplyEffects(Player& player, Bear& targetBear, bool saveMade);
};

#endif
