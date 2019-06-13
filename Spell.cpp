#include "Spell.h"
#include "Display/HUD.h"
#include "Bear.h"
#include "Player.h"
#include "BearBattle.h"

TurnOf Spell::Cast(Player& player, BattleHUD& battleHUD){
  if(identifier == SpellID::none){
    return TurnOf::player;
  }

  bool saveMade;
  Bear* targetBear = battleHUD.GetBearPtr();
  std::vector<Bear*> bearVector = battleHUD.GetAllEnemyBears();
  int index = -1;

  do{
    if(affectsAllEnemyBears){
      index++;
      targetBear = bearVector.at(index);
    }
    bool displayLine = (!affectsAllEnemyBears) || (0 == index);

    saveMade = false;
    if(allowsSave){
      if(player.HasStoppedTime() && SaveType::reflex == saveType){
        saveMade = false;
      }
      else if(targetBear -> GetSave(saveType) >= GetSaveDC(player)){
        battleHUD.messages.Update(saveText, displayLine);
        saveMade = true;
      }
    }

    ApplyEffects(player, *targetBear, saveMade);

    if(!saveMade){
      battleHUD.messages.Update(successText, displayLine);
    }
  } while(affectsAllEnemyBears && index < battleHUD.GetNumEnemyBears() - 1);

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
