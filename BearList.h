#ifndef BEARLIST_H
#define BEARLIST_H

#include "Bear.h"

BearOutline bearOutline;

//Babby Bear
bearOutline.SetAbil(10,10,10,10,10,10);
bearOutline.name = sf::String("Babby ");
bearOutline.maxHealth = 20;
bearOutline.baseAttackBonus = 0;
bearOutline.baseAC = 10;
bearOutline.armor = 0;
const Bear babbyBear(bearOutline);


//Black Bear
bearOutline.SetAbil(10,10,10,10,10,10);
bearOutline.name = sf::String("Black ");
bearOutline.maxHealth = 40;
bearOutline.baseAttackBonus = 5;
bearOutline.baseAC = 10;
bearOutline.armor = 0;
const Bear blackBear(bearOutline);

//Brown Bear
bearOutline.SetAbil(10,10,10,10,10,10);
bearOutline.name = sf::String("Brown ");
bearOutline.maxHealth = 50;
bearOutline.baseAttackBonus = 0;
bearOutline.baseAC = 10;
bearOutline.armor = 0;
const Bear brownBear(bearOutline);



#endif
