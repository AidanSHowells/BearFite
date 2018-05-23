#include "Player.h"
#include "Bear.h"
#include "RollDice.h"
#include "HUD.h"
#include "Spell.h"
#include <algorithm>//for std::max and std::min
#include <iostream>//for std::cerr

void Bear::SetMessageBox(MessageBox& theMessages){
  Messages = &theMessages;
}

int Bear::AttackBonus(){
  return abil[int(Abil::STR)] - 10 + 2*(abil[int(Abil::DEX)] - 10);
}

int Bear::DamageBonus(){return (abil[int(Abil::STR)] - 10)/2;}

int Bear::AC(Action attackType){
  if(attackType == Action::leg){
    return baseAC + armor + abil[int(Abil::DEX)] - 10;
  }
  else if(attackType == Action::eye){
    return baseAC + armor + abil[int(Abil::DEX)] - 10 + eyeACBonus;
  }
  else if(attackType == Action::cast){//Ranged touch attack
    return baseAC + abil[int(Abil::DEX)] - 10;
  }
  else{
    std::cerr << "Warning! Use of invalid Action in Bear::AC.\n";
    std::cerr << "The index of the invalid Action was ";
    std::cerr << int(attackType) << ".\n\n";
    return -1;
  }
}

sf::String Bear::GetName() const {return name;}

sf::String Bear::GetModifier(){return modifier.name;}


void Bear::SetHealth(){
  health = body.UpdateHealth(body.baseHealth, level, abil[int(Abil::CON)]);
}


int Bear::GetHealth(){
  health = body.UpdateHealth(health, level, abil[int(Abil::CON)]);

  return health;
}

int Bear::GetSave(const SaveType saveType){
  int save = Roll(1,60);
  if(saveType == SaveType::reflex){
    save += 2 * abil.at(int(Abil::DEX)) - 20;
  }
  else if(saveType == SaveType::fort){
    save += 2 * abil.at(int(Abil::CON)) - 20;
  }
  else if(saveType == SaveType::will){
    save += 2 * abil.at(int(Abil::INT)) - 20;
  }
  else if(saveType == SaveType::COUNT){
    std::cerr << "Warning! Invalid use of ";
    std::cerr << "SaveType::COUNT in function Bear::GetSave.\n\n";
  }
  else{
    std::cerr << "Warning! Use of SaveType unknown to Bear::GetSave.\n";
    std::cerr << "The index of the invalid SaveType was ";
    std::cerr << int(save) << ".\n\n";
  }
  return save;
}

void Bear::DrainAbil(int ability, int drain){
  abil.at(ability) -= drain;
}

std::array<Bear, 4> Bear::ApplyModifier(Modifier mod, bool isDerived){
  if(isDerived){
    modifier2 = mod;
  }
  else{
    modifier = mod;
  }
  for(int i = 0; i < int(Abil::NUM_ABIL); i++){
    abil[i] = std::max(abil[i] + mod.abilAdd[i], 1);//Don't kill the bear
  }
  level += mod.levelAdd;

  critThreat *= mod.critThreatMult;
  critThreat += mod.critThreatAdd;
  critMult *= mod.critMultMult;
  critMult += mod.critMultAdd;


  //NOTE: Twins and companians stuff should come last
  //Make an array whose first bear is this bear:
  std::array<Bear, 4> theBears = {*this};
  //Add any twins to the array:
  for(int i = 1; i <= mod.numTwins; i++){
    theBears.at(i) = theBears.at(0);
  }

  if(!isDerived && mod.derivedModifier != nullptr){
    return ApplyModifier(*(mod.derivedModifier), true);
  }
  return theBears;//Return that array
}

void Bear::Hurt(int dmg){health -= dmg;}

void Bear::Bash(Player& thePlayer){
  int dmg = 0; //Keeps track of the damage of this attack
  int roll = Roll(1,60); //tracks bear attack roll for determining criticals

  if(roll + AttackBonus() >= thePlayer.AC() || roll == 60){
    if(roll > 60 - critThreat){
      dmg = Roll(critMult,8) + critMult * DamageBonus();
      Messages -> Update("Bear CRIT you for:", std::max(1,dmg));
    }
    else{
      dmg = Roll(1,8) + DamageBonus();
      Messages -> Update("Bear bash you for:", std::max(1,dmg));
    }
    thePlayer.Hurt(std::max(1,dmg));
  }
  else{
    Messages -> Update("Bear Spare You");
  }
}

void Bear::SetAbil(int STR, int DEX, int CON, int INT, int WIS, int CHA){
  abil[int(Abil::STR)] = STR;
  abil[int(Abil::DEX)] = DEX;
  abil[int(Abil::CON)] = CON;
  abil[int(Abil::INT)] = INT;
  abil[int(Abil::WIS)] = WIS;
  abil[int(Abil::CHA)] = CHA;
}

int Body::UpdateHealth(int newHealth, int newLevel, int newCON){
  health = newHealth;

  if(level < newLevel){
    //Roll any missing hit dice
    for(int i = hitDice.size(); i < newLevel; i++){
      hitDice.push_back(Roll(1,hitDieSize));
    }
    for(int i = level; i < newLevel; i++){
      health += hitDice.at(i);
    }
  }
  if(level > newLevel){
    for(int i = newLevel; i < level; i++){
      health -= hitDice.at(i);
    }
  }
  health = health - HealthBonus(CON) + HealthBonus(newCON);

  level = newLevel;
  CON = newCON;
  return health;
}
