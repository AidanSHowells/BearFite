#include <cstdlib>
#include <ctime>
#include <array>
#include <iostream>
#include <fstream>

#include "Display/HUD.h"
#include "BearBattle.h"
#include "Player.h"
#include "Spell.h"
#include "Feats.h"
#include "FindBear.h"

void UpdateSpecialBear(BearID& bearID, ModifierID& modID, MessageBox& messages);
void UpdatePlayerAbilities(Player& player, MessageBox& messages);
void UpdateBodyCount(Player& player, MessageBox& messages);
void ResetPlayerSpells(Player& player, MessageBox& messages);
void RecordWinLoss(const std::array<int, 2 * int(BearID::NUM_BEARS)>& winLoss,
                   MessageBox& messages);

enum class BearSelectionMethod {random, preselected, normal};

std::array<Bear,4> GetBears(const BearSelectionMethod method,
                            const Player& player,
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
  sf::RenderWindow window(sf::VideoMode(800, 600),
                          "BearFite",
                          sf::Style::Titlebar | sf::Style::Close);
  window.setKeyRepeatEnabled(false);

  //Keep track of wins
  std::array<int, 2 * int(BearID::NUM_BEARS)> scoreArray = {};//All zeros

  MessageBox messages(courierNewBd,courierNew,"Messages:");
  messages.Update("A/S/G:Get Abilities,",
                  "Bear, or Spells.",
                  "Q:Lock Body Count.",
                  "F/Z/X:Fight Special,",
                  "Rand, or Normal Bear.");

  Player player;
  player.SetMessageBox(messages);
  PlayerStats status(courierNewBd,courierNew,player);

  BearID specialBearID;
  ModifierID specialModID;
  bool bodyCountLocked = false;

  UpdateSpecialBear(specialBearID, specialModID, messages);

  while (window.isOpen()){

    sf::Event event;
    while (window.pollEvent(event)){
      status.ToggleMenu(event);
      status.ToggleFeats(event);
      if (event.type == sf::Event::Closed){
        window.close();
      }
      else if (event.type == sf::Event::KeyPressed){
        if(event.key.code == sf::Keyboard::F ||
           event.key.code == sf::Keyboard::Z ||
           event.key.code == sf::Keyboard::X)
        {
          BearSelectionMethod method;
          if(event.key.code == sf::Keyboard::F){
            method = BearSelectionMethod::preselected;
          }
          else if(event.key.code == sf::Keyboard::Z){
            method = BearSelectionMethod::random;
          }
          else if(event.key.code == sf::Keyboard::X){
            method = BearSelectionMethod::normal;
          }

          std::array<Bear,4> bears;
          bears = GetBears(method, player, specialBearID, specialModID);
          BearID enemyBearID = bears.at(0).GetID();
          BattleHUD battleHUD(courierNewBd,courierNew,player,bears);

          Winner winner = BearBattle(window, battleHUD);
          player.SetMessageBox(messages);
          player.PostBattleReset(winner == Winner::player);

          if(Winner::player == winner){
            scoreArray.at(2 * int(enemyBearID))++;
          }
          else if(Winner::bear == winner){
            scoreArray.at(2 * int(enemyBearID) + 1)++;
          }
          RecordWinLoss(scoreArray,messages);

          Bear lastBear = *(battleHUD.GetBearPtr());
          messages.Update("Your Final Health:", player.GetHealth(), true);
          messages.Update("Bear's Final Health:", lastBear.GetHealth());

          sf::String name = lastBear.GetName() + sf::String("bear");
          MessageBox::Style bearStyle = MessageBox::Style::alignLastLineRight;
          messages.Update("Last Bear Living Was:", name, false, bearStyle);

          if(bodyCountLocked){
            UpdateBodyCount(player,messages);
            messages.Update("A/S/G:Get Abilities,",
                            "Bear, or Spells.",
                            "Q:Unlock Body Count.",
                            "F/Z/X:Fight Special,",
                            "Rand, or Normal Bear.",
                            "D:Dranks, H:Heal.");
          }
          else{
            messages.Update("A/S/G:Get Abilities,",
                            "Bear, or Spells.",
                            "Q:Lock Body Count.",
                            "F/Z/X:Fight Special,",
                            "Rand, or Normal Bear.",
                            "D:Dranks, H:Heal.");
          }
        }
        else if(event.key.code == sf::Keyboard::A){
          UpdatePlayerAbilities(player, messages);
        }
        else if(event.key.code == sf::Keyboard::S){
          UpdateSpecialBear(specialBearID, specialModID, messages);
        }
        else if(event.key.code == sf::Keyboard::G){
          ResetPlayerSpells(player, messages);
        }
        else if(event.key.code == sf::Keyboard::Q){
          bodyCountLocked = !bodyCountLocked;
          if(bodyCountLocked){
            UpdateBodyCount(player,messages);
            messages.Update("Body Count Locked");
          }
          else{
            messages.Update("Body Count Unlocked");
          }
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
    window.draw(messages);
    status.Update(sf::Vector2f(sf::Mouse::getPosition(window)), false, false);
    window.draw(status);
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
  if(fin.fail() || modInt < 0 || modInt > int(ModifierID::NUM_MODIFIERS)){
    messages.Update(sf::String("Invalid Modifier."));
    fin.close();
    return;
  }

  fin.close();

  bearID = BearID(bearInt);
  modID = ModifierID(modInt);

  if(modID != ModifierID::none){
    if(ModifierID::NUM_MODIFIERS == modID){
      messages.Update(sf::String("Modifier is Random"), true);
    }
    else{
      messages.Update(sf::String("Bear is ") + ModifierName(modID), true);
    }
  }

  if(BearID::NUM_BEARS == bearID){
    messages.Update(sf::String("New Special Bear"), sf::String("is Random"));
  }
  else{
    sf::String name = Bear(bearID).GetName() + sf::String("bear");
    MessageBox::Style bearStyle = MessageBox::Style::alignLastLineRight;
    messages.Update(sf::String("New Special Bear is:"), name, false, bearStyle);
  }
}

void UpdatePlayerAbilities(Player& player, MessageBox& messages){
  int tempInt;
  int level;
  int baseAttackBonus;
  int spellLevel;
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

  fin >> level;
  if(fin.fail()){
    messages.Update(sf::String("Invalid file format."));
    return;
  }

  fin >> baseAttackBonus;
  if(fin.fail()){
    messages.Update(sf::String("Invalid file format."));
    return;
  }

  fin >> spellLevel;
  if(fin.fail()){
    messages.Update(sf::String("Invalid file format."));
    return;
  }

  //Next is the body count
  fin >> tempInt;
  if(fin.fail()){
    messages.Update(sf::String("Invalid file format."));
    return;
  }

  for(int i = 0; i < 6; i++){
    fin >> newAbil.at(i);
    if(fin.fail()){
      messages.Update(sf::String("Invalid file format."));
      return;
    }
  }

  player.SetLevel(level);
  player.SetBaseAttackBonus(baseAttackBonus);
  player.SetSpellcastingLevel(spellLevel);
  player.SetAbil(newAbil);
  messages.Update(sf::String("Abilities Updated"));

  fin.close();
}

void UpdateBodyCount(Player& player, MessageBox& messages){
  int tempInt;
  int bodyCount;

  //Open the input file
  std::ifstream fin;
  fin.open("input.txt");
  if(!fin.is_open()){
    messages.Update(sf::String("Failed to open file"));
    return;
  }

  //First 5 things are: bear, modifier, lvl, BAB, spell lvl
  for(int i = 0; i < 5; i++){
    fin >> tempInt;
    if(fin.fail()){
      messages.Update(sf::String("Invalid file format."));
      return;
    }
  }

  fin >> bodyCount;
  if(fin.fail()){
    messages.Update(sf::String("Invalid file format."));
    return;
  }

  player.SetBodyCount(bodyCount);
}

void ResetPlayerSpells(Player& player, MessageBox& messages){
  int tempInt;
  int spellInt;
  int featInt;
  int bearInt;
  std::array<int,3> newNumSpells;

  //Open the input file
  std::ifstream fin;
  fin.open("input.txt");
  if(!fin.is_open()){
    messages.Update(sf::String("Failed to open file"));
    return;
  }

  //First 12 things are: bear, modifier, lvl, BAB, spell lvl, body count, abils
  for(int i = 0; i < 12; i++){
    fin >> tempInt;
    if(fin.fail()){
      messages.Update(sf::String("Invalid file format."));
      return;
    }
  }

  player.ClearSpells();

  fin >> spellInt;
  while(!fin.fail() && spellInt > 0 && spellInt < int(SpellID::NUM_SPELLS)){

    for(int i = 0; i < 3 && !fin.fail(); i++){
      fin >> newNumSpells.at(i);
      if(fin.fail()){
        messages.Update(sf::String("Invalid file format."));
        return;
      }
    }
    if(!fin.fail()){
      SpellTree tree = SpellTree(SpellID(spellInt));
      for(int i = 0; i < 3; i++){
        tree.numSpells.at(i) = newNumSpells.at(i);
        tree.maxSpells.at(i) = newNumSpells.at(i);
      }
      player.UnlockSpellTree(tree);
      fin >> spellInt;
    }
  }

  //Reading only stops without failing in case of an invalid SpellID
  if(!fin.fail() && spellInt != 420){
    messages.Update(sf::String("SpellID must be"), sf::String("between 1 and "
                      + std::to_string(int(SpellID::NUM_SPELLS)-1)), true);

    fin.close();
    return;
  }

  messages.Update(sf::String("Spells Updated"));

  player.ClearFeats();

  fin >> featInt;
  while(!fin.fail() && featInt >= 0 && featInt < int(FeatID::NUM_FEATS)){
    fin >> bearInt;
    if(fin.fail()){
      messages.Update(sf::String("Invalid file format."));
      return;
    }
    else if(bearInt < 0 || bearInt > int(BearID::NUM_BEARS)){
      messages.Update(sf::String("BearID must be"), sf::String("between 0 and "
                        + std::to_string(int(BearID::NUM_BEARS))), true);
      return;
    }
    else{
      player.AddFeat(FeatID(featInt),BearID(bearInt));
    }
    fin >> featInt;
  }

  if(!fin.fail()){
    messages.Update(sf::String("FeatID must be"), sf::String("between 0 and "
                      + std::to_string(int(FeatID::NUM_FEATS)-1)), true);
  }

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

#include "Bear.h"
#include "Modifier.h"
#include "RollDice.h"

std::array<Bear,4> GetBears(const BearSelectionMethod method,
                            const Player& player,
                            const BearID bearID,
                            const ModifierID modID)
{
  Bear tempBear;
  ModifierID theModifier = ModifierID::none;

  if(BearSelectionMethod::random == method){
    int randInt = Roll(1, int(BearID::NUM_BEARS)) - 1;
    tempBear = Bear(BearID(randInt));

    randInt = Roll(1, int(ModifierID::NUM_MODIFIERS)) - 1;
    if(1 == Roll(1,3)){
      randInt = 0;
    }
    theModifier = ModifierID(randInt);
  }
  else if(BearSelectionMethod::preselected == method){
    if(bearID == BearID::NUM_BEARS){//Random bear in this case
      int randInt = Roll(1, int(BearID::NUM_BEARS)) - 1;
      tempBear = Bear(BearID(randInt));
    }
    else{
      tempBear = Bear(bearID);
    }
    if(modID == ModifierID::NUM_MODIFIERS){//Random Modifier in this case
      int randInt = Roll(1, int(ModifierID::NUM_MODIFIERS)) - 1;
      theModifier = ModifierID(randInt);
    }
    else{
      theModifier = modID;
    }
  }
  else if(BearSelectionMethod::normal == method){
    return FindBear(player);
  }

  return tempBear.ApplyModifier(theModifier);
}
