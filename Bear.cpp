#include "Player.h"
#include "Bear.h"

void BearOutline::SetAbil(int STR, int DEX, int CON, int INT, int WIS, int CHA){
  abil[0] = STR;
  abil[1] = DEX;
  abil[2] = CON;
  abil[3] = INT;
  abil[4] = WIS;
  abil[5] = CHA;
}

Bear::Bear(BearOutline theBearOutline){
  name = theBearOutline.name;
  for(int i = 0; i < 6; i++){
    abil[i] = theBearOutline.abil[i];
  }
  maxHealth = theBearOutline.maxHealth;
  health = maxHealth;
  baseAttackBonus = theBearOutline.baseAttackBonus;
  baseAC = theBearOutline.baseAC;
  armor = theBearOutline.armor;
}

/*
void Bear::SetMaxHealth(int newMaxHealth){maxHealth = newMaxHealth;}

void Bear::SetBaseAttackBonus(int newBaseAttackBonus){
  baseAttackBonus = newBaseAttackBonus;
}

void Bear::SetBaseAC(int newBaseAC){baseAC = newBaseAC;}

void Bear::SetArmor(int newArmor){armor = newArmor;}

void Bear::SetName(sf::String newName){name = newName;}
*/

void Bear::SetMessageBox(MessageBox& theMessages){Messages = &theMessages;}

int Bear::AttackBonus(){return (abil[0] - 10)/2;}

int Bear::DamageBonus(){return (abil[0] - 10)/2;}

int Bear::AC(){return baseAC + armor + (abil[1] - 10)/2;}

sf::String Bear::GetName(){return name;}

int Bear::GetHealth(){return health;}

void Bear::Hurt(int dmg){health -= dmg;}

void Bear::Bash(Player& thePlayer){
  int dmg = 0; //Keeps track of the damage of this attack
  if(rand() % 20 + AttackBonus() >= thePlayer.AC()){
    dmg = rand() % 12 + 1 + DamageBonus();
    Messages -> Update("Bear bash you for:", dmg);
    thePlayer.Hurt(dmg);
  }
  else{
    Messages -> Update("Bear Spare You");
  }
}

void Bear::ShowHealth(){
  Messages -> Update("Bear is health:", health);
}
