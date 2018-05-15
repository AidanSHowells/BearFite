#include "Player.h"
#include "Bear.h"
#include "RollDice.h"
#include <algorithm>//for std::max and std::min


void Player::SetMessageBox(MessageBox& theMessages){Messages = &theMessages;}

int Player::GetHealth(){return health;}

int Player::GetMaxHealth(){return maxHealth;}

int Player::GetNumDranks(){return numDranks;}

void Player::SetAbil(std::array<int,int(Abil::NUM_ABIL)> newAbil){
  abil = newAbil;
}

int Player::HealthBonus(){return (abil[int(Abil::CON)] - 10) * 2;}

int Player::LegAttackBonus(){return abil[int(Abil::STR)] - 10;}

int Player::LegDamageBonus(){return (abil[int(Abil::STR)] - 10)/2;}

int Player::EyeAttackBonus(){
  return abil[int(Abil::STR)] - 10 + abil[int(Abil::DEX)] - 10;
}

int Player::EyeDamageBonus(){return 2*(abil[int(Abil::STR)] - 10) + 5;}

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
