#include "HUD.h"
#include "Player.h"
#include "Bear.h"
#include "RollDice.h"

void DrawStuff(BattleHUD& theHUD, sf::Sprite background);
void WaitForEnter(BattleHUD& theHUD, sf::Sprite background);

bool BearBattle(BattleHUD& theHUD, Bear& fakeBear){
  Player& player = *(theHUD.GetPlayerPtr());

  //Keep track of turns
  TurnOf turn = TurnOf::player;

  //Make the picture
  sf::Texture finalBear;
  finalBear.loadFromFile("Resources/Background.png");
  sf::Sprite background;
  background.setTexture(finalBear);
  background.setPosition(205, 193);//(205, 55) to align it at the top


  while (theHUD.GetWindowPtr() -> isOpen()){

    if(TurnOf::bear == turn){
      sf::sleep(sf::milliseconds(250));//This # felt okay... feel free to change
      int i = 0;
      while(i < theHUD.GetNumBears()){
        Bear& currentBear = *theHUD.bearStats[i].GetBearPtr();
        if(!(currentBear.IsParalyzed() ||
            (currentBear.IsSlowed() && Roll(1,2) == 1))){
          currentBear.Bash(*theHUD.GetPlayerPtr());
        }
        if(!currentBear.IsHasted() || Roll(1,2) == 1){
          currentBear.TimerTick();
          i++;
        }
      }
      turn = TurnOf::player;
    }
    if(theHUD.RemoveDeadCombatants()){
      WaitForEnter(theHUD, background);
      return false;
    }

    sf::Event event;
    while (TurnOf::player == turn && theHUD.GetWindowPtr() -> pollEvent(event)){
      if (event.type == sf::Event::Closed){
        theHUD.GetWindowPtr() -> close();
      }
      if (event.type == sf::Event::KeyPressed ||
          event.type == sf::Event::MouseButtonPressed)
      {
        turn = theHUD.TakeAction(event);
        if(turn == TurnOf::bear){
          if(player.IsHasted() && Roll(1,2) == 2) turn = TurnOf::bear;
          else player.TimerTick();
        }
      }
    }
    fakeBear = *(theHUD.GetBearPtr() );//TEMP
    if(theHUD.RemoveDeadCombatants()){
      WaitForEnter(theHUD, background);
      return true;
    }

    DrawStuff(theHUD, background);
  }
  return false;//This shouldn't matter; we should only get here if !window.isOpen
  //FIXME: Instead of returning, there should be a error message printed
}

void DrawStuff(BattleHUD& theHUD, sf::Sprite background){
  theHUD.GetWindowPtr() -> clear();
  theHUD.draw();
  theHUD.GetWindowPtr() -> draw(background);
  theHUD.GetWindowPtr() -> display();
}

void WaitForEnter(BattleHUD& theHUD, sf::Sprite background){
  theHUD.messages.Update(sf::String("Press Enter"), true);
  while (theHUD.GetWindowPtr() -> isOpen()){
    sf::Event event;
    while(theHUD.GetWindowPtr() -> pollEvent(event)){
      if (event.type == sf::Event::Closed){
        theHUD.GetWindowPtr() -> close();
      }
      else if(event.type == sf::Event::KeyPressed)
      {
        if(event.key.code == sf::Keyboard::Return){
          return;
        }
      }
    }
    DrawStuff(theHUD, background);
  }
}
