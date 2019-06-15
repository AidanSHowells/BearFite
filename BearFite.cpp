#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Display/HUD.h"
#include "BearBattle.h"
#include "Player.h"


int main(){
  srand(unsigned(time(NULL)));

  sf::Font courierNew;
  if (!courierNew.loadFromFile("Resources/cour.ttf")){
    return EXIT_FAILURE;
  }
  sf::Font courierNewBd;
  if (!courierNewBd.loadFromFile("Resources/courbd.ttf")){
    return EXIT_FAILURE;
  }

  sf::RenderWindow window(sf::VideoMode(800, 600),
                          "BearFite",
                          sf::Style::Titlebar | sf::Style::Close);
  window.setKeyRepeatEnabled(false);

  Player player;
  std::vector <sf::String> options = {"What To Do?",
                                      "1:Find Some Bear",
                                      "2:Quaff Drank",
                                      "3:Retire",
                                      "4:Save and Quit"};
  HUD theHUD(courierNewBd, courierNew, player, options, 3, false);
  bool exiting = false;

  while (window.isOpen()){

    sf::Event event;
    while (window.pollEvent(event)){
      theHUD.playerStats.ToggleMenu(event);
      theHUD.playerStats.ToggleFeats(event);
      if (event.type == sf::Event::Closed){
        window.close();
      }
      else if(!exiting){
        const int choice = theHUD.options.GetChoice(event);
        if(choice == 1){
          std::array<Bear,4> bears;
          bears.at(0) = Bear(BearID::Polar);//TEMP
          BattleHUD battleHUD(courierNewBd,courierNew,player,bears);

          const Winner winner = BearBattle(window, battleHUD);

          player.SetMessageBox(theHUD.messages);
          player.PostBattleReset();
          if(winner == Winner::bear){
            window.close();
          }
        }
        else if(choice == 2){
          player.Heal();
        }
        else if(choice == 3){
          theHUD.messages.Update("Sorry! Retiring is","not supported yet",true);
        }
        else if(choice == 4){
          exiting = true;
          theHUD.messages.Update("Press Esc to cancel", true);
          theHUD.messages.Update("Press Enter to quit", "without saving",false);
          theHUD.messages.Update("Sorry! Saving is not", "supported yet",false);
        }
      }
      else if(exiting){
        if(event.type == sf::Event::KeyPressed){
          if(event.key.code == sf::Keyboard::Return){
            window.close();
          }
          else if(event.key.code == sf::Keyboard::Escape)
            exiting = false;
        }
      }
    }//End while(window.pollEvent(event))

    window.clear();
    theHUD.Update(sf::Vector2f(sf::Mouse::getPosition(window)), true);
    window.draw(theHUD);
    window.display();
  }//end while(window.isOpen())

  return 0;
}
