#include <iostream>
#include "Feats.h"
#include "Player.h"
#include "Bear.h" //For Bear::GetName()

Feat::Feat(const FeatID feat, const BearID theBearID){
  featID = feat;
  if(feat == FeatID::studied_dodge){
    permanent = true;
    cost = 0;
    targetBearMatters = true;
    if(theBearID == BearID::NUM_BEARS){
      name = "Studied Dodge";
    }
    else{
      targetBearID = theBearID;
      name = "Dodge " + Bear(theBearID).GetName();
    }
  }
  else if(feat == FeatID::escape_artist){
    name = "Escape Artist";
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

  active = permanent; //Permanent feats start (and are always) active; other
                      //feats start deactivated
}
