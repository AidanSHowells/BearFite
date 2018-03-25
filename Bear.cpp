#include "Player.h"
#include "Bear.h"


void Bear::SetMessageBox(MessageBox& theMessages){Messages = &theMessages;}

int Bear::AttackBonus(){return abil[0] - 10 + (abil[1] - 10)/2;}

int Bear::DamageBonus(){return (abil[0] - 10)/2;}

int Bear::AC(){return baseAC + armor + abil[1] - 10;}

sf::String Bear::GetName(){return name;}

int Bear::GetHealth(){return health;}

void Bear::Hurt(int dmg){health -= dmg;}

void Bear::Bash(Player& thePlayer){
  int dmg = 0; //Keeps track of the damage of this attack
  if(rand() % 60 + AttackBonus() >= thePlayer.AC()){
    dmg = rand() % 8 + 1 + DamageBonus();
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
