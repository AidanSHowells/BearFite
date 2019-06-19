#include <string>//For std::to_string
#include "Messages.h"
#include "Color.h"
#include "AddSpace.h"

MessageBox::MessageBox(
  sf::Font& titleFont,
  sf::Font& mainFont,
  sf::String theTitle,
  sf::Vector2f thePosition, //Default is sf::Vector2f(0, 0)
  sf::Vector2f theSize      //Default is sf::Vector2f(200, 460)
):
  position(thePosition),
  size(theSize)
{
  //Make the background rectangle
  background.setSize(size);
  background.setFillColor(Color::HUDBackground);

  //Make the title
  line[0].setFont(titleFont);
  line[0].setString(theTitle);
  line[0].setCharacterSize(20);//in pixels, not points
  line[0].setFillColor(Color::DefaultText);
  line[0].setPosition(position.x,position.y);

  //Initialize the rest of the lines
  for(int i = 1; i < numLines; i++){
    line[i].setFont(mainFont);
    line[i].setString("");
    line[i].setCharacterSize(15);
    line[i].setFillColor(Color::DefaultText);
    line[i].setPosition(position.x, position.y + float(20 * i));
  }
  for(int i = 0; i < numDivLines; i++){
    divLine[i].setSize(sf::Vector2f(size.x, 1));
    divLine[i].setFillColor(sf::Color::Black);
    divLine[i].setPosition(position.x, position.y + float(40 + 20 * i));
    displayDivLine[i] = false;
  }
}

void MessageBox::Clear(){
  for(int i = 1; i < numLines; i++){
    line[i].setString("");
  }
  for(int i = 0; i < numDivLines; i++){
    displayDivLine[i] = false;
  }
}

void MessageBox::Update(const sf::String& inputString, bool makeLine){
  //Note: makeLine defaults to false
  SetTopString(markChar + inputString, makeLine);
}

void MessageBox::Update(const sf::String& inputString1,
                        const sf::String& inputString2,
                        bool makeLine,
                        const Style style)
{
  //Note: makeLine defaults to false
  if(style == Style::alignLastLineRight){
    SetTopString(AddSpacing(inputString2, 22), makeLine);
  }
  else{
    SetTopString(sf::String(" ") + inputString2, makeLine);
  }
  Update(inputString1);
}

void MessageBox::Update(const sf::String& inputString1,
                        const sf::String& inputString2,
                        const sf::String& inputString3)
{
  SetTopString(sf::String(" ") + inputString3);
  Update(inputString1, inputString2);
}

void MessageBox::Update(const sf::String& inputString1,
                        const sf::String& inputString2,
                        const sf::String& inputString3,
                        const sf::String& inputString4)
{
  SetTopString(sf::String(" ") + inputString4);
  Update(inputString1, inputString2, inputString3);
}

void MessageBox::Update(const sf::String& inputString1,
                        const sf::String& inputString2,
                        const sf::String& inputString3,
                        const sf::String& inputString4,
                        const sf::String& inputString5)
{
  SetTopString(sf::String(" ") + inputString5);
  Update(inputString1, inputString2, inputString3, inputString4);
}

void MessageBox::Update(const sf::String& inputString1,
                        const sf::String& inputString2,
                        const sf::String& inputString3,
                        const sf::String& inputString4,
                        const sf::String& inputString5,
                        const sf::String& inputString6)
{
  SetTopString(sf::String(" ") + inputString6);
  Update(inputString1, inputString2, inputString3, inputString4, inputString5);
}

void MessageBox::Update(const sf::String& inputString,
                        int inputInt,
                        bool makeLine)
{
  //Note that makeLine defaults to false
  SetTopString( AddSpacing(std::to_string(inputInt), 22) , makeLine);
  Update(inputString);
}


void MessageBox::draw(sf::RenderTarget& target, sf::RenderStates states) const{
  target.draw(background, states);
  for(int i = 0; i < numLines; i++){
    target.draw(line[i], states);
  }
  for(int i = 0; i < numDivLines; i++){
    if(displayDivLine[i]){
      target.draw(divLine[i], states);
    }
  }
}

void MessageBox::SetTopString(const sf::String& inputString, bool makeLine){
  if("" != line[numLines - 1].getString()){
    int lastMarkCharIndex = 1;
    for(int i = 1; i < numLines; i++){
      if(markChar == line[i].getString().substring(0,1) ){
        lastMarkCharIndex = i;
      }
    }
    for(int i = numLines - 1; i >= lastMarkCharIndex; i--){
      line[i].setString("");
    }
  }

  //Move everything down one
  for(int i = numLines - 1; i > 1; i--){
    line[i].setString(line[i-1].getString());
  }
  for(int i = numDivLines - 1; i > 0; i--){
    displayDivLine[i] = displayDivLine[i-1];
  }
  //Make the top line inputString
  line[1].setString(inputString);
  displayDivLine[0] = makeLine;//Note that makeLine defaults to false
}
