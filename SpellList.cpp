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
  else if(spellID == SpellID::leech ||
          spellID == SpellID::reversal ||
          spellID == SpellID::abilDrain)
  {
    spellIDList.at(0) = SpellID::leech;
    spellIDList.at(1) = SpellID::reversal;
    spellIDList.at(2) = SpellID::abilDrain;
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
  else if(spellID == SpellID::leech){
    name = sf::String("Leech");
    school = SpellSchool::STR;
    successText = sf::String("*Slurp*");

    //Set saves
    allowsSave = true;
    saveType = SaveType::fort;
    saveText = sf::String("Bear tastes gross");
    saveBaseDC = -20;
    saveLevelFactor = 1;
    saveSchoolFactor = 1;
  }
  else if(spellID == SpellID::reversal){
    name = sf::String("Reversal");
    school = SpellSchool::STR;
    successText = sf::String("The tabled turn");

    //Set saves
    allowsSave = true;
    saveType = SaveType::fort;
    saveText = sf::String("Bear not trade");
    saveBaseDC = -20;
    saveLevelFactor = 1;
    saveSchoolFactor = 1;
  }
  else if(spellID == SpellID::abilDrain){
    name = sf::String("Ability Drain");
    school = SpellSchool::STR;
    successText = sf::String("You are drain bear");

    //Set saves
    allowsSave = true;
    saveType = SaveType::fort;
    saveText = sf::String("Not today");
    saveBaseDC = -30;
    saveLevelFactor = 1;
    saveSchoolFactor = 1;
  }
  else if(spellID == SpellID::inferno){
    name = sf::String("Inferno");
    school = SpellSchool::INT;
    successText = sf::String("Bear is cooked");

    //Set saves
    allowsSave = true;
    saveType = SaveType::reflex;
    saveText = sf::String("Bear flip away");
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


void Spell::ApplyEffects(Player& player, BattleHUD& battleHUD, bool saveMade){
  Bear& targetBear = *(battleHUD.GetBearPtr());
  int damage = 0;

  if(SpellID::none == identifier){}
  else if(SpellID::pain == identifier){
    if(!saveMade){
      damage = targetBear.GetHealth() / 2;
      damage += Roll(1 + player.GetSpellcastingLevel() / 2, 4);
    }
  }
  else if(SpellID::death == identifier){
    if(saveMade){
      damage = Roll(3,6);
    }
    else{
      damage = targetBear.GetHealth();
      damage += 2 * player.GetSpellSchoolBonus(school);
    }
  }
  else if(SpellID::pleasure == identifier){
    if(!saveMade){
      player.MakeSweetLove();
      targetBear.MakeSweetLove();
    }
  }
  else if(SpellID::leech == identifier){
    if(!saveMade){
      damage = Roll(1 + player.GetSpellcastingLevel() / 3, 6);
      player.Hurt(-damage);
    }
  }
  else if(SpellID::reversal == identifier){
    if(!saveMade){
      int diff = targetBear.GetHealth() - player.GetHealth();
      targetBear.Hurt(diff);
      player.Hurt(-diff);
    }
  }
  else if(SpellID::abilDrain == identifier){
    if(!saveMade){
      int numDrains = std::min(1 + player.GetSpellcastingLevel() / 4,
                               player.GetAbil(int(Abil::CHA)) - 10);

      for(int i = 0; i < numDrains; i++){
        int targetAbil = Roll(1,6) - 1;
        int drain = std::min(targetBear.GetAbil(targetAbil) - 1, Roll(1,4));
        targetBear.DrainAbil(targetAbil, drain);
        player.BuffAbil(targetAbil, drain);
      }
    }
  }
  else if(SpellID::inferno == identifier){
    damage = Roll(1 + player.GetSpellcastingLevel() / 3, 6);
    if(saveMade) damage = damage / 2;
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
