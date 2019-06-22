#include "FindBear.h"
#include "Modifier.h"
#include "RollDice.h"

std::array<Bear,4> FindBear(const Player& player){
  std::vector<BearID> potentialBears;
  int difficulty = player.GetBodyCount();
  for(int i = 0; i < int(BearID::NUM_BEARS); i++){
    if(Bear(BearID(i)).GetDifficulty() <= difficulty){
      potentialBears.push_back(BearID(i));
    }
  }

  Bear foundbear(potentialBears.at( Roll(1, potentialBears.size()) - 1 ));
  difficulty -= foundbear.GetDifficulty();

  ModifierID modifier;

  if(difficulty < 10){
    modifier = ModifierID::none;
  }
  else if(difficulty < 20 && Roll(1,2) == 1){
    modifier = ModifierID::none;
  }
  else if(Roll(1,5) == 1){
    modifier = ModifierID::none;
  }
  else{
    std::vector<ModifierID> candidates;
    for(int i = 0; i < int(ModifierID::NUM_MODIFIERS); i++){
      candidates.push_back(ModifierID(i));
    }
    modifier = candidates.at(Roll(1,int(ModifierID::NUM_MODIFIERS))-1);
  }

  return foundbear.ApplyModifier(modifier);
}
