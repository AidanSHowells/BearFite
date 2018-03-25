#include "Player.h"
#include "Bear.h"
#include "RollDice.h"

void Player::SetMessageBox(MessageBox& theMessages){Messages = &theMessages;}

int Player::GetHealth(){return health;}

int Player::GetMaxHealth(){return maxHealth;}

int Player::GetNumDranks(){return numDranks;}

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
    Messages -> Update("Eye punching", "is unsupported.");//TEMP
    return TurnOf::player;//TEMP
  }
  else if(theAction == Action::john_hopkins){
    Messages -> Update("John Hopkins punching", "is unsupported.");//TEMP
    return TurnOf::player;//TEMP
  }
  else if(theAction == Action::quaff){
    return Quaff();
  }
  else if(theAction == Action::cast){
    Messages -> Update("Whoops!", "Spellcasting Error");
    return TurnOf::player;
  }
  else if(theAction == Action::flee){
    //return Flee(theBear);
    Messages -> Update("Fleeing", "is unsupported.");//TEMP
    return TurnOf::player;//TEMP
  }
  else{
    return TurnOf::player;
  }
}

TurnOf Player::LegPunch(Bear& bear){
  int dmg = 0; //Keeps track of the damage of this attack
  if(RollDice(1,60) + LegAttackBonus() >= bear.AC()){
    dmg = RollDice(1,8) + 1 + LegDamageBonus();
    Messages -> Update("You got bear for:", dmg);
    bear.Hurt(dmg);
  }
  else{Messages -> Update("Carp, you miss.");}

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
    Messages -> Update("Down the hatch");
    health = std::min(maxHealth, health + 15);//No soft max yet
    numDranks--;
    return TurnOf::bear;
  }
}
