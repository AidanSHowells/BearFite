#include "RollDice.h"
#include "Spell.h"
#include "HUD.h"
#include "Bear.h"
#include "Player.h"

void Spell::Cast(Player& player, BattleHUD& battleHUD){
  if(identifier == SpellID::none){
    return;
  }

  Bear& targetBear = *(battleHUD.GetBearPtr());

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
    targetBear.MakeSweetLove();
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
  if(spellcastingLevelAffectsNumDamageDice){
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
