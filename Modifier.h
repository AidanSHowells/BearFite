#ifndef MODIFIER_H
#define MODIFIER_H

#include <SFML/System/String.hpp>
#include "Abilities.h"

//List of all possible modifiers (plus NUM_MODIFIERS, which is always last):
enum class ModifierID{none, beefy, exact, sturdy, genious, socrates, handsome,
                      numerous, experienced, elite, keen, crictal, large,
                      hungry, mother, life_saving,
                      NUM_MODIFIERS};

sf::String ModifierName(const ModifierID modID);

#endif
