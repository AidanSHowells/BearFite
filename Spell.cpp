#include "Spell.h"
#include "HUD.h"
#include "Bear.h"
#include "Player.h"

TurnOf Spell::Cast(Player& player, BattleHUD& battleHUD){
  if(identifier == SpellID::none){
    return TurnOf::player;
  }

  bool saveMade;
  Bear* targetBear = battleHUD.GetBearPtr();
  std::vector<Bear*> bearVector = battleHUD.GetAllEnemyBears();
  int index = -1;

  do{
    if(affectsAllBears){
      index++;
      targetBear = bearVector.at(index);
    }
    bool displayLine = (!affectsAllBears) || (0 == index);

    saveMade = false;
    if(allowsSave){
      if(targetBear -> GetSave(saveType) >= GetSaveDC(player)){

        battleHUD.messages.Update(saveText, displayLine);
        saveMade = true;
      }
    }

    ApplyEffects(player, *targetBear, saveMade);

    if(!saveMade){
      battleHUD.messages.Update(successText, displayLine);
    }
  } while(affectsAllBears && index < battleHUD.GetNumBears() - 1);

  if(alwaysText != sf::String("")){
    battleHUD.messages.Update(alwaysText);
  }
  if(spellEndsBattle){
    return TurnOf::neither;
  }
  return TurnOf::bear;
}


int Spell::GetSaveDC(Player player){
  int DC = saveBaseDC;
  DC += saveLevelFactor * player.GetSpellcastingLevel();
  DC += saveSchoolFactor * player.GetSpellSchoolBonus(school);

  return DC;
}
