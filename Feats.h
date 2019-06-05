#ifndef FEATS_H
#define FEATS_H

#include <SFML/System/String.hpp>
#include "Bear.h"//For BearID

//List of all possible feats (plus NUM_FEATS, which is always last):
enum class FeatID{studied_dodge, escape_artist,
                  power_attack, whirlwind_attack,
                  gulper, cobra_strike,
                  NUM_FEATS};

struct Feat{
  Feat(const FeatID feat, const BearID theBearID = BearID::NUM_BEARS);
  FeatID featID;
  sf::String name = sf::String("");
  bool permanent = true;
  bool active = false;
  int cost = 0;
  BearID targetBearID = BearID::NUM_BEARS;//Some feats are specific to 1 species
};

#endif
