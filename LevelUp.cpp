#include <cstdlib>
#include <ctime>
#include <iostream>

#include "LevelUp.h"
#include "Display/HUD.h"
#include "Feats.h"
#include "Spell.h"
#include "RollDice.h"

bool GetAndAddSpell(sf::RenderWindow& window, HUD& theHUD, Player& player);
void GetAndAddTree( sf::Font& titleFont,
                    sf::Font& mainFont,
                    sf::RenderWindow& window,
                    Player& player,
                    std::vector<SpellID>& potentialCandidates );
void GetAndAddFeat(sf::Font& titleFont,
                    sf::Font& mainFont,
                    sf::RenderWindow& window,
                    Player& player,
                    std::vector<FeatID>& potentialCandidates );

BearID GetBear( sf::RenderWindow& window,
                HUD& theHUD,
                const std::vector<BearID>& potentialBears);
int GetIncompleteSpellIndex(const Player& player, const int treeIndex);
std::vector<FeatID> GetPotentialFeats(const Player& player);



void LevelUp( sf::Font& titleFont,
              sf::Font& mainFont,
              sf::RenderWindow& window,
              Player& player)
{
  bool needBonus = true;
  bool needSkill = ( (1 + player.GetLevel()) % 5 == 0 );

  const bool roomForFeat = player.CanAddMainFeat() || player.CanAddExtraFeat();
  const bool hasAllPotentialFeats = GetPotentialFeats(player).empty();
  const bool canAddFeat = roomForFeat && !hasAllPotentialFeats;

  const bool canGetTree = player.CanUnlockSpellTree();
  const bool incompleteTree = !player.GetIncompleteSpellTrees().empty();
  const bool canAddSpell = canGetTree || incompleteTree;


  if( (!canAddFeat) && (!canAddSpell) ){
    needSkill = false;//Can't add a feat or spell, so we don't try
  }

  std::vector <sf::String> options = {"Fighting?","1:Base Attack Bonus","",
                                      "SpellCasting?","3:Spell Level", "", ""};
  if(needSkill){
    if(canAddFeat){
      options.at(2) = "2:New Feat";
    }
    if(canGetTree){
      options.at(5) = "4:New Spell Tree";
    }
    if(incompleteTree){
      options.at(6) = "5:Unlock Spell";
    }
  }
  HUD theHUD(titleFont, mainFont, player, options, 3, true);
  if(needSkill && canAddFeat && canGetTree && incompleteTree){
    theHUD.messages.Update( "Press either 1 or 3,",
                            "and one of 2, 4, or 5", false);
  }
  else if(needSkill && canAddFeat && canGetTree){
    theHUD.messages.Update("Press either 1 or 3,", "and either 2 or 4", false);
  }
  else if(needSkill && canAddFeat && incompleteTree){
    theHUD.messages.Update("Press either 1 or 3,", "and either 2 or 5", false);
  }
  else if(needSkill && canGetTree && incompleteTree){
    theHUD.messages.Update("Press either 1 or 3,", "and either 4 or 5", false);
  }
  else{
    theHUD.messages.Update("Press either 1 or 3", false);
  }
  player.LevelUp();

  while (window.isOpen()){
    if(!needSkill && !needBonus){
      if(player.ReadyToLevelUp()){
        LevelUp(titleFont, mainFont, window, player);
      }
      return;
    }

    sf::Event event;
    while (window.pollEvent(event)){
      theHUD.playerStats.ToggleMenu(event);
      theHUD.playerStats.ToggleFeats(event);
      if (event.type == sf::Event::Closed){
        window.close();
      }
      else{
        const int choice = theHUD.options.GetChoice(event);
        if(choice == 1 && needBonus){
          player.IncrementBaseAttackBonus();
          needBonus = false;
          options.at(1) = "";
          options.at(4) = "";
          theHUD.options.NewChoices(options,3,true);
        }
        else if(choice == 2 && needSkill && canAddFeat){
          std::vector<FeatID> potentialCandidates = GetPotentialFeats(player);
          GetAndAddFeat(titleFont,mainFont,window,player,potentialCandidates);
          needSkill = false;
          options.at(2) = "";
          options.at(5) = "";
          options.at(6) = "";
          theHUD.options.NewChoices(options,3,true);
        }
        else if(choice == 3 && needBonus){
          player.IncrementSpellcastingLevel();
          needBonus = false;
          options.at(1) = "";
          options.at(4) = "";
          theHUD.options.NewChoices(options,3,true);
        }
        else if(choice == 4 && needSkill && canGetTree){
          std::vector<SpellID> potentialCandidates;
          for(int i = 1; i < int(SpellID::NUM_SPELLS); i += 3){
            if(!player.HasSpell(SpellID(i))){
              potentialCandidates.push_back(SpellID(i));
            }
          }
          if(potentialCandidates.empty()){
            for(int i = 1; i < int(SpellID::NUM_SPELLS); i += 3){
              potentialCandidates.push_back(SpellID(i));
            }
          }
          GetAndAddTree(titleFont,mainFont,window,player,potentialCandidates);
          needSkill = false;
          options.at(2) = "";
          options.at(5) = "";
          options.at(6) = "";
          theHUD.options.NewChoices(options,3,true);
        }
        else if(choice == 5 && needSkill && incompleteTree){
          if(GetAndAddSpell(window,theHUD,player)){
            needSkill = false;
            options.at(2) = "";
            options.at(5) = "";
            options.at(6) = "";
            theHUD.options.NewChoices(options,3,true);
          }
        }//End choice == 5
      }
    }//End while(window.pollEvent(event))

    window.clear();
    theHUD.Update(sf::Vector2f(sf::Mouse::getPosition(window)), true);
    window.draw(theHUD);
    window.display();
  }//end while(window.isOpen())
}



