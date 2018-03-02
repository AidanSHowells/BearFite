#ifndef PLAYER_H
#define PLAYER_H

#include "HUD.h"

class Bear;


class Player{
  public:
    Player(MessageBox& theMessages);
    int AC(); //Combines all AC-affecting factors
    void Hurt(int); //How the bear injures the player
    void TakeAction(Action theAction, Bear& theBear);//See below for syntax
  private:
    MessageBox* Messages; //So damage statements know where to print
    int abil[6] = {10, 10, 10, 10, 10 , 10}; //STR, DEX, CON, INT, WIS, CHR
    int maxHealth = 40;
    int health = maxHealth;
    int BaseAttackBonus = 0; //This will be level-based
    int BaseAC = 10; //This will be level-based
    int Armor = 0; //This will be determined by equipped items and magic
    int LegAttackBonus(); //Calculates attack bonus with abilities etc.
    int LegDamageBonus(); // Same for damage
    void LegPunch(Bear& bear);
};

/*Syntax for TakeAction:
if(event.type == sf::Event::MouseButtonPressed ||
   event.type == sf::Event::KeyPressed)
{
  player.TakeAction(optionsBox.GetAction(event), bear);
}
*/

#endif
