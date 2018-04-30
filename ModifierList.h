#ifndef MODIFIERLIST_H
#define MODIFIERLIST_H

//List of all modifiers that can occur (plus SIZE, which is always last):
enum class ModifierID{none, beefy, exact, sturdy, genious, socrates, handsome,
                      numerous, experienced, keen, crictal, SIZE};


//NOTE: If you make numTwins and/or numCompanians dynamic for some modifier,
//      your'll need to edit FindBear(). Similarly, if you make them both
//      non-zero, or either one non-zero for any modifier where derivedModifier
//      isn't nullptr, you'll have to edit Bear::ApplyModifier().
struct Modifier{
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
  //FIXME: Some stuff about the relative levels of possible companians goes here

  int numTwins = 0;//How many identical bears are added

  //bool isInvisible = false;//We want to be able to make "life saving" a suprise
};

Modifier GetModifier(ModifierID);


struct Beefy : Modifier{
  Beefy(){
    name = sf::String("Beefy");
    abilAdd[0] = 10;
  }
};

struct Exact : Modifier{
  Exact(){
    name = sf::String("Exact");
    abilAdd[1] = 10;
  }
};

struct Sturdy : Modifier{
  Sturdy(){
    name = sf::String("Sturdy");
    abilAdd[2] = 10;
  }
};

struct Genious : Modifier{
  Genious(){
    name = sf::String("Genious");
    abilAdd[3] = 10;
  }
};

struct Socrates : Modifier{
  Socrates(){
    name = sf::String("Socrates");
    abilAdd[4] = 10;
  }
};

struct Handsome : Modifier{
  Handsome(){
    name = sf::String("Handsome");
    abilAdd[5] = 10;
  }
};

struct Numerous : Modifier{
  Numerous(){
    name = sf::String("Numerous");
    numTwins = 2;
  }
};

struct Experienced : Modifier{
  Experienced(){
    name = sf::String("Experienced");
    levelAdd = 5;
  }
};

struct Keen : Modifier{
  Keen(){
    name = sf::String("Keen");
    critThreatMult = 2;
    critThreatAdd = 3;
  }
};

struct Crictal : Modifier{
  Crictal(){
    name = sf::String("Crictal");
    int critMultMult = 2;
    int critMultAdd = 1;
  }
};

#endif
