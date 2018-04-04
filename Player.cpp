#include "Player.h"
#include "Bear.h"
#include "RollDice.h"
#include <algorithm>//for std::max and std::min


void Player::SetMessageBox(MessageBox& theMessages){Messages = &theMessages;}

int Player::GetHealth(){return health;}

int Player::GetMaxHealth(){return maxHealth;}

int Player::GetNumDranks(){return numDranks;}

int Player::HealthBonus(){return (abil[2] - 10) * 2;}

int Player::LegAttackBonus(){return abil[0] - 10;}

int Player::LegDamageBonus(){return (abil[0] - 10)/2;}

int Player::AC(){return baseAC + armor + abil[1] - 10;}

void Player::Hurt(int dmg){health -= dmg;}

TurnOf Player::TakeAction(Action theAction, Bear& theBear){
  if(theAction == Action::leg){
    return LegPunch(theBear);
  }
  else if(theAction == Action::eye){
    //return EyePunch(theBear);
    Messages -> Update(sf::String("Eye punching"),
                       sf::String("is unsupported."));//TEMP
    return TurnOf::player;//TEMP
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

TurnOf Player::LegPunch(Bear& bear){
  int dmg = 0; //Keeps track of the damage of this attack
  if(Roll(1,60) + LegAttackBonus() >= bear.AC()){
    dmg = Roll(1,8) + LegDamageBonus();
    Messages -> Update("You got bear for:", dmg, true);
    bear.Hurt(dmg);
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
