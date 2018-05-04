#ifndef MODIFIER_H
#define MODIFIER_H

#include <SFML/System/String.hpp>

//List of all modifiers that can occur (plus SIZE, which is always last):
enum class ModifierID{none, beefy, exact, sturdy, genious, socrates, handsome,
                      numerous, experienced, keen, crictal, SIZE};


//NOTE: If you make numTwins and/or numCompanians dynamic for some modifier,
//      your'll need to edit FindBear(). Similarly, if you make them both
//      non-zero, or either one non-zero for any modifier where derivedModifier
//      isn't nullptr, you'll have to edit Bear::ApplyModifier().
struct Modifier{
  Modifier(ModifierID modID = ModifierID::none);
  //ModifierID identifier = ModifierID::none;
  Modifier* derivedModifier = nullptr;
  //sf::String GetName() const;//Function for getting the name
  sf::String name = sf::String("None");
  int effectiveLevel = 0;

  int levelAdd = 0;
  int abilAdd[6] = {0,0,0,0,0,0};

  int critThreatMult = 1;
  int critThreatAdd = 0;
  int critMultMult = 1;
  int critMultAdd = 0;

  //int numCompanians = 0;//How many (non-identical) companians are given
  //Some stuff about the relative levels of possible companians goes here

  int numTwins = 0;//How many identical bears are added

  //bool isInvisible = false;//We want to be able to make "life saving" a suprise
};


#endif
