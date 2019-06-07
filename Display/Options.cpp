#include <iostream>//For std::cerr
#include "Options.h"
#include "Color.h"

OptionsBox::OptionsBox(
  sf::Font& titleFont,
  sf::Font& mainFont,
  const std::array <sf::String, 8>& optionString, //Defaults to the battle text
  bool boxHasTwoTitles                            //Defaults to true
):
  hasTwoTitles(boxHasTwoTitles),
  sizeOfFirstList(4),
  sizeOfSecondList(4),
  numOptions(sizeOfFirstList + sizeOfSecondList),
  numHighlightBoxes(numOptions - 1 - int(boxHasTwoTitles)) //Minus one per title
{
  if(sizeOfFirstList + sizeOfSecondList > maxNumOptions){
    std::cerr << "Too many options. They're not all going to fit.\n\n";
  }

  //Make the background rectangle
  background.setSize(size);
  background.setFillColor(Color::HUDBackground);
  background.setPosition(position.x, position.y);

  //Make the divider line
  divLine.setSize(sf::Vector2f(2, size.y));
  divLine.setFillColor(sf::Color::Black);
  divLine.setPosition(divPosition, position.y);

  //Make the options
  for(int i = 0; i < numOptions; i++){
    optionsText[i].setCharacterSize(25);
    optionsText[i].setFillColor(Color::DefaultText);
    optionsText[i].setString(optionString.at(i));

    //Headings get titleFont, everything else gets mainFont
    if(0 == i || (sizeOfFirstList == i && hasTwoTitles)){
      optionsText[i].setFont(titleFont);
    }
    else{
      optionsText[i].setFont(mainFont);
    }

    //Positioning depends on which list you're in
    float xPos;
    float yPos;
    if(i < sizeOfFirstList){
      xPos = position.x;
      yPos = position.y + float(30 * i);
    }
    else{
      xPos = divPosition + 10;
      yPos = position.y + float(30*(i - sizeOfFirstList + int(!hasTwoTitles)));
    }
    optionsText[i].setPosition(xPos, yPos);
  }

  //Make the first set of hightlight boxes
  for(int i = 0; i < sizeOfFirstList - 1; i++){
    highlightBox[i].AdjustToFit(optionsText[i + 1].getGlobalBounds());
  }

  //Make the second set of hightlight boxes
  for(int i = sizeOfFirstList - 1; i < numHighlightBoxes; i++){
    int index = i + 1 + int(hasTwoTitles);
    highlightBox[i].AdjustToFit(optionsText[index].getGlobalBounds());
  }
}

int OptionsBox::GetChoice(const sf::Event theEvent){
  int playerChoice = 0;//Zero if they didn't choose anything

  if(theEvent.type == sf::Event::KeyPressed){
    for(int i = 0; i < numHighlightBoxes; i++){
      if(theEvent.key.code == (i + sf::Keyboard::Num1) ||
         theEvent.key.code == (i + sf::Keyboard::Numpad1))
      {
        playerChoice = i + 1;
      }
    }
  }

  else if(theEvent.type == sf::Event::MouseButtonPressed){
    sf::Vector2f clickLocation(float(theEvent.mouseButton.x),
                               float(theEvent.mouseButton.y) );
    for(int i = 0; i < numHighlightBoxes; i++){
      if(highlightBox[i].Contains(clickLocation)){
        playerChoice = i + 1;
      }
    }
  }

  return playerChoice;
}

void OptionsBox::Update(const sf::Vector2f mousePosition, const bool highlight){
  if(highlight){
    for(int i = 0; i < numHighlightBoxes; i++){
      highlightBox[i].UpdateState(mousePosition);
    }
  }
  else{
    for(int i = 0; i < numHighlightBoxes; i++){
      highlightBox[i].UpdateState(false);
    }
  }
}

void OptionsBox::draw(sf::RenderTarget& target, sf::RenderStates states) const{
  target.draw(background, states);
  if(hasTwoTitles){
    target.draw(divLine, states);
  }
  for(int  i = 0; i < numOptions; i++){
    target.draw(optionsText[i], states);
  }
  for(int i = 0; i < numHighlightBoxes; i++){
    target.draw(highlightBox[i], states);
  }
}
