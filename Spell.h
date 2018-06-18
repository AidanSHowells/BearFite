#ifndef SPELL_H
#define SPELL_H

#include <array>//For std::array
#include <SFML/System/String.hpp>
#include "Abilities.h"

enum class SpellID{none, pain, death, pleasure, inferno, NUM_SPELLS};

enum class SaveType{reflex, fort, will, COUNT};

enum class SpellSchool{STR,DEX,CON,INT,WIS,CHA,WIS_CHA};//FIXME: Better names

class BattleHUD;
class Bear;
class Player;

class Spell{
  public:
    Spell(const SpellID spellID = SpellID::none);
    void Cast(Player& player, BattleHUD& battleHUD);
    sf::String GetName(){return name;}
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

    //Function for actually doing the stuff if casting is successful
    void ApplyEffects(Player& player, BattleHUD& battleHUD, bool saveMade);
};

#endif
