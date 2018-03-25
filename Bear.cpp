#include "Player.h"
#include "Bear.h"


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