bool GetAndAddSpell(sf::RenderWindow& window, HUD& theHUD, Player& player){
  std::vector<int> incompleteTrees = player.GetIncompleteSpellTrees();
  const int numTrees = incompleteTrees.size();
  for(int i = 0; i < numTrees; i++){
    sf::String name = player.GetSpellName(GetIncompleteSpellIndex(player, i));
    theHUD.messages.Update(std::to_string(i + 1) + ":" + name);
  }
  theHUD.messages.Update("9:Go Back");

  while (window.isOpen()){

    sf::Event event;
    while (window.pollEvent(event)){
      theHUD.playerStats.ToggleMenu(event);
      theHUD.playerStats.ToggleFeats(event);
      if(event.type == sf::Event::Closed){
        window.close();
      }
      else if(event.type == sf::Event::KeyPressed){
        for(int i = 0; i < numTrees; i++){
          if(event.key.code == (i + sf::Keyboard::Num1) ||
             event.key.code == (i + sf::Keyboard::Numpad1) )
          {
            player.UnlockSpell(GetIncompleteSpellIndex(player, i));
            theHUD.messages.Clear();
            return true;
          }
        }
        if(event.key.code == (sf::Keyboard::Num9) ||
           event.key.code == (sf::Keyboard::Numpad9))
        {
          theHUD.messages.Clear();
          return false;
        }
      }
    }//End while(window.pollEvent(event))

    window.clear();
    theHUD.Update(sf::Vector2f(sf::Mouse::getPosition(window)), false);
    window.draw(theHUD);
    window.display();
  }//end while(window.isOpen())
  return false;
}

void GetAndAddTree( sf::Font& titleFont,
                    sf::Font& mainFont,
                    sf::RenderWindow& window,
                    Player& player,
                    std::vector<SpellID>& potentialCandidates )
{
  std::vector<SpellID> candidates;
  int numToAdd = 3;
  while(!potentialCandidates.empty() && numToAdd > 0){
    int index = Roll(1, potentialCandidates.size() ) - 1;
    candidates.push_back(potentialCandidates.at(index));
    potentialCandidates.erase(potentialCandidates.begin() + index);
    numToAdd--;
  }

  std::vector <sf::String> options = {"Which Spell?"};
  for(std::size_t i = 0; i < candidates.size(); i++){
    sf::String name = Spell(candidates.at(i)).GetName();
    options.push_back(std::to_string(i + 1) + ":" + name);
  }
  HUD theHUD(titleFont, mainFont, player, options, 4, false);

  while (window.isOpen()){

    sf::Event event;
    while (window.pollEvent(event)){
      theHUD.playerStats.ToggleMenu(event);
      theHUD.playerStats.ToggleFeats(event);
      if(event.type == sf::Event::Closed){
        window.close();
      }
      else{
        const int choice = theHUD.options.GetChoice(event);
        if(choice > 0){
          player.UnlockSpellTree(SpellTree(candidates.at(choice - 1)));
          return;
        }
      }
    }//End while(window.pollEvent(event))

    window.clear();
    theHUD.Update(sf::Vector2f(sf::Mouse::getPosition(window)), true);
    window.draw(theHUD);
    window.display();
  }//end while(window.isOpen())
}

