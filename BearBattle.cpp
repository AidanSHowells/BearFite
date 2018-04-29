#include "HUD.h"
#include "Player.h"
#include "Bear.h"


bool BearBattle(BattleHUD& theHUD, Bear& fakeBear){
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
      for(int i = 0; i < theHUD.GetNumBears(); i++){
        theHUD.bearStats[i].GetBearPtr() -> Bash(*theHUD.GetPlayerPtr());
      }
      turn = TurnOf::player;
    }
    if(theHUD.RemoveDeadCombatants()){return false;}

    sf::Event event;
    while (TurnOf::player == turn && theHUD.GetWindowPtr() -> pollEvent(event)){
      if (event.type == sf::Event::Closed){
        theHUD.GetWindowPtr() -> close();
      }
      if (event.type == sf::Event::KeyPressed ||
          event.type == sf::Event::MouseButtonPressed)
      {
        turn = theHUD.TakeAction(event);
      }
    }
    fakeBear = *(theHUD.GetBearPtr() );//TEMP
    if(theHUD.RemoveDeadCombatants()){return true;}

    //Draw the stuff to the screen
    theHUD.GetWindowPtr() -> clear();
    theHUD.draw();
    theHUD.GetWindowPtr() -> draw(background);
    theHUD.GetWindowPtr() -> display();
  }
  return true;//This shouldn't matter; we should only get here if !window.isOpen
  //FIXME: Instead of returning, there should be a error message printed
}
