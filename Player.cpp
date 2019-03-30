#include "Player.h"
#include "Bear.h"
#include "RollDice.h"
#include "Spell.h"
#include <algorithm>//for std::max and std::min
#include <iostream>//for std::cerr


Player::Player(){
  body.hitDieSize = 6;
  body.baseHealth = 50;

  maxHealth = body.UpdateHealth(body.baseHealth,
                                level,
                                GetAbil(int(Abil::CON)),
                                numVirginities);

  health = maxHealth;
}

void Player::SetMessageBox(MessageBox& theMessages){Messages = &theMessages;}

int Player::GetHealth(){
  health = std::min(health, GetMaxHealth());

  return health;
}

int Player::GetMaxHealth(){
  maxHealth = body.UpdateHealth(maxHealth,
                                level,
                                GetAbil(int(Abil::CON)),
                                numVirginities);

  return maxHealth;
}

int Player::GetNumDranks(){return numDranks;}

int Player::GetAbil(const int index, const bool isCheckingDeath) const {
  int abil = baseAbil.at(index) + abilBuff.at(index);
  if(index == int(Abil::STR)){
    abil += 6 * IsRaging() + 4 * IsWarCrying() + 10 * HasBigFist();
  }
  if(index == int(Abil::DEX)){
    abil += 4 * HasBigFist() + 6 * IsHasted() - 6 * IsSlowed();
    if(!isCheckingDeath && IsParalyzed()){
      abil = std::min(1, abil);
    }
  }
  if(index == int(Abil::CON)){
    abil += 6 * IsRaging() + 4 * IsWarCrying() + 10 * HasBigFist();
  }
  if(index == int(Abil::INT)){
    abil += -4 * IsRaging();
  }
  if(index == int(Abil::WIS)){

  }
  if(index == int(Abil::CHA)){
    abil += -4 * IsRaging();
  }
  return abil;
}

void Player::BuffAbil(const int index, const int buff){
  abilBuff.at(index) += buff;
}

int Player::AC(){return baseAC + armor + GetAbil(int(Abil::DEX)) - 10;}

void Player::Hurt(int dmg){health -= dmg;}

