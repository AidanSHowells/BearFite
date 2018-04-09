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

sf::String Bear::GetModifier(){return modifier.name;}


void Bear::SetHealth(){
  health = body.UpdateHealth(body.baseHealth, level, abil[2]);
}


int Bear::GetHealth(){
  health = body.UpdateHealth(health, level, abil[2]);

  return health;
}

std::array<Bear, 4> Bear::ApplyModifier(Modifier mod, bool isDerived){
  if(isDerived){
    modifier2 = mod;
  }
  else{
    modifier = mod;
  }
  for(int i = 0; i < 6; i++){
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
