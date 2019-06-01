#ifndef FEATS_H
#define FEATS_H

#include <SFML/System/String.hpp>

//List of all possible feats (plus NUM_FEATS, which is always last):
enum class FeatID{tempPerm, tempToggle1, tempToggle2, tempPool1, tempPool2,
                  NUM_FEATS};

sf::String FeatName(const FeatID theFeat);

#endif
