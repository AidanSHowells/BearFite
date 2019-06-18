#include "HUD.h"
#include "Player.h"
#include "Bear.h"
#include "BearBattle.h"
#include "RollDice.h"

/*Why force the person creating a HUD object to provide fonts? Two reasons.
 *First, constructors can't return values, so we can't tell the constructor to
 *return an error code if the font fails to load. This makes it harder to fail
 *gracefully. Second, it's not as simple as loading fonts in the constructor
 *and assigning them to the text. From the "sf::Font" documentation: "It is
 *important to note that the sf::Text instance doesn't copy the font that it
 *uses, it only keeps a reference to it. Thus, a sf::Font must not be destructed
 *while it is used by a sf::Text (i.e. never write a function that uses a local
 *sf::Font instance for creating a text)."
 */

HUD::HUD(sf::Font& titleFont,
    sf::Font& mainFont,
    Player& thePlayer,
    const std::vector <sf::String>& optionString,
    int optionsListBreakPoint,
    bool optionsTitle
):
  messages(titleFont,mainFont,"Messages:"),
  options(titleFont,mainFont,optionString,optionsListBreakPoint,optionsTitle),
  playerStats(titleFont,mainFont,thePlayer),
  player(&thePlayer)
{
  player -> SetMessageBox(messages);
}

void HUD::Update(const sf::Vector2f mousePos, const bool optionsAvailable){
  options.Update(mousePos, optionsAvailable);
  playerStats.Update(mousePos, false, false);
}

void HUD::draw(sf::RenderTarget& target, sf::RenderStates states) const{
  target.draw(messages, states);
  target.draw(options, states);
  target.draw(playerStats, states);
}


BattleHUD::BattleHUD( sf::Font& titleFont,
                      sf::Font& mainFont,
                      Player& thePlayer,
                      const std::array<Bear,4>& bears
):
HUD(titleFont, mainFont, thePlayer, {"PUNCH:Where Punch Bear?","1:Leg","2:Eye",
  "3:John Hopkins","ELSE:What Do?","4:Quaff Drank","5:Cast Spell","6:Flee"}, 4),
bearStats{
  BearStats(titleFont,mainFont,bears.at(0),true),
  BearStats(titleFont,mainFont,bears.at(1),false,sf::Vector2f(205,50)),
  BearStats(titleFont,mainFont,bears.at(2),false,sf::Vector2f(205,75)),
  BearStats(titleFont,mainFont,bears.at(3),false,sf::Vector2f(205,100))},
friendBearStats(titleFont,mainFont,Bear(),true)
{
  for(int i = 0; i < 4; i++){
    bearStats[i].GetBearPtr() -> SetMessageBox(messages);
  }
  friendBearStats.GetBearPtr() -> SetMessageBox(messages);
  player -> SetLastBear(bears.at(0).GetName());
  bearHighlight.UpdateState(true);
}

std::vector<Bear*> BattleHUD::GetAllEnemyBears(){
  std::vector<Bear*> bearVec;
  for(int i = 0; i < GetNumEnemyBears(); i++){
    bearVec.push_back(bearStats[i].GetBearPtr());
  }
  return bearVec;
}

int BattleHUD::GetNumEnemyBears() const{
  int numBears = 4;
  for(int i = 3; i >= 0; i--){
    if(!bearStats[i].GetShouldAppear()){
      numBears = i;
    }
  }
  return numBears;
}

int BattleHUD::RemoveDeadCombatants(Winner& winner){
  int numDranks = 0;

  //FriendBear stuff here.

  for(int i = GetNumEnemyBears() - 1; i >= 0; i--){
    if(bearStats[i].GetBearPtr() -> IsDead() ||
       bearStats[i].GetBearPtr() -> IsLove())
    {
      Bear tempBear = *bearStats[i].GetBearPtr();
      if(tempBear.IsDead()){
        player -> IncrementBodyCount();
        player -> AddExp(tempBear.ExpReward());
        if(Roll(1,5) > 3){// 2/5 drank per bear, same as calc version default
          numDranks++;
        }
      }
      for(int j = i; j < 3; j++){
        bearStats[j].SetBear( *bearStats[j + 1].GetBearPtr() );
        bearStats[j].SetShouldAppear( bearStats[j + 1].GetShouldAppear() );
      }
      bearStats[3].SetBear(tempBear);
      bearStats[3].SetShouldAppear(false);

      if(bearStats[0].GetShouldAppear()){
        targetBearIndex = 0;//Now targeting the top bear
      }
      else{
        //If we just killed the last remaining bear, its stats will be in slot 3
        targetBearIndex = 3;
      }
    }
  }

  if(player -> IsDead()){
    winner = Winner::bear;
  }
  //The player has won if they're alive and the top bear is dead
  else if(!bearStats[0].GetShouldAppear()){
    winner = Winner::player;
  }
  else{
    winner = Winner::neither;
  }
  return numDranks;
}

TurnOf BattleHUD::TakeAction(sf::Event theEvent){
  playerStats.ToggleFeats(theEvent);
  if(isPickingSpell || theEvent.type == sf::Event::MouseButtonPressed){
    int spellIndex = 0;
    bool choseSpell;//Spell, as opposed to Feat
    choseSpell = playerStats.GetSpell(theEvent, spellIndex);
    if(spellIndex != PlayerStats::noChoice){
      isPickingSpell = false;
      if(spellIndex != PlayerStats::changedMindAboutCasting){
        if(choseSpell){
          return player -> Cast(spellIndex, *this);
        }
        else{
          return player -> ActivateFeat(spellIndex);
        }
      }
    }
  }
  if(!isPickingSpell){
    if(theEvent.type == sf::Event::KeyPressed){
      if(theEvent.key.code == sf::Keyboard::Up){
        //targetBearIndex = (targetBearIndex - 1) % GetNumEnemyBears();
        //The above doesn't work because the idiots who wrote the C++ standard
        //defined % wrong, so we need something like:
        if(0 == targetBearIndex){
          targetBearIndex = GetNumEnemyBears() - 1;
        }
        else{
          targetBearIndex = targetBearIndex - 1;
        }
      }
      else if(theEvent.key.code == sf::Keyboard::Down){
        targetBearIndex = (targetBearIndex + 1) % GetNumEnemyBears();
      }
    }
    playerStats.ToggleMenu(theEvent);

    Action theAction = Action(options.GetChoice(theEvent));
    if (theAction == Action::cast){
      if(playerStats.SpellChoiceProcessStarted(messages)){
        isPickingSpell = true;
      }
    }
    else{
      return player -> TakeAction(theAction, *GetBearPtr(), GetAllEnemyBears());
    }
  }//Endif not picking spell
  return TurnOf::player;
}

void BattleHUD::Update(const sf::Vector2f mousePos,const bool optionsAvailable){
  canPickFromOptions = optionsAvailable;
  options.Update(mousePos, !isPickingSpell && optionsAvailable);
  playerStats.Update(mousePos, isPickingSpell, optionsAvailable);

  if(GetNumEnemyBears() > 1){
    bearHighlight.AdjustToFit(bearStats[targetBearIndex].GetNameBox());
  }
  for(int i = 0; i < GetNumEnemyBears(); i++){
    bearStats[i].Update();
  }
}

void BattleHUD::draw(sf::RenderTarget& target, sf::RenderStates states) const{
  target.draw(messages, states);
  target.draw(options, states);
  target.draw(playerStats, states);

  for(int i = 0; i < GetNumEnemyBears(); i++){
    target.draw(bearStats[i], states);
  }
  if(GetNumEnemyBears() > 1){
    target.draw(bearHighlight, states);
  }
}
