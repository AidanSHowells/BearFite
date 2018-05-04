#include <cstdlib>
#include <ctime>
#include <array>
#include <iostream>
#include <fstream>

#include "HUD.h"
#include "BearBattle.h"
#include "Player.h"

void UpdateSpecialBear(BearID& bearID, ModifierID& modID, MessageBox& messages);
void UpdatePlayerAbilities(Player& player, MessageBox& messages);
void RecordWinLoss(const std::array<int, 2 * int(BearID::NUM_BEARS)>& winLoss,
                   MessageBox& messages);

//TEMP: Belongs in FindBear.h:
bool FindBear(const sf::Keyboard::Key theKey,
              BattleHUD& theHUD,
              const BearID bearID,
              const ModifierID modID);

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
  std::array<int, 2 * int(BearID::NUM_BEARS)> scoreArray = {};//All zeros

  MessageBox messages(window,courierNewBd,courierNew,"Messages:");
  messages.Update("Q: Fight Babby Party",
                  "A: New Abilities",
                  "S: New Special Bear",
                  "F: Fight Special Bear",
                  "Z: Random Bear");

  Player player;
  player.SetMessageBox(messages);
  PlayerStats status(window,courierNewBd,courierNew,player);

  BearID specialBearID;
  ModifierID specialModID;

  UpdateSpecialBear(specialBearID, specialModID, messages);

  while (window.isOpen()){

    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){
        window.close();
      }
      if (event.type == sf::Event::KeyPressed){
        if(event.key.code == sf::Keyboard::Q ||
           event.key.code == sf::Keyboard::F ||
           event.key.code == sf::Keyboard::Z)
        {
          int bearHealth = 420;
          Bear fakeBear;
          BattleHUD battleHUD(window,courierNewBd,courierNew,player,fakeBear);
          if(FindBear(event.key.code, battleHUD, specialBearID, specialModID)){
            if(BearBattle(battleHUD, fakeBear)){
              scoreArray.at(2 * int(fakeBear.GetID()))++;
            }
            else{
              scoreArray.at(2 * int(fakeBear.GetID()) + 1)++;
            }
            player.SetMessageBox(messages);
            RecordWinLoss(scoreArray,messages);

            messages.Update("Your Final Health:", player.GetHealth(), true);
            messages.Update("Bear's Final Health:", fakeBear.GetHealth());
            messages.Update("Last Bear Was:", fakeBear);

            messages.Update("Q: Fight Babby Party",
                            "A: New Abilities",
                            "S: New Special Bear",
                            "F: Fight Special Bear",
                            "Z: Random Bear",
                            "D: Dranks, H: Heal");
          }//endif FindBear
        }//endif specific key
        else if(event.key.code == sf::Keyboard::A){
          UpdatePlayerAbilities(player, messages);
        }
        else if(event.key.code == sf::Keyboard::S){
          UpdateSpecialBear(specialBearID, specialModID, messages);
        }
        else if(event.key.code == sf::Keyboard::D){
          player.Replenish();
          messages.Update("Your Dranks:", player.GetNumDranks() );
        }
        else if(event.key.code == sf::Keyboard::H ||
                event.key.code == sf::Keyboard::Num4 ||
                event.key.code == sf::Keyboard::Numpad4)
        {
          player.Heal();
        }
      }//endif keypress
    }

    window.clear();
    messages.draw();
    status.Update();
    status.draw();
    window.display();
  }//end while(window.isOpen())

  return 0;
}

void UpdateSpecialBear(BearID& bearID, ModifierID& modID, MessageBox& messages){
  int bearInt;
  int modInt;

  //Open the input file
  std::ifstream fin;
  fin.open("input.txt");
  if(!fin.is_open()){
    messages.Update(sf::String("Failed to open file"));
    return;
  }

  //Get the bear
  fin >> bearInt;
  if(fin.fail() || bearInt < 0 || bearInt > int(BearID::NUM_BEARS)){
    messages.Update(sf::String("Invalid Bear."));
    fin.close();
    return;
  }
  //Get the modifier
  fin >> modInt;
  if(fin.fail() || modInt < 0 || modInt > int(ModifierID::SIZE)){
    messages.Update(sf::String("Invalid Modifier."));
    fin.close();
    return;
  }

  fin.close();

  bearID = BearID(bearInt);
  modID = ModifierID(modInt);
  if(modID != ModifierID::none){
    messages.Update(sf::String("Bear is ") + Modifier(modID).name, true);
  }
  messages.Update(sf::String("New Special Bear is"), Bear(bearID));
}

