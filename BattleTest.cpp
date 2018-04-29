#include <cstdlib>
#include <ctime>

#include "HUD.h"
#include "BearList.h"
#include "BearBattle.h"
#include "Player.h"

int main(){
  srand(unsigned(time(NULL)));


  //Load the fonts
  sf::Font courierNew;
  if (!courierNew.loadFromFile("Resources/cour.ttf")){
    return EXIT_FAILURE;
  }
  sf::Font courierNewBd;
  if (!courierNewBd.loadFromFile("Resources/courbd.ttf")){
    return EXIT_FAILURE;
  }

  //Create the window
  sf::RenderWindow window(sf::VideoMode(800, 600), "BearFite", sf::Style::Titlebar | sf::Style::Close);
  window.setKeyRepeatEnabled(false);

  //Keep track of wins
  int winsvBabby = 0;
  int lossesToBabby = 0;
  int winsvBlack = 0;
  int lossesToBlack = 0;
  int winsvBrown = 0;
  int lossesToBrown = 0;
  int winsvPolar = 0;
  int lossesToPolar = 0;
  int winsvParty = 0;
  int lossesToParty = 0;

  MessageBox messages(window,courierNewBd,courierNew,"Messages:");
  messages.Update("Q - R: Regular Bears",
                  "A: Babby Party",
                  "Z: Random Bear");

  Player player;
  PlayerStats status(window,courierNewBd,courierNew,player);

  while (window.isOpen()){

    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){
        window.close();
      }
      if (event.type == sf::Event::KeyPressed){
        if(event.key.code == sf::Keyboard::Q ||
           event.key.code == sf::Keyboard::W ||
           event.key.code == sf::Keyboard::E ||
           event.key.code == sf::Keyboard::R ||
           event.key.code == sf::Keyboard::A ||
           event.key.code == sf::Keyboard::Z)
        {
          sf::Keyboard::Key key = event.key.code;
          int bearHealth = 420;
          Bear fakeBear;
          HUD battleHUD(window,courierNewBd,courierNew,player,fakeBear);
          FindBear(key, battleHUD);


          if(BearBattle(battleHUD, fakeBear)){
            if(key == sf::Keyboard::Q){winsvBabby++;}
            if(key == sf::Keyboard::W){winsvBlack++;}
            if(key == sf::Keyboard::E){winsvBrown++;}
            if(key == sf::Keyboard::R){winsvPolar++;}
            if(key == sf::Keyboard::A){winsvParty++;}
          }
          else{
            if(key == sf::Keyboard::Q){lossesToBabby++;}
            if(key == sf::Keyboard::W){lossesToBlack++;}
            if(key == sf::Keyboard::E){lossesToBrown++;}
            if(key == sf::Keyboard::R){lossesToPolar++;}
            if(key == sf::Keyboard::A){lossesToParty++;}
          }
          player.SetMessageBox(messages);

          messages.Update("Your Final Health:", player.GetHealth());
          messages.Update("Bear's Final Health:", fakeBear.GetHealth());
          messages.Update("Last Bear Was:", fakeBear);

          messages.Update("Against Babby:",
          std::to_string(winsvBabby) + "/" +
          std::to_string(winsvBabby + lossesToBabby));
          messages.Update("Against Black:",
          std::to_string(winsvBlack) + "/" +
          std::to_string(winsvBlack + lossesToBlack));
          messages.Update("Against Brown:",
          std::to_string(winsvBrown) + "/" +
          std::to_string(winsvBrown + lossesToBrown));
          messages.Update("Against Polar:",
          std::to_string(winsvPolar) + "/" +
          std::to_string(winsvPolar + lossesToPolar));
          messages.Update("Against Party:",
          std::to_string(winsvParty) + "/" +
          std::to_string(winsvParty + lossesToParty));

          messages.Update("Q - R: Regular Bears",
                          "A: Babby Party",
                          "Z: Random Bear",
                          "D: Dranks, H: Heal");
        }//endif specific key
        else if(event.key.code == sf::Keyboard::D){
          player.Replenish();
          messages.Update("Your Dranks:", player.GetNumDranks() );
        }
        else if(event.key.code == sf::Keyboard::H){
          player.Heal();
        }
      }//endif keypress
    }//end while loop

    window.clear();
    messages.draw();
    status.Update();
    status.draw();
    window.display();
  }
}
