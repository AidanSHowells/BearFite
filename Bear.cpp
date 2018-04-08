#include "Player.h"
#include "Bear.h"
#include "RollDice.h"
#include "HUD.h"
#include <algorithm>//for std::max and std::min

void Bear::SetMessageBox(MessageBox& theMessages){
  Messages = &theMessages;
}

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


void Bear::SetHealth(){
  health = body.UpdateHealth(body.baseHealth, level, abil[2]);
}


int Bear::GetHealth(){
  health = body.UpdateHealth(health, level, abil[2]);

  return health;
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

void Bear::SetAbil(int STR, int DEX, int CON, int INT, int WIS, int CHR){
  abil[0] = STR;
  abil[1] = DEX;
  abil[2] = CON;
  abil[3] = INT;
  abil[4] = WIS;
  abil[5] = CHR;
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
