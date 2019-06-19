#include <iostream>//For std::cerr
#include "Options.h"
#include "Color.h"

OptionsBox::OptionsBox(
  sf::Font& titleFont,
  sf::Font& mainFont,
  const std::vector <sf::String>& optionString,
  int listBreakPoint,
  bool boxHasTwoTitles,                           //Defaults to true
  bool battleProportions                          //Defaults to false
):
  divPosition(310 + 40 * int(battleProportions)),
  boldFont(titleFont),
  regularFont(mainFont)
{
  //Make the background rectangle
  background.setSize(size);
  background.setFillColor(Color::HUDBackground);
  background.setPosition(position.x, position.y);

  //Make the divider line
  divLine.setSize(sf::Vector2f(2, size.y));
  divLine.setFillColor(sf::Color::Black);
  divLine.setPosition(divPosition, position.y);

  for(int i = 0; i < maxNumOptions; i++){
    optionsText[i].setCharacterSize(25);
    optionsText[i].setFillColor(Color::DefaultText);
  }

  NewChoices(optionString,listBreakPoint,boxHasTwoTitles);
}

void OptionsBox::NewChoices(const std::vector <sf::String>& optionString,
                            int listBreakPoint,
                            bool boxHasTwoTitles)
{
  hasTwoTitles = boxHasTwoTitles;
  numOptions = optionString.size();
  sizeOfFirstList = listBreakPoint;
  sizeOfSecondList = numOptions - sizeOfFirstList;
  numHighlightBoxes = numOptions - 1 - int(boxHasTwoTitles);//minus 1 per title

  if(numOptions > maxNumOptions){
    std::cerr << "Too many options. They're not all going to fit.\n\n";
  }

  //Make the options
  for(int i = 0; i < numOptions; i++){
    optionsText[i].setString(optionString.at(i));

    //Headings get bold, everything else doesn't
    if(0 == i || (sizeOfFirstList == i && hasTwoTitles)){
      optionsText[i].setFont(boldFont);
    }
    else{
      optionsText[i].setFont(regularFont);
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
