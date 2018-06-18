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
      battleHUD.messages.Update(dodgeText, true);
      Spell(castIfPlayerMisses).Cast(player, battleHUD);
      return;
    }
  }

  if(allowsSave){
    if(targetBear.GetSave(saveType) >= GetSaveDC(player)){
      battleHUD.messages.Update(saveText, true);
      Spell(castIfBearSaves).Cast(player, battleHUD);
      return;
    }
  }

  ApplyEffects(player, battleHUD);

  Spell(castOnSuccess).Cast(player, battleHUD);

  battleHUD.messages.Update(successText, true);
}


int Spell::GetSaveDC(Player player){
  int DC = saveBaseDC;
  DC += saveLevelFactor * player.GetSpellcastingLevel();
  DC += saveSchoolFactor * player.GetSpellSchoolBonus(school);

  return DC;
}
