#ifndef PLAYER_H
#define PLAYER_H

#include "HUD.h"

class Bear;


class Player{
  public:
    void SetMessageBox(MessageBox& theMessages);
    int GetHealth();
    int GetMaxHealth();
    int GetNumDranks();
    //void Quaff();
    int AC(); //Combines all AC-affecting factors
    void Hurt(int); //How the bear injures the player
    TurnOf TakeAction(Action theAction, Bear& theBear);//See below for syntax
  private:
    MessageBox* Messages; //So damage statements know where to print
    int abil[6] = {10, 10, 10, 10, 10 , 10}; //STR, DEX, CON, INT, WIS, CHR
    int maxHealth = 40;
    int health = maxHealth;
    int numDranks = 5;
    int baseAttackBonus = 0; //This will be level-based
    int baseAC = 30; //This will be level-based
    int armor = 0; //This will be determined by equipped items and magic
    int LegAttackBonus(); //Calculates attack bonus with abilities etc.
    int LegDamageBonus(); // Same for damage
    TurnOf LegPunch(Bear& bear);
    TurnOf Quaff();
};

/*Syntax for TakeAction:
if(event.type == sf::Event::MouseButtonPressed ||
   event.type == sf::Event::KeyPressed)
{
  turn = player.TakeAction(optionsBox.GetAction(event), bear);
}
//Returns TurnOf::player if it's still the player's turn, TurnOf::bear otherwise
*/

#endif
