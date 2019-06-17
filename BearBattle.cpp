#include "Display/HUD.h"
#include "Player.h"
#include "Bear.h"
#include "RollDice.h"
#include "BearBattle.h"

void DrawStuff( sf::RenderWindow& window,
                BattleHUD& theHUD,
                const sf::Sprite& background,
                const bool canSelectOptions = true);
void WaitForEnter(sf::RenderWindow& window,
                  BattleHUD& theHUD,
                  const sf::Sprite& background,
                  Winner theWinner,
                  int NumDranks);


Winner BearBattle(sf::RenderWindow& window, BattleHUD& theHUD){
  Player& player = *(theHUD.GetPlayerPtr());
  Winner theWinner = Winner::neither;

  //Keep track of turns and dranks
  TurnOf turn = TurnOf::player;
  int numDranks = 0;

  //Make the picture
  sf::Texture finalBear;
  finalBear.loadFromFile("Resources/Background.png");
  sf::Sprite background;
  background.setTexture(finalBear);
  background.setPosition(205, 193);//(205, 55) to align it at the top


  while (window.isOpen()){

    if(TurnOf::bear == turn){
      sf::sleep(sf::milliseconds(250));//This # felt okay... feel free to change
      int numEnemyBears = theHUD.GetNumEnemyBears();
      for(int i = 0; i < numEnemyBears; i++){
        theHUD.bearStats[i].GetBearPtr() -> TakeTurn(*theHUD.GetPlayerPtr());
      }
      turn = TurnOf::player;
    }

    numDranks += theHUD.RemoveDeadCombatants(theWinner);
    if(theWinner != Winner::neither){
      WaitForEnter(window, theHUD, background, theWinner, numDranks);
      return theWinner;
    }

    sf::Event event;
    while (TurnOf::player == turn && window.pollEvent(event)){
      if (event.type == sf::Event::Closed){
        window.close();
      }
      if (event.type == sf::Event::KeyPressed ||
          event.type == sf::Event::MouseButtonPressed)
      {
        turn = theHUD.TakeAction(event);
        if(turn == TurnOf::bear){
          if(player.IsHasted() && Roll(1,2) == 2){
            turn = TurnOf::player;
          }
          else player.TimerTick();
        }
      }
    }

    numDranks += theHUD.RemoveDeadCombatants(theWinner);
    if(theWinner != Winner::neither){
      WaitForEnter(window, theHUD, background, theWinner, numDranks);
      return theWinner;
    }

    if(TurnOf::neither == turn){
      WaitForEnter(window, theHUD, background, theWinner, numDranks);
      return Winner::neither; //If it's ever no one's turn, it means the battle
                              //ended. (Presumably because the player fled)
    }

    DrawStuff(window, theHUD, background);
  }
  return Winner::neither; //This should only execute if the player closes the
                          //game in the middle of a battle
}

void DrawStuff( sf::RenderWindow& window,
                BattleHUD& theHUD,
                const sf::Sprite& background,
                const bool canSelectOptions)//Default is true
{
  theHUD.Update(sf::Vector2f(sf::Mouse::getPosition(window)), canSelectOptions);

  window.clear();
  window.draw(background);
  window.draw(theHUD);
  window.display();
}

void WaitForEnter(sf::RenderWindow& window,
                  BattleHUD& theHUD,
                  const sf::Sprite& background,
                  Winner theWinner,
                  int numDranks)
{
  if(numDranks > 1){
    theHUD.messages.Update(sf::String("You find Dranks"), true);
    theHUD.GetPlayerPtr() -> FindDranks(numDranks);
  }
  else if(numDranks == 1){
    theHUD.messages.Update(sf::String("You find Drank"), true);
    theHUD.GetPlayerPtr() -> FindDranks(numDranks);
  }
  theHUD.messages.Update(sf::String("Press Enter"), true);
  while (window.isOpen()){
    sf::Event event;
    while(window.pollEvent(event)){
      theHUD.playerStats.ToggleMenu(event);
      theHUD.playerStats.ToggleFeats(event);
      if (event.type == sf::Event::Closed){
        window.close();
      }
      else if(event.type == sf::Event::KeyPressed)
      {
        if(event.key.code == sf::Keyboard::Return){
          return;
        }
      }
    }
    DrawStuff(window, theHUD, background, false);
  }
}
