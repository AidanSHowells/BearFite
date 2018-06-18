#include <iostream> //For std::cerr
#include <string>
#include "RollDice.h"
#include "Spell.h"
#include "Player.h"


SpellTree::SpellTree(const SpellID spellID){
  if(spellID == SpellID::none){
    for(int i = 0; i < 3; i++){
      spellIDList.at(i) = SpellID::none;
      numSpells.at(i) = 0;
      maxSpells.at(i) = 0;
    }
  }
  else if(spellID == SpellID::pain ||
          spellID == SpellID::death ||
          spellID == SpellID::pleasure)
  {
    spellIDList.at(0) = SpellID::pain;
    spellIDList.at(1) = SpellID::death;
    spellIDList.at(2) = SpellID::pleasure;
  }
  else if(spellID == SpellID::NUM_SPELLS){
    std::cerr << "Warning! Attempted use of ";
    std::cerr << "SpellID::NUM_SPELLS in SpellTree constructor.\n\n";
  }
  else{
    std::cerr << "Warning! ";
    std::cerr << "Attempted use of SpellID unknown to SpellTree constructor.\n";
    std::cerr << "The number corresponding to the invalid SpellID was ";
    std::cerr << int(spellID) << ".\n\n";
  }
}


Spell::Spell(const SpellID spellID){//Defaults to SpellID::none
  identifier = spellID;
  if(spellID == SpellID::none){}
  else if(spellID == SpellID::pain){
    name = sf::String("Pain");
    school = SpellSchool::CHA;
    successText = sf::String("Ouch");

    //Set saves
    allowsSave = true;
    saveType = SaveType::will;
    saveText = sf::String("Bear is unperturbed");
    saveBaseDC = -20;
    saveLevelFactor = 1;
    saveSchoolFactor = 1;
  }
  else if(spellID == SpellID::death){
    name = sf::String("Death");
    school = SpellSchool::CHA;
    successText = sf::String("No more bear");

    //Set saves
    allowsSave = true;
    saveType = SaveType::will;
    saveText = sf::String("Bad failure");
    saveBaseDC = -30;
    saveLevelFactor = 1;
    saveSchoolFactor = 1;
  }
  else if(spellID == SpellID::pleasure){
    name = sf::String("Pleasure");
    school = SpellSchool::CHA;
    successText = sf::String("Hard bear");

    //Set saves
    allowsSave = true;
    saveType = SaveType::will;
    saveText = sf::String("Soft bear");
    saveBaseDC = -30;
    saveLevelFactor = 1;
    saveSchoolFactor = 1;
  }
  else if(spellID == SpellID::NUM_SPELLS){
    std::cerr << "Warning! Attempted use of ";
    std::cerr << "SpellID::NUM_SPELLS in Spell constructor.\n\n";
  }
  else{
    std::cerr << "Warning! ";
    std::cerr << "Attempted use of SpellID unknown to Spell constructor.\n";
    std::cerr << "The number corresponding to the invalid SpellID was ";
    std::cerr << int(spellID) << ".\n\n";
  }
}


void Spell::ApplyEffects(Player& player, BattleHUD& battleHUD){
  Bear& targetBear = *(battleHUD.GetBearPtr());
  int damage = 0;

  if(SpellID::none == identifier){}
  else if(SpellID::pain == identifier){
    damage = targetBear.GetHealth() / 2;
    damage += Roll(1 + player.GetSpellcastingLevel() / 2, 4);
  }
  else if(SpellID::death == identifier){
    damage = targetBear.GetHealth();
    damage += 2 * player.GetSpellSchoolBonus(school);
  }
  else if(SpellID::pleasure == identifier){
    player.MakeSweetLove();
    targetBear.MakeSweetLove();
  }
  else if(SpellID::NUM_SPELLS == identifier){
    std::cerr << "Warning! Attempted use of ";
    std::cerr << "SpellID::NUM_SPELLS in Spell::ApplyEffects.\n\n";
  }
  else{
    std::cerr << "Warning! ";
    std::cerr << "Attempted use of SpellID unknown to Spell::ApplyEffects.\n";
    std::cerr << "The number corresponding to the invalid SpellID was ";
    std::cerr << int(identifier) << ".\n\n";
  }

  targetBear.Hurt(damage);
}
