#include <iostream> //For std::cerr
#include <string>
#include <algorithm> //For std::min
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
  else if(spellID == SpellID::inferno ||
          spellID == SpellID::blizzard ||
          spellID == SpellID::storm)
  {
    spellIDList.at(0) = SpellID::inferno;
    spellIDList.at(1) = SpellID::blizzard;
    spellIDList.at(2) = SpellID::storm;
  }
  else if(spellID == SpellID::rage ||
          spellID == SpellID::warCry ||
          spellID == SpellID::bigFist)
  {
    spellIDList.at(0) = SpellID::rage;
    spellIDList.at(1) = SpellID::warCry;
    spellIDList.at(2) = SpellID::bigFist;
  }
  else if(spellID == SpellID::santuary ||
          spellID == SpellID::fish ||
          spellID == SpellID::refuge)
  {
    spellIDList.at(0) = SpellID::santuary;
    spellIDList.at(1) = SpellID::fish;
    spellIDList.at(2) = SpellID::refuge;
  }
  else if(spellID == SpellID::slow ||
          spellID == SpellID::haste ||
          spellID == SpellID::timeStop)
  {
    spellIDList.at(0) = SpellID::slow;
    spellIDList.at(1) = SpellID::haste;
    spellIDList.at(2) = SpellID::timeStop;
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
    affectsAllEnemyBears = true;

    //Set saves
    allowsSave = true;
    saveType = SaveType::reflex;
    saveText = sf::String("Bear flip away");
    saveBaseDC = -30;
    saveLevelFactor = 1;
    saveSchoolFactor = 1;
  }
  else if(spellID == SpellID::blizzard){
    name = sf::String("Blizzard");
    school = SpellSchool::INT;
    successText = sf::String("Bear is freeze");
    affectsAllEnemyBears = true;

    //Set saves
    allowsSave = true;
    saveType = SaveType::reflex;
    saveText = sf::String("Bear is only chilly");
    saveBaseDC = -30;
    saveLevelFactor = 1;
    saveSchoolFactor = 1;
  }
  else if(spellID == SpellID::storm){
    name = sf::String("Storm");
    school = SpellSchool::INT;
    successText = sf::String("*BZZZZZZZZZZ*");
    affectsAllEnemyBears = true;

    //Set saves
    allowsSave = true;
    saveType = SaveType::reflex;
    saveText = sf::String("Bear weathers storm");
    saveBaseDC = -30;
    saveLevelFactor = 1;
    saveSchoolFactor = 1;
  }
  else if(spellID == SpellID::rage){
    name = sf::String("Rage");
    school = SpellSchool::INT;
    successText = sf::String("yoU fEeL ARGER!");
    spellIsOffensive = false;
  }
  else if(spellID == SpellID::warCry){
    name = sf::String("War Cry");
    school = SpellSchool::INT;
    alwaysText = sf::String("You are LOUD");
    successText = sf::String("Bear is crying");
    affectsAllEnemyBears = true;

    //Set saves
    allowsSave = true;
    saveType = SaveType::will;
    saveText = sf::String("Bear laughs");
    saveBaseDC = -30;
    saveLevelFactor = 1;
    saveSchoolFactor = 1;
  }
  else if(spellID == SpellID::bigFist){
    name = sf::String("Big Fist");
    school = SpellSchool::INT;
    successText = sf::String("Fist is Big");
    spellIsOffensive = false;
  }
  else if(spellID == SpellID::santuary){
    name = sf::String("Santuary");
    school = SpellSchool::WIS;
    successText = sf::String("You are safe");
    spellIsOffensive = false;
  }
  else if(spellID == SpellID::fish){
    name = sf::String("Fish");
    school = SpellSchool::WIS;
    successText = sf::String("Bear Lik Dis Fish");

    //Set saves
    allowsSave = true;
    saveType = SaveType::will;
    saveText = sf::String("Fish is Bad");
    saveBaseDC = -30;
    saveLevelFactor = 1;
    saveSchoolFactor = 1;
  }
  else if(spellID == SpellID::refuge){
    name = sf::String("Refuge");
    school = SpellSchool::WIS;
    successText = sf::String("Goodbye");

    spellEndsBattle = true;
    spellIsOffensive = false;
  }
  else if(spellID == SpellID::slow){
    name = sf::String("Slow");
    school = SpellSchool::DEX;
    successText = sf::String("Bear flows like honey");

    //Set Saves
    allowsSave = true;
    saveType = SaveType::will;
    saveText = sf::String("Bear flows like milk");
    saveBaseDC = -20;
    saveLevelFactor = 1;
    saveSchoolFactor = 1;
  }
  else if(spellID == SpellID::haste){
    name = sf::String("Haste");
    school = SpellSchool::DEX;
    successText = sf::String("\"Zoom\"");
    spellIsOffensive = false;
  }
  else if(spellID == SpellID::timeStop){
    name = sf::String("Time Stop");
    school = SpellSchool::DEX;
    successText = sf::String("Time is become stop");
    spellIsOffensive = false;
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


void Spell::ApplyEffects(Player& player, Bear& targetBear, bool saveMade){
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
        int drain = targetBear.DrainAbil(targetAbil, Roll(1,4));
        player.BuffAbil(targetAbil, drain);
      }
    }
  }
  else if(SpellID::inferno == identifier){
    damage = Roll(1 + player.GetSpellcastingLevel() / 3, 6);
    if(saveMade) damage = damage / 2;
  }
  else if(SpellID::blizzard == identifier){
    damage = Roll(1 + player.GetSpellcastingLevel() / 3, 8);
    if(saveMade){
      damage = damage / 2;
    }
    else{
      targetBear.Slow(10);
    }
  }
  else if(SpellID::storm == identifier){
    damage = Roll(1 + player.GetSpellcastingLevel() / 3, 10);
    if(saveMade){
      damage = damage / 2;
    }
    else{
      targetBear.Paralyze(10);
    }
  }
  else if(SpellID::rage == identifier){
    player.Rage(20);
  }
  else if(SpellID::warCry == identifier){
    player.WarCry(20);
    if(!saveMade){targetBear.Cry(20);}
  }
  else if(SpellID::bigFist == identifier){
    player.BigFist(20);
  }
  else if(SpellID::santuary == identifier){
    player.EnterSantuary(4);
  }
  else if(SpellID::fish == identifier){
    if(!saveMade){
      int numFish = 1 + player.GetSpellcastingLevel() / 10;
      int fishSize = Roll(numFish, 6) + player.GetSpellSchoolBonus(school) / 10;
      targetBear.FeedFish(fishSize);
    }
  }
  else if(SpellID::refuge == identifier){
    player.Hurt(-50);
  }
  else if(SpellID::slow == identifier){
    //Compare with blizzard before changing
    int numDice = 1 + player.GetSpellcastingLevel() / 3;
    int bonusTurns = 6 + player.GetSpellSchoolBonus(school) / 10;
    targetBear.Slow(bonusTurns + Roll(numDice,4));
  }
  else if(SpellID::haste == identifier){
    int numDice = 1 + player.GetSpellcastingLevel() / 3;
    int bonusTurns = 6 + player.GetSpellSchoolBonus(school) / 10;
    player.Haste(bonusTurns + Roll(numDice,4));
  }
  else if(SpellID::timeStop == identifier){
    player.StopTime(4);
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

void SpellTree::IncrementCount(int index){
  numSpells.at(index) = std::min(maxSpells.at(index), numSpells.at(index) + 1);
}
