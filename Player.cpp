#include "Player.h"
#include "Bear.h"

void Player::SetMessageBox(MessageBox& theMessages){Messages = &theMessages;}

int Player::LegAttackBonus(){return (abil[0] - 10)/2;}

int Player::LegDamageBonus(){return (abil[0] - 10)/2;}

int Player::AC(){return BaseAC + Armor + (abil[1] - 10)/2;}

void Player::Hurt(int dmg){health -= dmg;}

void Player::TakeAction(Action theAction, Bear& theBear){
  if(theAction == Action::leg){
    LegPunch(theBear);
  }
  else if(theAction == Action::eye){
    //EyePunch(theBear);
    Messages -> Update("Eye punching", "is unsupported.");//TEMP
  }
  else if(theAction == Action::john_hopkins){
    Messages -> Update("John Hopkins punching", "is unsupported.");//TEMP
  }
  else if(theAction == Action::quaff){
    //Quaff();
    Messages -> Update("Dranking", "is unsupported.");//TEMP
  }
  else if(theAction == Action::cast){
    Messages -> Update("Spellcasting", "is unsupported.");//TEMP
    //I actually don't know how this is going to work at all.
  }
  else if(theAction == Action::flee){
    //Flee(theBear);
    Messages -> Update("Fleeing", "is unsupported.");//TEMP
  }
}

void Player::LegPunch(Bear& bear){
  int dmg = 0; //Keeps track of the damage of this attack
  if(rand() % 20 + LegAttackBonus() >= bear.AC()){
    dmg = rand() % 8 + 1 + LegDamageBonus();
    Messages -> Update("You got bear for:", dmg);
    bear.Hurt(dmg);
  }
  else{Messages -> Update("Carp, you miss.");}
}
