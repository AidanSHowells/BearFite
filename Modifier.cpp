#include <iostream> //for std::cerr
#include "Modifier.h"
#include "Bear.h"
#include "RollDice.h"

sf::String ModifierName(const ModifierID modID){
  sf::String name;

  if(ModifierID::none == modID){
    name = sf::String("None");
  }
  else if(ModifierID::beefy == modID){
    name = sf::String("Beefy");
  }
  else if(ModifierID::exact == modID){
    name = sf::String("Exact");
  }
  else if(ModifierID::sturdy == modID){
    name = sf::String("Sturdy");
  }
  else if(ModifierID::genious == modID){
    name = sf::String("Genious");
  }
  else if(ModifierID::socrates == modID){
    name = sf::String("Socrates");
  }
  else if(ModifierID::handsome == modID){
    name = sf::String("Handsome");
  }
  else if(ModifierID::numerous == modID){
    name = sf::String("Numerous");
  }
  else if(ModifierID::experienced == modID){
    name = sf::String("Experienced");
  }
  else if(ModifierID::elite == modID){
    name = sf::String("Elite");
  }
  else if(ModifierID::keen == modID){
    name = sf::String("Keen");
  }
  else if(ModifierID::crictal == modID){
    name = sf::String("Crictal");
  }
  else if(ModifierID::large == modID){
    name = sf::String("Large");
  }
  else if(ModifierID::hungry == modID){
    name = sf::String("Hungry");
  }
  else if(ModifierID::mother == modID){
    name = sf::String("Mother");
  }
  else if(ModifierID::life_saving == modID){
    name = sf::String("Undying");
  }
  else if(ModifierID::NUM_MODIFIERS == modID){
    std::cerr << "Warning! Attempted use of ModifierID::NUM_MODIFIERS in ";
    std::cerr << "ModifierName.\n\n";
  }
  else{
    std::cerr << "Warning! ";
    std::cerr << "Attempted use of modifier unknown to ModifierName.\n";
    std::cerr << "The number corresponding to the invalid modifier was ";
    std::cerr << int(modID) << ".\n\n";
  }
  return name;
}


std::array<Bear, 4> Bear::ApplyModifier(const ModifierID modID){
  modifier = modID;

  std::array<Bear, 4> theBears = {Bear(), Bear(), Bear(), Bear()};

  if(ModifierID::none == modID){
    //Do nothing
  }
  else if(ModifierID::beefy == modID){
    abil.at(int(Abil::STR)) += 10;
  }
  else if(ModifierID::exact == modID){
    abil.at(int(Abil::DEX)) += 10;
  }
  else if(ModifierID::sturdy == modID){
    abil.at(int(Abil::CON)) += 10;
  }
  else if(ModifierID::genious == modID){
    abil.at(int(Abil::INT)) += 10;
  }
  else if(ModifierID::socrates == modID){
    abil.at(int(Abil::WIS)) += 10;
  }
  else if(ModifierID::handsome == modID){
    abil.at(int(Abil::CHA)) += 10;
  }
  else if(ModifierID::numerous == modID){
    theBears.at(1) = (*this);
    theBears.at(2) = (*this);
  }
  else if(ModifierID::experienced == modID){
    level += 5;
  }
  else if(ModifierID::elite == modID){
    for(int i = 0; i < int(Abil::NUM_ABIL); i++){
      abil.at(i) += 5;
    }
    level += 5;
  }
  else if(ModifierID::keen == modID){
    critThreat = 2 * critThreat + 3;
  }
  else if(ModifierID::crictal == modID){
    critMult = 2 * critMult + 3;
  }
  else if(ModifierID::large == modID){
    abil.at(int(Abil::STR)) += 10;
    abil.at(int(Abil::DEX)) = std::max(abil.at(int(Abil::DEX)) - 5, 1);
    abil.at(int(Abil::CON)) += 5;
  }
  else if(ModifierID::hungry == modID){
    abil.at(int(Abil::CON)) = std::max(abil.at(int(Abil::CON)) - 5, 1);
    //Also make the bear perma-argry: See Bear::IsAngry
    //Also make the bear love fish: See Bear::FeedFish
  }
  else if(ModifierID::mother == modID){
    int numBabbies = Roll(1,2);
    for(int i = 0; i < numBabbies; i++){
      theBears.at(i + 1) = Bear(BearID::Babby);
    }
  }
  else if(ModifierID::life_saving == modID){
    modifierNameVisible = false;
    //The real meat of this one is in Bear::IsDead()
  }
  else if(ModifierID::NUM_MODIFIERS == modID){
    std::cerr << "Warning! Attempted use of ModifierID::NUM_MODIFIERS in ";
    std::cerr << "ApplyModifier.\n\n";
  }
  else{
    std::cerr << "Warning! ";
    std::cerr << "Attempted use of modifier unknown to ApplyModifier.\n";
    std::cerr << "The number corresponding to the invalid modifier was ";
    std::cerr << int(modID) << ".\n\n";
  }

  theBears.at(0) = *this;

  return theBears;
}
