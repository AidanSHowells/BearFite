#include "Player.h"
#include "Bear.h"
#include "RollDice.h"
#include "Spell.h"
#include <algorithm>//for std::max and std::min
#include <iostream>//for std::cerr


void Player::SetMessageBox(MessageBox& theMessages){Messages = &theMessages;}

int Player::GetHealth(){return health;}

int Player::GetMaxHealth(){return maxHealth;}

int Player::GetNumDranks(){return numDranks;}

void Player::SetAbil(std::array<int,int(Abil::NUM_ABIL)> newAbil){
  abil = newAbil;
}

int Player::AC(){return baseAC + armor + abil[int(Abil::DEX)] - 10;}

void Player::Hurt(int dmg){health -= dmg;}

TurnOf Player::TakeAction(Action theAction, Bear& theBear){
  if(theAction == Action::leg){
    return LegPunch(theBear);
  }
  else if(theAction == Action::eye){
    return EyePunch(theBear);
    //return EyePunch(theBear);
    //Messages -> Update(sf::String("Eye punching"),
    //                   sf::String("is unsupported."));//TEMP
    //return TurnOf::player;//TEMP
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
    //return Flee(theBear);
    Messages -> Update(sf::String("Fleeing"),
                       sf::String("is unsupported."));//TEMP
    return TurnOf::player;//TEMP
  }
  else{
    return TurnOf::player;
  }
}

int Player::GetSpellSchoolBonus(const SpellSchool school){
  int bonus;
  if(school == SpellSchool::STR){
    bonus = abil.at(int(Abil::STR)) + 2 * abil.at(int(Abil::INT));
  }
  else if(school == SpellSchool::DEX){
    bonus = abil.at(int(Abil::DEX)) + 2 * abil.at(int(Abil::INT));
  }
  else if(school == SpellSchool::CON){
    bonus = abil.at(int(Abil::CON)) + 2 * abil.at(int(Abil::INT));
  }
  else if(school == SpellSchool::INT){
    bonus = 3 * abil.at(int(Abil::INT));
  }
  else if(school == SpellSchool::WIS){
    bonus = ( 3 * abil.at(int(Abil::WIS)) + 3 * abil.at(int(Abil::INT)) )/2;
  }
  else if(school == SpellSchool::CHA){
    bonus = ( 3 * abil.at(int(Abil::CHA)) + 3 * abil.at(int(Abil::INT)) )/2;
  }
  else if (school == SpellSchool::WIS_CHA){
    bonus = abil.at(int(Abil::INT)) + abil.at(int(Abil::WIS))
            + abil.at(int(Abil::CHA));
  }
  else{
    std::cerr << "Warning! Use of SpellSchool unknown to ";
    std::cerr << "Player::GetSpellcastingLevel.\n";
    std::cerr << "The index of the invalid SpellSchool was ";
    std::cerr << int(school) << ".\n\n";
  }
  return bonus;
}

sf::String Player::GetSpellName(const int index){
  if(index < 0 || index >= 3 * GetNumSpellTrees()){
    return sf::String("");
  }
  else if(index == 0){
    return sf::String(" Pain:");
  }
  else if(index == 1){
    return sf::String(" Death:");
  }
  else if(index == 2){
    return sf::String(" Pleasure:");
  }
  else if(index == 3){
    return sf::String(" STR Up:");
  }
  else if(index == 4){
    return sf::String(" STR Jump:");
  }
  else if(index == 5){
    return sf::String(" STR Boost:");
  }
  else if(index == 6){
    return sf::String(" Fish:");
  }
  else if(index == 7){
    return sf::String(" Big Fish:");
  }
  else if(index == 8){
    return sf::String(" Invuln:");
  }
  else if(index == 9){
    return sf::String(" Fireball:");
  }
  else if(index == 10){
    return sf::String(" Iceball:");
  }
  else if(index == 11){
    return sf::String(" Lightning:");
  }
  else if(index == 12){
    return sf::String(" STR Down:");
  }
  else if(index == 13){
    return sf::String(" STR Drain:");
  }
  else if(index == 14){
    return sf::String(" Weakness:");
  }
  else if(index == 15){
    return sf::String(" Reversal:");
  }
  else if(index == 16){
    return sf::String(" HP Drain:");
  }
  else if(index == 17){
    return sf::String(" Vampirism:");
  }
  else if(index == 18){
    return sf::String(" Detect:");
  }
  else if(index == 19){
    return sf::String(" Dispel:");
  }
  else if(index == 20){
    return sf::String(" Cleanse:");
  }
}

int Player::GetNumSpell(const int index){
  if(index < 0 || index >= 3 * GetNumSpellTrees()){
    return 0;
  }
  else{
    return 5;
  }
}

int Player::GetMaxNumSpell(const int index){
  if(index < 0 || index >= 3 * GetNumSpellTrees()){
    return 0;
  }
  else{
    return 5;
  }
}

bool Player::TouchAttack(Bear bear){
  return (Roll(1,60) + TouchAttackBonus() >= bear.AC(Action::cast));
}

void Player::MakeSweetLove(){
  Messages -> Update("You have lost", "your virginity.", true);
  Messages -> Update("Bear is love.");
  numVirginities--;
}

int Player::HealthBonus(){return (abil[int(Abil::CON)] - 10) * 2;}

int Player::LegAttackBonus(){return abil[int(Abil::STR)] - 10;}

int Player::LegDamageBonus(){return (abil[int(Abil::STR)] - 10)/2;}

int Player::EyeAttackBonus(){
  return abil[int(Abil::STR)] - 10 + abil[int(Abil::DEX)] - 10;
}

int Player::EyeDamageBonus(){return 2*(abil[int(Abil::STR)] - 10) + 5;}

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
