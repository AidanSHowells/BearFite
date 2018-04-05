#include "Player.h"
#include "Bear.h"
#include "RollDice.h"
#include "HUD.h"
#include <algorithm>//for std::max and std::min

void Bear::SetMessageBox(MessageBox& theMessages){
  Messages = &theMessages;
}

int Bear::HitDice(){return Roll(level, hitDieSize);}

int Bear::HealthBonus(){return (abil[2] - 10) * 2;}

int Bear::AttackBonus(){return abil[0] - 10 + 2*(abil[1] - 10);}

int Bear::DamageBonus(){return (abil[0] - 10)/2;}

int Bear::AC(Action attackType){
  if(attackType == Action::leg){
    return baseAC + armor + abil[1] - 10;
  }
  if(attackType == Action::eye){
    return baseAC + armor + abil[1] - 10 + eyeACBonus;
  }
}

sf::String Bear::GetName(){return name;}

sf::String Bear::GetModifier(){return modifier;}

int Bear::GetHealth(){return health;}

void Bear::Hurt(int dmg){health -= dmg;}

void Bear::Bash(Player& thePlayer){
  int dmg = 0; //Keeps track of the damage of this attack

  if(Roll(1,60) + AttackBonus() >= thePlayer.AC()){
    dmg = std::max(1, Roll(1,8) + DamageBonus());
    Messages -> Update("Bear bash you for:", dmg);
    thePlayer.Hurt(dmg);
  }
  else{
    Messages -> Update("Bear Spare You");
  }
}

void Bear::SetAbil(int STR, int DEX, int CON, int INT, int WIS, int CHR){
  abil[0] = STR;
  abil[1] = DEX;
  abil[2] = CON;
  abil[3] = INT;
  abil[4] = WIS;
  abil[5] = CHR;
}
