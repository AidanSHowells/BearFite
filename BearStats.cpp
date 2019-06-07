#include <string>//For std::to_string
#include "BearStats.h"
#include "Display/Color.h"
#include "Display/AddSpace.h"

BearStats::BearStats(
  sf::Font& titleFont,
  sf::Font& mainFont,
  Bear theBear,
  bool titleBar,            //Default is true
  sf::Vector2f thePosition, //Default is sf::Vector2f(205, 0)
  sf::Vector2f theSize      //Default is sf::Vector2f(390, 23)
):
bear(theBear),
position(thePosition),
size(theSize + sf::Vector2f(0, float(25 * int(titleBar)) ) ),
hasTitleBar(titleBar),
shouldAppear(theBear.CanBeFought())
{
  //Make the static text
  for(int i = 0; i < numBearInfo; i += 2){
    bearInfo[i].setFont(titleFont);
    bearInfo[i].setCharacterSize(20);
    bearInfo[i].setFillColor(Color::DefaultText);
  }
  bearInfo[0].setString("Species:");
  bearInfo[0].setPosition(position.x, position.y);
  bearInfo[2].setString("Health:");
  bearInfo[2].setPosition(position.x + 140, position.y);
  bearInfo[4].setString("Modifier:");
  bearInfo[4].setPosition(position.x + 232, position.y);

  //Make the dynamic text
  for(int i = 1; i < numBearInfo; i += 2){
    bearInfo[i].setFont(mainFont);
    bearInfo[i].setCharacterSize(20);
    bearInfo[i].setFillColor(Color::DefaultText);
    bearInfo[i].setPosition(bearInfo[i-1].getPosition().x,
                            position.y - float(3 - 23 * int(hasTitleBar)) );
  }
  //No need to set the dynamic strings here, because Update() handles them

  //Make the background rectangles
  background[0].setPosition(bearInfo[0].getPosition().x, position.y);
  background[1].setPosition(bearInfo[2].getPosition().x - 2, position.y);
  background[2].setPosition(bearInfo[4].getPosition().x - 2, position.y);

  float xPosition[3] = {
    background[1].getPosition().x - background[0].getPosition().x - 2,
    background[2].getPosition().x - background[1].getPosition().x - 2,
    size.x + position.x - background[2].getPosition().x
  };

  for(int i = 0; i < numBackground; i++){
    background[i].setFillColor(Color::HUDBackground);
    background[i].setSize(sf::Vector2f(xPosition[i],size.y));
  }
}

void BearStats::Update(){
  if(shouldAppear){
    bearInfo[1].setString(bear.GetName());
    bearInfo[3].setString( AddSpacing(std::to_string(bear.GetHealth()), 7) );
    bearInfo[5].setString(bear.GetModifier());
  }
}

void BearStats::SetBear(const Bear& theNewBear){
  bear = theNewBear;
  shouldAppear = true;
}

Bear* BearStats::GetBearPtr(){
  return &bear;
}

bool BearStats::GetShouldAppear() const{
  return shouldAppear;
}

void BearStats::SetShouldAppear(bool shouldBearAppear){
  shouldAppear = shouldBearAppear;
}

void BearStats::draw(sf::RenderTarget& target, sf::RenderStates states) const{
  if(shouldAppear){
    for(int i = 0; i < numBackground; i++){
      target.draw(background[i], states);
    }
    if(hasTitleBar){
      for(int i = 0; i < numBearInfo; i += 2){
        target.draw(bearInfo[i], states);
      }
    }
    for(int i = 1; i < numBearInfo; i += 2){
      target.draw(bearInfo[i], states);
    }
  }
}