void GetAndAddFeat( sf::Font& titleFont,
                    sf::Font& mainFont,
                    sf::RenderWindow& window,
                    Player& player,
                    std::vector<FeatID>& potentialCandidates )
{
  std::vector<FeatID> candidates;
  int numToAdd = 4;
  while(!potentialCandidates.empty() && numToAdd > 0){
    int index = Roll(1, potentialCandidates.size() ) - 1;
    candidates.push_back(potentialCandidates.at(index));
    potentialCandidates.erase(potentialCandidates.begin() + index);
    numToAdd--;
  }

  std::vector <sf::String> options = {"Which Feat?"};
  for(std::size_t i = 0; i < candidates.size(); i++){
    sf::String name = Feat(candidates.at(i)).name;
    options.push_back(std::to_string(i + 1) + ":" + name);
  }
  HUD theHUD(titleFont, mainFont, player, options, 3, false);

  while (window.isOpen()){

    sf::Event event;
    while (window.pollEvent(event)){
      theHUD.playerStats.ToggleMenu(event);
      theHUD.playerStats.ToggleFeats(event);
      if(event.type == sf::Event::Closed){
        window.close();
      }
      else{
        const int choice = theHUD.options.GetChoice(event);
        if(choice > 0){
          BearID targetBear = BearID::NUM_BEARS;

          if(Feat(candidates.at(choice - 1)).targetBearMatters){
            std::vector<BearID> potentialBears;
            for(int i = 0; i < int(BearID::NUM_BEARS); i++){
              if(!player.HasFeat(candidates.at(choice - 1),BearID(i),false)){
                potentialBears.push_back(BearID(i));
              }
            }
            targetBear = GetBear(window, theHUD, potentialBears);
          }

          player.AddFeat(candidates.at(choice - 1),targetBear);
          return;
        }
      }
    }//End while(window.pollEvent(event))

    window.clear();
    theHUD.Update(sf::Vector2f(sf::Mouse::getPosition(window)), true);
    window.draw(theHUD);
    window.display();
  }//end while(window.isOpen())
}

BearID GetBear( sf::RenderWindow& window,
                HUD& theHUD,
                const std::vector<BearID>& potentialBears)
{
  theHUD.messages.Clear();
  int firstIndex = 0;
  for(int i = 0; i < 8; i++){
    int bearIndex = (i + firstIndex) % potentialBears.size();
    sf::String bearName = Bear(potentialBears.at(bearIndex)).GetName();
    theHUD.messages.Update(std::to_string(i + 1) + ":" + bearName);
  }
  theHUD.messages.Update("9:More Bears");
  while (window.isOpen()){

    sf::Event event;
    while (window.pollEvent(event)){
      theHUD.playerStats.ToggleMenu(event);
      theHUD.playerStats.ToggleFeats(event);
      if(event.type == sf::Event::Closed){
        window.close();
      }
      else if(event.type == sf::Event::KeyPressed){
        for(int i = 0; i < 8; i++){
          if(event.key.code == (i + sf::Keyboard::Num1) ||
             event.key.code == (i + sf::Keyboard::Numpad1) )
          {
            int bearIndex = (i + firstIndex) % potentialBears.size();
            return potentialBears.at(bearIndex);
          }
        }
        if(event.key.code == (sf::Keyboard::Num9) ||
           event.key.code == (sf::Keyboard::Numpad9))
        {
          theHUD.messages.Clear();
          firstIndex = (firstIndex + 8) % potentialBears.size();
          for(int i = 0; i < 8; i++){
            int bearIndex = (i + firstIndex) % potentialBears.size();
            sf::String bearName = Bear(potentialBears.at(bearIndex)).GetName();
            theHUD.messages.Update(std::to_string(i + 1) + ":" + bearName);
          }
          theHUD.messages.Update("9:More Bears");
        }
      }
    }//End while(window.pollEvent(event))

    window.clear();
    theHUD.Update(sf::Vector2f(sf::Mouse::getPosition(window)), false);
    window.draw(theHUD);
    window.display();
  }//end while(window.isOpen())

  return BearID::NUM_BEARS;//Should only get here if they quit the game
}

int GetIncompleteSpellIndex(const Player& player, const int treeIndex){
  std::vector<int> incompleteTrees = player.GetIncompleteSpellTrees();

  int spellIndex = 3 * incompleteTrees.at(treeIndex) + 1;//Second spell in tree
  if(player.GetMaxNumSpell(spellIndex) > 0){
    spellIndex++;//If they have the 2nd spell already, target the 3rd instead
  }

  return spellIndex;
}

std::vector<FeatID> GetPotentialFeats(const Player& player){
  std::vector<FeatID> potentialCandidates;
  const bool canAddMainFeat = player.CanAddMainFeat();
  for(int i = 0; i < int(FeatID::NUM_FEATS); i++){
    if( Feat(FeatID(i)).permanent || canAddMainFeat){
      if(!player.HasFeat(FeatID(i),false)){
        potentialCandidates.push_back(FeatID(i));
      }
      else if(Feat(FeatID(i)).targetBearMatters){
        bool done = false;
        for(int j = 0; (!done) && ( j < int(BearID::NUM_BEARS) ); j++){
          if(!player.HasFeat(FeatID(i),BearID(j),false)){
            potentialCandidates.push_back(FeatID(i));
            done = true;
          }
        }
      }
    }
  }
  return potentialCandidates;
}
