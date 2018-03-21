#include "HUD.h"
#include "Player.h"
#include "Bear.h"

bool BearBattle(sf::RenderWindow& window,
                sf::Font& titleFont,
                sf::Font& mainFont,
                Player& player,
                Bear& bear)
{
  //Keep track of turns
  TurnOf turn = TurnOf::player;


  //Make the HUD
  Display HUD(window,titleFont,mainFont,player,bear);


  while (window.isOpen()){

    if(TurnOf::bear == turn){
      sf::sleep(sf::milliseconds(250));//This # felt okay... feel free to change
      bear.Bash(player);
      turn = TurnOf::player;
    }

    sf::Event event;
    while (TurnOf::player == turn && window.pollEvent(event)){
      if (event.type == sf::Event::Closed){
        window.close();
      }
      if (event.type == sf::Event::KeyPressed ||
          event.type == sf::Event::MouseButtonPressed)
      {
        turn = player.TakeAction(HUD.GetAction(event), bear);
      }
    }

    //Draw the stuff to the screen
    window.clear();
    HUD.draw();
    window.display();

    if(bear.GetHealth()<=0){return true;}
    if(player.GetHealth()<=0){return false;}
  }
  return true;//This shouldn't matter; we should only get here if !window.isOpen
}
