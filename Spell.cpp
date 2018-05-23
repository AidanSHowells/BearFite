#include <iostream> //For std::cerr
#include "RollDice.h"
#include "Spell.h"
#include "HUD.h"
#include "Bear.h"
#include "Player.h"

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

    //Set damage
    baseDamage = 0;
    bearHealthPercentDamage = 50;
    baseNumDamageDice = 1;
    levelAffectsNumDamageDice = true;
    spellLevelsPerExtraDamageDie = 2;
    damageDiceSize = 4;
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

    //Set damage
    baseDamage = 0;
    bearHealthPercentDamage = 100;
    spellSchoolBonusDamageFactor = 2;
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

    //Set extra effects
    makeLove = true;
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

void Spell::Cast(Player& player, BattleHUD& battleHUD){
  Bear targetBear = *(battleHUD.GetBearPtr());

  if(requiresTouchAttack){
    if(!player.TouchAttack(targetBear)){
      battleHUD.messages.Update(dodgeText);
      Spell(castIfPlayerMisses).Cast(player, battleHUD);
      return;
    }
  }

  if(allowsSave){
    if(targetBear.GetSave(saveType) >= GetSaveDC(player)){
      battleHUD.messages.Update(saveText);
      Spell(castIfBearSaves).Cast(player, battleHUD);
      return;
    }
  }

  targetBear.Hurt(GetDamage(player, targetBear));
  for(int i = 0; i < int(Abil::NUM_ABIL); i++){
    if(drainAbil[i]){
      targetBear.DrainAbil(i, Roll(1,4));
    }
  }
  if(makeLove){
    player.MakeSweetLove();
  }

  Spell(castOnSuccess).Cast(player, battleHUD);

  battleHUD.messages.Update(successText);
}


int Spell::GetSaveDC(Player player){
  int DC = saveBaseDC;
  DC += saveLevelFactor * player.GetSpellcastingLevel();
  DC += saveSchoolFactor * player.GetSpellSchoolBonus(school);

  return DC;
}

int Spell::GetDamage(Player player, Bear bear){
  int numDamageDice = baseNumDamageDice;
  if(levelAffectsNumDamageDice){
    int spellLevel = player.GetSpellcastingLevel();
    numDamageDice += spellLevel / spellLevelsPerExtraDamageDie;
  }

  int damage = baseDamage;
  damage += (bearHealthPercentDamage * bear.GetHealth()) / 100;
  damage += spellSchoolBonusDamageFactor * player.GetSpellSchoolBonus(school);
  damage += Roll(numDamageDice, damageDiceSize);

  //if(identifier = SpellID::thatOneWeirdSpell){damage += ...}

  return damage;
}