void UpdatePlayerAbilities(Player& player, MessageBox& messages){
  int tempInt;
  std::array<int,6> newAbil;

  //Open the input file
  std::ifstream fin;
  fin.open("input.txt");
  if(!fin.is_open()){
    messages.Update(sf::String("Failed to open file"));
    return;
  }

  //The first two things in the file are the bear and its modifier
  for(int i = 0; i < 2; i++){
    fin >> tempInt;
    if(fin.fail()){
      messages.Update(sf::String("Invalid file format."));
      return;
    }
  }

  for(int i = 0; i < 6; i++){
    fin >> newAbil.at(i);
    if(fin.fail()){
      messages.Update(sf::String("Invalid file format."));
      return;
    }
  }
  player.SetAbil(newAbil);
  messages.Update(sf::String("Abilities Updated"));

  fin.close();
}

void RecordWinLoss(const std::array<int, 2 * int(BearID::NUM_BEARS)>& winLoss,
                   MessageBox& messages)
{
  //Open the output file
  std::ofstream fout;
  fout.open("output.txt");
  if(!fout.is_open()){
    messages.Update(sf::String("Failed to open file."),
                    sf::String("Stats won't be kept"));
    return;
  }

  //Record the wins and losses
  std::string bearName;
  for(int i = 0; i < int(BearID::NUM_BEARS); i++){
    bearName = Bear(BearID(i)).GetName();
    fout << "Against " << bearName << "bear: " << winLoss.at(2 * i) << "/";
    fout << winLoss.at(2 * i) + winLoss.at(2 * i + 1) << "\n";
  }

  fout.close();
}

//TEMP: Belongs in FindBear.cpp
#include "HUD.h"
#include "Bear.h"
#include "Modifier.h"
#include "RollDice.h"

bool FindBear(const sf::Keyboard::Key theKey,
              BattleHUD& theHUD,
              const BearID bearID,
              const ModifierID modID)
{
  Bear theBear[4];
  Modifier theModifier = Modifier(ModifierID::none);

  if(sf::Keyboard::Z == theKey){//Random Bear
    int randInt = Roll(1, int(BearID::NUM_BEARS)) - 1;
    theBear[0] = Bear(BearID(randInt));

    randInt = Roll(1, int(ModifierID::SIZE)) - 1;
    if(1 == Roll(1,3)){
      randInt = 0;
    }
    theModifier = Modifier(ModifierID(randInt));
  }
  else if(sf::Keyboard::Q == theKey){//Babby Party
    for(int i = 0; i < 4; i++){
      Bear bear(BearID::Babby);
      theBear[i] = bear;
    }
    theHUD.AddEnemyBears(theBear, 4);
    return true;//This is gross, but this part of the function is temporary
  }
  else if(sf::Keyboard::F == theKey){//Special Bear
    theBear[0] = Bear(bearID);
    theModifier = Modifier(modID);
  }
  else{
    theHUD.messages.Update(sf::String("Whoops! That key is"),
                           sf::String("not supported."));
    return false;//Failure
  }

  //Functions can't return C-style arrays, so we have to get "creative":
  std::array<Bear, 4> bears = theBear[0].ApplyModifier(theModifier);
  for(int i = 0; i < 4; i++){
    theBear[i] = bears.at(i);
  }

  int numBears = 1 + theModifier.numTwins;//To be replaced with the next line
  //int numBears = 1 + theModifier.numCompanians + theModifier.numTwins;
  theHUD.AddEnemyBears(theBear, numBears);
  return true;//Success
}
//Eventual Algorithm:
//Make vector of bears whose base level is small enough
//Choose a bear from the vector at random
//Some (25% ?) chance of no modifier. Else:
  //Make vector of modifiers whose effective level is small enough (none, etc.)
  //Choose a modifier from the vector at random


//end TEMP (Belongs in FindBear.cpp)
