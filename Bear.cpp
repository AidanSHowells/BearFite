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

int Bear::GetAttackBonus() const {
  return GetAbil(int(Abil::STR)) - 10 + 2*(GetAbil(int(Abil::DEX)) - 10);
}

int Bear::GetDamageBonus() const {
  return (GetAbil(int(Abil::STR)) - 10)/2;
}

int Bear::GetAC(const Action attackType) const {
  if(attackType == Action::leg){
    return baseAC + armor + GetAbil(int(Abil::DEX)) - 10;
  }
  else if(attackType == Action::eye){
    return baseAC + armor + GetAbil(int(Abil::DEX)) - 10 + eyeACBonus;
  }
  else if(attackType == Action::cast){//Ranged touch attack
    return baseAC + GetAbil(int(Abil::DEX)) - 10;
  }
  else{
    std::cerr << "Warning! Use of invalid Action in Bear::GetAC.\n";
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
    save += 2 * GetAbil(int(Abil::DEX)) - 20;
  }
  else if(saveType == SaveType::fort){
    save += 2 * GetAbil(int(Abil::CON)) - 20;
  }
  else if(saveType == SaveType::will){
    save += 2 * GetAbil(int(Abil::INT)) - 20;
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

void Bear::FeedFish(int fishSize){
  int eatingSpeed = std::max(1, GetAbil(int(Abil::CON)) / 10);
  eatingTime += fishSize / eatingSpeed;
  eatingTime = std::max(1, eatingTime);
}

int Bear::GetAbil(const int index, const bool isCheckingDeath) const {
  int ab = abil.at(index);
  if(index == int(Abil::STR)){
    if(!isCheckingDeath){
      ab += -4 * IsCrying();
    }
  }
  if(index == int(Abil::DEX)){
    ab += 6 * IsHasted();
    if(!isCheckingDeath){
      ab += -6 * IsSlowed();
    }
  }
  if(index == int(Abil::CON)){

  }
  if(index == int(Abil::INT)){

  }
  if(index == int(Abil::WIS)){
    if(!isCheckingDeath){
      ab += -2 * IsCrying();
    }
  }
  if(index == int(Abil::CHA)){

  }
  return ab;
}

void Bear::TimerTick(){
  hastedTime = std::max(0, hastedTime - 1);
  slowedTime = std::max(0, slowedTime - 1);
  paralyzedTime = std::max(0, paralyzedTime - 1);
  cryingTime = std::max(0, cryingTime - 1);
  //Eating time is reduced in "TakeTurn" instead. This means that paralyzed
  //bears don't eat, and slowed/hasted bears eat faster/slower, which I like
}

int Bear::DrainAbil(const int ability, int drain, const bool canKill){
  if(!canKill && abil.at(ability) - drain < 1){
    drain = std::max(0, abil.at(ability) - 1);
  }
  abil.at(ability) -= drain;

  return drain;
}

bool Bear::IsDead(){
  if(GetHealth() <= 0){
    return true;
  }
  for(int i = 0; i < int(Abil::NUM_ABIL); i++){
    if(GetAbil(i, true) < 1){
      return true;
    }
  }
  return false;
}

std::array<Bear, 4> Bear::ApplyModifier(Modifier mod, bool isDerived){
  if(isDerived){
    modifier2 = mod;
  }
  else{
    modifier = mod;
  }
  for(int i = 0; i < int(Abil::NUM_ABIL); i++){
    abil.at(i) = std::max(abil.at(i) + mod.abilAdd[i], 1);//Don't kill the bear
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

void Bear::TakeTurn(Player& target){
  bool done = false;
  while(!done){
    if(!(IsParalyzed() || (IsSlowed() && Roll(1,2) == 1) )){
      if(IsEating()){
        eatingTime = std::max(0, eatingTime - 1);
        if(IsEating()){
          Messages -> Update(sf::String("Bear is munching"));
        }
        else{
          Messages -> Update(sf::String("BRUP! Fish over"));
        }
      }
      else if(target.IsSafe()){
        if(isAngry || (GetAbil(int(Abil::WIS)) < 10)){
          Messages -> Update(sf::String("GRRRAAAAAH!"),sf::String("BOING!"));
        }
        else{
          Messages -> Update(sf::String("Bear is watching..."));
        }
      }
      else{//Not eating and target isn't safe
        Bash(target);
      }
    }
    if(!IsHasted() || Roll(1,2) == 1){
      TimerTick();
      done = true;
    }
  }
}

void Bear::Bash(Player& thePlayer){
  int dmg = 0; //Keeps track of the damage of this attack
  int roll = Roll(1,60); //tracks bear attack roll for determining criticals

  if(roll + GetAttackBonus() >= thePlayer.GetAC() || roll == 60){
    if(roll > 60 - critThreat){
      dmg = Roll(critMult,8) + critMult * GetDamageBonus();
      Messages -> Update("Bear CRIT you for:", std::max(1,dmg));
    }
    else{
      dmg = Roll(1,8) + GetDamageBonus();
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
