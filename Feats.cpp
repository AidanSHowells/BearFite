#include <iostream>
#include "Feats.h"
#include "Player.h"

Feat::Feat(const FeatID feat, const BearID theBearID){
  featID = feat;
  targetBearID = theBearID;//Default is NUM_BEARS
  if(feat == FeatID::studied_dodge){
    active = true;
    permanent = true;
    cost = 0;
    if(theBearID == BearID::NUM_BEARS){
      std::cerr << "Warning! The \"Studied Dodge\" feat must be provided a ";
      std::cerr << "bear in order to function correctly\n\n";
      name = "Studied Dodge";
    }
    else{
      name = "Dodge " + Bear(theBearID).GetName();
    }
  }
  else if(feat == FeatID::escape_artist){
    name = "Escape Artist";
    active = true;
    permanent = true;
    cost = 0;
  }
  else if(feat == FeatID::power_attack){
    name = "Power Attack";
    permanent = false;
    cost = 0;
  }
  else if(feat == FeatID::whirlwind_attack){
    name = "Whirlwind Attack";
    permanent = false;
    cost = 0;
  }
  else if(feat == FeatID::gulper){
    name = "Gulper";
    permanent = false;
    cost = 1;
  }
  else if(feat == FeatID::cobra_strike){
    name = "Cobra Strike";
    permanent = false;
    cost = 1;
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
