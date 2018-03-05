#include "Player.h"
#include "Bear.h"


void Bear::SetMessageBox(MessageBox& theMessages){Messages = &theMessages;}

int Bear::AttackBonus(){return (abil[0] - 10)/2;}

int Bear::DamageBonus(){return (abil[0] - 10)/2;}

int Bear::AC(){return BaseAC + Armor + (abil[1] - 10)/2;}

sf::String Bear::GetName(){return sf::String("Kleptobear");}

int Bear::GetHealth(){return health;}

void Bear::Hurt(int dmg){health -= dmg;}

void Bear::ShowHealth(){
  Messages -> Update("Bear is health:", health);
}
