#include <iostream> //for std::cerr
#include "Modifier.h"

Modifier::Modifier(ModifierID modID){
  if(ModifierID::none == modID){
    //Do nothing
  }
  else if(ModifierID::beefy == modID){
    name = sf::String("Beefy");
    abilAdd[int(Abil::STR)] = 10;
  }
  else if(ModifierID::exact == modID){
    name = sf::String("Exact");
    abilAdd[int(Abil::DEX)] = 10;
  }
  else if(ModifierID::sturdy == modID){
    name = sf::String("Sturdy");
    abilAdd[int(Abil::CON)] = 10;
  }
  else if(ModifierID::genious == modID){
    name = sf::String("Genious");
    abilAdd[int(Abil::INT)] = 10;
  }
  else if(ModifierID::socrates == modID){
    name = sf::String("Socrates");
    abilAdd[int(Abil::WIS)] = 10;
  }
  else if(ModifierID::handsome == modID){
    name = sf::String("Handsome");
    abilAdd[int(Abil::CHA)] = 10;
  }
  else if(ModifierID::numerous == modID){
    name = sf::String("Numerous");
    numTwins = 2;
  }
  else if(ModifierID::experienced == modID){
    name = sf::String("Experienced");
    levelAdd = 5;
  }
  else if(ModifierID::elite == modID){
    name = sf::String("Elite");
    for(int i = 0; i < int(Abil::NUM_ABIL); i++){
      abilAdd[i] = 5;
    }
    levelAdd = 5;
  }
  else if(ModifierID::keen == modID){
    name = sf::String("Keen");
    critThreatMult = 2;
    critThreatAdd = 3;
  }
  else if(ModifierID::crictal == modID){
    name = sf::String("Crictal");
    critMultMult = 2;
    critMultAdd = 1;
  }
  else if(ModifierID::NUM_MODIFIERS == modID){
    std::cerr << "Warning! ";
    std::cerr << "Attempted use of ModifierID::NUM_MODIFIERS in constructor.\n";
    std::cerr << "\n";
  }
  else{
    std::cerr << "Warning! Attempted use of modifier unknown to constructor.\n";
    std::cerr << "The number corresponding to the invalid modifier was ";
    std::cerr << int(modID) << ".\n\n";
  }
}
