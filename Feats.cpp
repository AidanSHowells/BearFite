#include <iostream>
#include "Feats.h"
#include "Player.h"

Feat::Feat(const FeatID feat){
  featID = feat;
  if(feat == FeatID::tempPerm){
    permanent = true;
  }
  else if(feat == FeatID::tempToggle1){
    permanent = false;
    cost = 0;
  }
  else if(feat == FeatID::tempToggle2){
    permanent = false;
    cost = 0;
  }
  else if(feat == FeatID::tempPool1){
    permanent = false;
    cost = 1;
  }
  else if(feat == FeatID::tempPool2){
    permanent = false;
    cost = 2;
  }
  else if(feat == FeatID::NUM_FEATS){
    std::cerr << "Warning! ";
    std::cerr << "Illegal use of FeatID::NUM_FEATS in Feat constructor.\n\n";
  }
  else{
    std::cerr << "Warning! ";
    std::cerr << "Attempted use of FeatID unknown to Feat constructor.\n";
    std::cerr << "The number corresponding to the invalid feat was ";
    std::cerr << int(feat) << ".\n\n";
  }
}

sf::String FeatName(const FeatID theFeat){
  sf::String name = "";
  if(theFeat == FeatID::tempPerm){
    name = "Perm Feat";
  }
  else if(theFeat == FeatID::tempToggle1){
    name = "Toggle Feat Eins";
  }
  else if(theFeat == FeatID::tempToggle2){
    name = "Toggle Feat Zwei";
  }
  else if(theFeat == FeatID::tempPool1){
    name = "Pool Feat Eins";
  }
  else if(theFeat == FeatID::tempPool2){
    name = "Pool Feat Zwei";
  }
  else if(theFeat == FeatID::NUM_FEATS){
    std::cerr << "Warning! ";
    std::cerr << "Illegal use of FeatID::NUM_FEATS in FeatName function.\n\n";
  }
  else{
    std::cerr << "Warning! Attempted use of FeatID unknown to FeatName.\n";
    std::cerr << "The number corresponding to the invalid feat was ";
    std::cerr << int(theFeat) << ".\n\n";
  }
  return name;
}
