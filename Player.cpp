#include "HUD.h"
#include <string>//For std::to_string
#include "Player.h"
#include "Bear.h"

Player::Player(MessageBox& theMessages){Messages = &theMessages;}
int Player::LegAttackBonus(){return (abil[0] - 10)/2;}
int Player::LegDamageBonus(){return (abil[0] - 10)/2;}
int Player::AC(){return BaseAC + Armor + (abil[1] - 10)/2;}
void Player::Hurt(int dmg){health -= dmg;}
void Player::LegPunch(Bear &bear){
  int dmg = 0; //Keeps track of the damage of this attack
  if(rand() % 20 + LegAttackBonus() >= bear.AC()){
    dmg = rand() % 8 + 1 + LegDamageBonus();
    Messages -> Update(std::to_string(dmg));
    Messages -> Update("You got bear for:");
    bear.Hurt(dmg);
  }
  else{Messages -> Update("Carp, you miss.");}
}