bool Player::IsDead(){
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

TurnOf Player::TakeAction(const Action theAction, Bear& theBear){
  if(IsSafe() &&
    (theAction == Action::leg ||
    theAction == Action::eye ||
    theAction == Action::john_hopkins))
  {
    Messages -> Update(sf::String("Don't be naughty"));
    return TurnOf::player;
  }
  if(theAction == Action::leg){
    return LegPunch(theBear);
  }
  else if(theAction == Action::eye){
    return EyePunch(theBear);
  }
  else if(theAction == Action::john_hopkins){
    Messages -> Update(sf::String("John Hopkins punching"),
                       sf::String("is unsupported."));//TEMP
    return TurnOf::player;//TEMP
  }
  else if(theAction == Action::quaff){
    return Quaff();
  }
  else if(theAction == Action::cast){
    Messages -> Update(sf::String("Whoops!"), sf::String("Spellcasting Error"));
    return TurnOf::player;
  }
  else if(theAction == Action::flee){
    return Flee(theBear);
  }
  else{
    return TurnOf::player;
  }
}

TurnOf Player::Cast(const int index, BattleHUD& environment){
  int spellTreeIndex = index / 3;
  int spellIndex = index % 3;
  SpellID spellToCast = spellList.at(spellTreeIndex).spellIDList.at(spellIndex);

  if(IsSafe() && Spell(spellToCast).IsOffensive()){
    Messages -> Update(sf::String("Don't be naughty"));
    return TurnOf::player;
  }
  else{
    spellList.at(spellTreeIndex).numSpells.at(spellIndex) --;
    return Spell(spellToCast).Cast(*this, environment);
  }
}

int Player::GetSpellSchoolBonus(const SpellSchool school){
  int bonus;
  if(school == SpellSchool::STR){
    bonus = GetAbil(int(Abil::STR)) + 2 * GetAbil(int(Abil::INT));
  }
  else if(school == SpellSchool::DEX){
    bonus = GetAbil(int(Abil::DEX)) + 2 * GetAbil(int(Abil::INT));
  }
  else if(school == SpellSchool::CON){
    bonus = GetAbil(int(Abil::CON)) + 2 * GetAbil(int(Abil::INT));
  }
  else if(school == SpellSchool::INT){
    bonus = 3 * GetAbil(int(Abil::INT));
  }
  else if(school == SpellSchool::WIS){
    bonus = ( 3 * GetAbil(int(Abil::WIS)) + 3 * GetAbil(int(Abil::INT)) )/2;
  }
  else if(school == SpellSchool::CHA){
    bonus = ( 3 * GetAbil(int(Abil::CHA)) + 3 * GetAbil(int(Abil::INT)) )/2;
  }
  else if (school == SpellSchool::WIS_CHA){
    bonus = GetAbil(int(Abil::INT)) + GetAbil(int(Abil::WIS))
            + GetAbil(int(Abil::CHA));
  }
  else{
    std::cerr << "Warning! ";
    std::cerr << "Use of SpellSchool unknown to Player::GetSpellSchoolBonus.\n";
    std::cerr << "The index of the invalid SpellSchool was ";
    std::cerr << int(school) << ".\n\n";
    bonus = 0;
  }
  return bonus;
}

sf::String Player::GetSpellName(const int index){
  if(index < 0 || index >= 3 * GetNumSpellTrees()){
    return sf::String("");
  }

  int spellTreeIndex = index / 3;
  int spellIndex = index % 3;
  SpellID spellID = spellList.at(spellTreeIndex).spellIDList.at(spellIndex);
  return Spell(spellID).GetName();
}

int Player::GetNumSpell(const int index){
  if(index < 0 || index >= 3 * GetNumSpellTrees()){
    return 0;
  }
  else{
    int spellTreeIndex = index / 3;
    int spellIndex = index % 3;
    return spellList.at(spellTreeIndex).numSpells.at(spellIndex);
  }
}

int Player::GetMaxNumSpell(const int index){
  if(index < 0 || index >= 3 * GetNumSpellTrees()){
    return 0;
  }
  else{
    int spellTreeIndex = index / 3;
    int spellIndex = index % 3;
    return spellList.at(spellTreeIndex).maxSpells.at(spellIndex);
  }
}

void Player::UnlockSpellTree(SpellTree tree){
  spellList.push_back(tree);
}

bool Player::TouchAttack(Bear bear){
  return (Roll(1,60) + TouchAttackBonus() >= bear.AC(Action::cast));
}

void Player::MakeSweetLove(){
  Messages -> Update("You have lost", "your virginity.", true);
  Messages -> Update("Bear is love.");
  numVirginities--;
}

void Player::TimerTick(){
  hastedTime = std::max(0, hastedTime - 1);
  ragingTime = std::max(0, ragingTime - 1);
  warCryingTime = std::max(0, warCryingTime - 1);
  bigFistTime = std::max(0, bigFistTime - 1);
  santuaryTime = std::max(0, santuaryTime -1);
}

void Player::SetAbil(std::array<int,int(Abil::NUM_ABIL)> newAbil){
  baseAbil = newAbil;
}

int Player::LegAttackBonus(){return GetAbil(int(Abil::STR)) - 10;}

int Player::LegDamageBonus(){return (GetAbil(int(Abil::STR)) - 10)/2;}

int Player::EyeAttackBonus(){
  return GetAbil(int(Abil::STR)) - 10 + GetAbil(int(Abil::DEX)) - 10;
}

int Player::EyeDamageBonus(){return 2*(GetAbil(int(Abil::STR)) - 10) + 5;}

int Player::TouchAttackBonus(){
  return 0;//FIXME
}


TurnOf Player::LegPunch(Bear& bear){
  int dmg = 0; //Keeps track of the damage of this attack
  int roll = Roll(1,60); //keeps track of roll for handling criticals

  if(roll + LegAttackBonus() >= bear.AC(Action::leg) || roll == 60){
    if(roll > 60 - legCritThreat){
      dmg = Roll(2,8) + 2 * LegDamageBonus();
      Messages -> Update("You CRIT bear for:", dmg, true);
    }
    else{
      dmg = Roll(1,8) + LegDamageBonus();
      Messages -> Update("You got bear for:", dmg, true);
    }
    bear.Hurt(std::max(1,dmg));
  }
  else{Messages -> Update("Carp, you miss.", true);}

  return TurnOf::bear;//Not the player's turn anymore
}

TurnOf Player::EyePunch(Bear& bear){
  int dmg = 0; //Keeps track of the damage of this attack
  int roll = Roll(1,60); //keeps track fo roll for handling criticals
  if(roll + EyeAttackBonus() >= bear.AC(Action::eye) || roll == 60){
    if(roll > 60 - eyeCritThreat){
      dmg = Roll(4,12) + 2 * EyeDamageBonus();
      Messages -> Update("You CRIT bear for:", std::max(1,dmg), true);
    }
    else{
      dmg = Roll(2,12) + EyeDamageBonus();
      Messages -> Update("You got bear for:", std::max(1,dmg), true);
    }
    bear.Hurt(std::max(1,dmg));
  }
  else{Messages -> Update("Carp, you miss.", true);}

  return TurnOf::bear;//Not the player's turn anymore
}

TurnOf Player::Quaff(){
  if(numDranks < 1){
    Messages -> Update("You're drank pauper.");
    return TurnOf::player;
  }
  else if(health >= maxHealth){
    Messages -> Update("You aren't thirst.");
    return TurnOf::player;
  }
  else{
    Messages -> Update("Down the hatch", true);
    health = std::min(maxHealth, health + 15);//No soft max yet
    numDranks--;
    return TurnOf::bear;
  }
}

TurnOf Player::Flee(Bear& bear){
  if(IsHasted() ||
    (Roll(1,60) + GetAbil(int(Abil::DEX)) >= 30 + bear.GetAbil(int(Abil::DEX))))
  {//FIXME: The odds of successfully fleeing need to be fine-tuned
    Messages -> Update("You escape bear", true);
    return TurnOf::neither;
  }
  Messages -> Update("Bear still behind you", true);
  return TurnOf::bear;
}
