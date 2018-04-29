#include "HUD.h"
#include <string>//For std::to_string
#include <cassert>//For error handling
#include "Player.h"
#include "Bear.h"

/*Why force the person creating a HUD object to provide fonts? Two reasons.
 *First, constructors can't return values, so we can't tell the constructor to
 *return an error code if the font fails to load. This makes it harder to fail
 *gracefully. Second, it's not as simple as loading fonts in the constructor
 *and assigning them to the text. From the "sf::Font" documentation: "It is
 *important to note that the sf::Text instance doesn't copy the font that it
 *uses, it only keeps a reference to it. Thus, a sf::Font must not be destructed
 *while it is used by a sf::Text (i.e. never write a function that uses a local
 *sf::Font instance for creating a text)."
 */

//Color definitions. I use upper case to be consistant with SFML
sf::Color Gray = sf::Color(192,192,192);
sf::Color ClearYellow = sf::Color(255,255,0,153);

//Helper Functions:
sf::String AddSpacing(const sf::String& inputString, int totalLength){
  sf::String spacing = "";
  for(int i = 0; i < totalLength - inputString.getSize(); i++){
    spacing += sf::String(" ");
  }
  return(spacing + inputString);
}


MessageBox::MessageBox(
  sf::RenderWindow& theWindow,
  sf::Font& titleFont,
  sf::Font& mainFont,
  sf::String theTitle,
  sf::Vector2f thePosition, //Default is sf::Vector2f(0, 0)
  sf::Vector2f theSize      //Default is sf::Vector2f(200, 460)
):
  window(&theWindow),
  position(thePosition),
  size(theSize)
  //numLines(int(theSize.y / 20))//My guess is that the number of lines of text
  //displayed should be the integer part of size.y/20. Change it if you disagree
  //NOTE: numLines currently isn't dynamic because I'm not convinced I
  //      understand "new" and "delete[]" well enough to safely use them.
{
  //Make the background rectangle
  background.setSize(size);
  background.setFillColor(Gray);

  //Make the title
  line[0].setFont(titleFont);
  line[0].setString(theTitle);
  line[0].setCharacterSize(20);//in pixels, not points
  line[0].setFillColor(sf::Color::Black);
  line[0].setPosition(position.x,position.y);

  //Initialize the rest of the lines
  for(int i = 1; i < numLines; i++){
    line[i].setFont(mainFont);
    line[i].setString("");
    line[i].setCharacterSize(15);
    line[i].setFillColor(sf::Color::Black);
    line[i].setPosition(position.x, position.y + float(20 * i));
  }
  for(int i = 0; i < numDivLines; i++){
    divLine[i].setSize(sf::Vector2f(size.x, 1));
    divLine[i].setFillColor(sf::Color::Black);
    divLine[i].setPosition(position.x, position.y + float(40 + 20 * i));
    displayDivLine[i] = false;
  }
}

//Destructor removed since line[] is no longer dynamically allocated
//MessageBox::~MessageBox(){delete[] line;}

void MessageBox::Update(sf::String inputString, bool makeLine){
  //Note: makeLine defaults to false
  SetTopString(markChar + inputString, makeLine);
}

void MessageBox::Update(sf::String inputString1, sf::String inputString2){
  SetTopString(sf::String(" ") + inputString2);
  Update(inputString1);
}

void MessageBox::Update(sf::String inputString1,
                        sf::String inputString2,
                        sf::String inputString3)
{
  SetTopString(sf::String(" ") + inputString3);
  Update(inputString1, inputString2);
}

void MessageBox::Update(sf::String inputString1,
                        sf::String inputString2,
                        sf::String inputString3,
                        sf::String inputString4)
{
  SetTopString(sf::String(" ") + inputString4);
  Update(inputString1, inputString2, inputString3);
}

void MessageBox::Update(sf::String inputString, int inputInt, bool makeLine){
  //Note that makeLine defaults to false
  SetTopString( AddSpacing(std::to_string(inputInt), 22) , makeLine);
  Update(inputString);
}

void MessageBox::Update(sf::String inputString, Bear inputBear){
  sf::String outputString = inputBear.GetName() + "bear";
  SetTopString( AddSpacing(outputString, 22) );
  Update(inputString);
}

void MessageBox::draw(){
  //Recall that a->b is equivalent to (*a).b
  window -> draw(background);
  for(int i = 0; i < numLines; i++){
    window -> draw(line[i]);
  }
  for(int i = 0; i < numDivLines; i++){
    if(displayDivLine[i]){
      window -> draw(divLine[i]);
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

OptionsBox::OptionsBox(
  sf::RenderWindow& theWindow,
  sf::Font& titleFont,
  sf::Font& mainFont,
  const std::array <sf::String, 8>& optionString, //Defaults to the battle text
  sf::Vector2f thePosition,                       //sf::Vector2f(0,465)
  sf::Vector2f theSize,                           //sf::Vector2f(595, 135)
  float dividerPosition                           //350.0f
):
  window(&theWindow),
  position(thePosition),
  size(theSize),
  divPosition(dividerPosition)
{
  //Make the background rectangle
  background.setSize(size);
  background.setFillColor(Gray);
  background.setPosition(position.x, position.y);

  //Make the divider line
  divLine.setSize(sf::Vector2f(2, size.y));
  divLine.setFillColor(sf::Color::Black);
  divLine.setPosition(divPosition, position.y);

  //Make the options
  for(int i = 0; i < numOptionsText; i++){
    optionsText[i].setCharacterSize(25);
    optionsText[i].setFillColor(sf::Color::Black);
    optionsText[i].setString(optionString.at(i));

    //Headings get titleFont, everything else gets mainFont
    if(0 == i % sizeOfEachList){
      optionsText[i].setFont(titleFont);
    }
    else{
      optionsText[i].setFont(mainFont);
    }

    //Positioning depends on which list you're in
    float xPos;
    float yPos;
    if(i < sizeOfEachList){
      xPos = position.x;
      yPos = position.y + float(30 * i);
    }
    else{
      xPos = divPosition + 10;
      yPos = position.y + float(30 * (i - sizeOfEachList));
    }
    optionsText[i].setPosition(xPos, yPos);
  }

  //Make the first set of hightlight boxes
  for(int i = 0; i < sizeOfEachList - 1; i++){
    highlightBox[i] = optionsText[i + 1].getGlobalBounds();
  }

  //Make the second set of hightlight boxes
  for(int i = sizeOfEachList - 1; i < numHighlightBox; i++){
    highlightBox[i] = optionsText[i + 2].getGlobalBounds();
  }
}

void OptionsBox::draw(){
  //Recall that a->b is equivalent to (*a).b
  window -> draw(background);
  window -> draw(divLine);
  for(int  i = 0; i < numOptionsText; i++){
    window -> draw(optionsText[i]);
  }
}

Action OptionsBox::GetAction(sf::Event theEvent){
  if(theEvent.type == sf::Event::KeyPressed){
    if (theEvent.key.code == sf::Keyboard::Num1 ||
        theEvent.key.code == sf::Keyboard::Numpad1)
    {return Action::leg;}

    else if (theEvent.key.code == sf::Keyboard::Num2 ||
             theEvent.key.code == sf::Keyboard::Numpad2)
    {return Action::eye;}

    else if (theEvent.key.code == sf::Keyboard::Num3 ||
             theEvent.key.code == sf::Keyboard::Numpad3)
    {return Action::john_hopkins;}

    else if (theEvent.key.code == sf::Keyboard::Num4 ||
             theEvent.key.code == sf::Keyboard::Numpad4)
    {return Action::quaff;}

    else if (theEvent.key.code == sf::Keyboard::Num5 ||
             theEvent.key.code == sf::Keyboard::Numpad5)
    {return Action::cast;}

    else if (theEvent.key.code == sf::Keyboard::Num6 ||
             theEvent.key.code == sf::Keyboard::Numpad6)
    {return Action::flee;}

    else{
      return Action::nothing;
    }
  }
  else if(theEvent.type == sf::Event::MouseButtonPressed){
    sf::Vector2f clickLocation(float(theEvent.mouseButton.x),
                               float(theEvent.mouseButton.y) );

    if (highlightBox[0].contains(clickLocation)){
      return Action::leg;
    }
    else if (highlightBox[1].contains(clickLocation)){
      return Action::eye;
    }
    else if (highlightBox[2].contains(clickLocation)){
      return Action::john_hopkins;
    }
    else if (highlightBox[3].contains(clickLocation)){
      return Action::quaff;
    }
    else if (highlightBox[4].contains(clickLocation)){
      return Action::cast;
    }
    else if (highlightBox[5].contains(clickLocation)){
      return Action::flee;
    }
    else{
      return Action::nothing;
    }
  }
}

void OptionsBox::Highlight(){
  sf::RectangleShape highlight;
  highlight.setFillColor(ClearYellow);

  for(int i = 0; i < numHighlightBox; i++){
    if(highlightBox[i].contains(sf::Vector2f(sf::Mouse::getPosition(*window)))){
      highlight.setSize(sf::Vector2f(highlightBox[i].width,
                                     highlightBox[i].height));
      highlight.setPosition(highlightBox[i].left,highlightBox[i].top);
      window -> draw(highlight);
    }
  }

}


BearStats::BearStats(
  sf::RenderWindow& theWindow,
  sf::Font& titleFont,
  sf::Font& mainFont,
  Bear theBear,
  bool titleBar,            //Default is true
  sf::Vector2f thePosition, //Default is sf::Vector2f(205, 0)
  sf::Vector2f theSize      //Default is sf::Vector2f(390, 23)
):
window(&theWindow),
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
    bearInfo[i].setFillColor(sf::Color::Black);
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
    bearInfo[i].setFillColor(sf::Color::Black);
    bearInfo[i].setPosition(bearInfo[i-1].getPosition().x,
                            position.y - float(3 - 23 * int(hasTitleBar)) );
  }
  //no need to set dynamic text here, since Update is called by HUD::draw

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
    background[i].setFillColor(Gray);
    background[i].setSize(sf::Vector2f(xPosition[i],size.y));
  }
}

void BearStats::Update(){
  bearInfo[1].setString(bear.GetName());
  bearInfo[3].setString( AddSpacing(std::to_string(bear.GetHealth()), 7) );
  bearInfo[5].setString(bear.GetModifier());
}

void BearStats::SetBear(const Bear& theNewBear){
  bear = theNewBear;
  shouldAppear = true;
}

Bear* BearStats::GetBearPtr(){
  return &bear;
}

bool BearStats::GetShouldAppear(){
  return shouldAppear;
}

void BearStats::SetShouldAppear(bool shouldBearAppear){
  shouldAppear = shouldBearAppear;
}

sf::Vector2f BearStats::GetNameBoxPosition(){
  sf::FloatRect nameBox = bearInfo[1].getGlobalBounds();
  return sf::Vector2f(nameBox.left, nameBox.top);
}

sf::Vector2f BearStats::GetNameBoxSize(){
  sf::FloatRect nameBox = bearInfo[1].getGlobalBounds();
  return sf::Vector2f(nameBox.width, nameBox.height);
}

void BearStats::draw(){
  if(shouldAppear){
    //Recall that a->b is equivalent to (*a).b
    for(int i = 0; i < numBackground; i++){
      window -> draw(background[i]);
    }
    if(hasTitleBar){
      for(int i = 0; i < numBearInfo; i += 2){
        window -> draw(bearInfo[i]);
      }
    }
    for(int i = 1; i < numBearInfo; i += 2){
      window -> draw(bearInfo[i]);
    }
  }
}


PlayerStats::PlayerStats(
  sf::RenderWindow& theWindow,
  sf::Font& titleFont,
  sf::Font& mainFont,
  Player& thePlayer,
  sf::Vector2f thePosition, //Default is sf::Vector2f(600, 0)
  sf::Vector2f theSize      //Default is sf::Vector2f(200, 600)
):
window(&theWindow),
player(&thePlayer),
position(thePosition),
size(theSize)
{
  //Make the background rectangle
  background.setSize(size);
  background.setFillColor(Gray);
  background.setPosition(position.x, position.y);

  //Make the header
  header.setFont(titleFont);
  header.setString("   YOUR STATUS");
  header.setCharacterSize(20);
  header.setFillColor(sf::Color::Black);
  header.setPosition(position.x, position.y);

  //Make the health and drank info
  health[0].setFont(titleFont);
  health[0].setString("Health:");
  health[1].setFont(mainFont);
  //no need to set health here, since Update is called by HUD::draw
  health[2].setFont(titleFont);
  health[2].setString("Dranks:");
  health[3].setFont(mainFont);
  //no need to set numDranks here, since Update is called by HUD::draw
  health[4].setFont(titleFont);
  health[4].setString("Effects:");
  health[5].setFont(mainFont);
  health[5].setString("                  None");//FIXME
  for(int i = 0; i < numHealth; i++){
    health[i].setCharacterSize(15);
    health[i].setFillColor(sf::Color::Black);
    health[i].setPosition(position.x, position.y + float(20 + 20 * (i/2)));
  }

  //Make the ability score header
  ability[0].setFont(titleFont);
  ability[0].setCharacterSize(15);
  ability[0].setFillColor(sf::Color::Black);
  ability[0].setString("Ablilities:");
  ability[0].setPosition(position.x, position.y + 80);

  //Make the ability score info
  for(int i = 1; i < numAbility; i += 2){
    ability[i].setFont(mainFont);
    ability[i].setCharacterSize(15);
    ability[i].setFillColor(sf::Color::Black);
    ability[i].setPosition(position.x + float(100 * ( i / 6) ),
                           position.y + float(87 + (i % 6) * 10) );

    ability[i+1].setFont(mainFont);
    ability[i+1].setCharacterSize(15);
    ability[i+1].setFillColor(sf::Color::Black);
    ability[i+1].setPosition(position.x + float(100 * (i / 6) ),
                             position.y + float(87 + (i % 6) * 10) );
  }
  ability[1].setString("STR:");
  ability[3].setString("DEX:");
  ability[5].setString("CON:");
  ability[7].setString("INT:");
  ability[9].setString("WIS:");
  ability[11].setString("CHA:");

  //Make the spells header
  spell[0].setFont(titleFont);
  spell[0].setCharacterSize(15);
  spell[0].setFillColor(sf::Color::Black);
  spell[0].setString("Spells:");
  spell[0].setPosition(position.x, position.y + 155);

  //Make the spells info
  for(int i = 1; i < numSpell; i += 2){
    spell[i].setFont(mainFont);
    spell[i].setCharacterSize(15);
    spell[i].setFillColor(sf::Color::Black);
    spell[i].setPosition(position.x, position.y + float(163 + i * 10) );

    spell[i+1].setFont(mainFont);
    spell[i+1].setCharacterSize(15);
    spell[i+1].setFillColor(sf::Color::Black);
    spell[i+1].setPosition(position.x, position.y + float(163 + i * 10) );
    spell[i+1].setString("            5");//FIXME
  }
  //FIXME: This whole list should eventually be dynamic
  spell[1].setString(" Pain:");
  spell[3].setString(" Death:");
  spell[5].setString(" Pleasure:");
  spell[7].setString(" STR Up:");
  spell[9].setString(" STR Jump:");
  spell[11].setString(" STR Boost:");
  spell[13].setString(" Fish:");
  spell[15].setString(" Big Fish:");
  spell[17].setString(" Invuln:");
  spell[19].setString(" Fireball:");
  spell[21].setString(" Iceball:");
  spell[23].setString(" Lightning:");
  spell[25].setString(" STR Down:");
  spell[27].setString(" STR Drain:");
  spell[29].setString(" Weakness:");
  spell[31].setString(" Reversal:");
  spell[33].setString(" HP Drain:");
  spell[35].setString(" Vampirism:");
  spell[37].setString(" Detect:");
  spell[39].setString(" Dispel:");
  spell[41].setString(" Cleanse:");

  //Divide up the spells
  for(int i = 0; i < numDivLine; i++){
    divLine[i].setSize(sf::Vector2f(200,1));
    divLine[i].setFillColor(sf::Color::Black);
    divLine[i].setPosition(position.x, position.y + float(162 + 10 + i * 60) );
  }
}

void PlayerStats::Update(){
  //Health
  sf::String playerHealth = std::to_string(player -> GetHealth());
  playerHealth += "/";
  playerHealth += std::to_string(player -> GetMaxHealth());
  health[1].setString(AddSpacing(playerHealth, 22) );

  //Dranks
  health[3].setString(AddSpacing(std::to_string(player -> GetNumDranks()), 22));

  //Ability scores
  for(int i = 1; i <= 6; i++){
    ability[2*i].setString(AddSpacing(std::to_string(player->GetAbil(i-1)),10));
  }
}

void PlayerStats::draw(){
  //Recall that a->b is equivalent to (*a).b
  window -> draw(background);
  window -> draw(header);
  for(int i = 0; i < numHealth; i++){
    window -> draw(health[i]);
  }
  for(int i = 0; i < numAbility; i++){
    window -> draw(ability[i]);
  }
  for(int i = 0; i < numSpell; i++){
    window -> draw(spell[i]);
  }
  for(int i = 0; i < numDivLine; i++){
    window -> draw(divLine[i]);
  }
}


HUD::HUD(sf::RenderWindow& theWindow,
        sf::Font& titleFont,
        sf::Font& mainFont,
        Player& thePlayer,
        const Bear& theBear
):
messages(theWindow,titleFont,mainFont,"Messages:"),
options(theWindow,titleFont,mainFont),
bearStats{BearStats(theWindow,titleFont,mainFont,theBear,true),
  BearStats(theWindow,titleFont,mainFont,Bear(),false,sf::Vector2f(205,50)),
  BearStats(theWindow,titleFont,mainFont,Bear(),false,sf::Vector2f(205,75)),
  BearStats(theWindow,titleFont,mainFont,Bear(),false,sf::Vector2f(205,100)),
  BearStats(theWindow,titleFont,mainFont,Bear(),true)},
playerStats(theWindow,titleFont,mainFont,thePlayer),
window(&theWindow),
player(&thePlayer)
{
  bear = bearStats[0].GetBearPtr();
  bear -> SetMessageBox(messages);
  player -> SetMessageBox(messages);
}

int HUD::GetNumBears(){
  int numBears = 4;
  for(int i = 3; i >= 0; i--){
    if(!bearStats[i].GetShouldAppear()){
      numBears = i;
    }
  }
  return numBears;
}


void HUD::AddEnemyBears(Bear bear[], int numBears){
  for(int i = 0; i < numBears; i++){
    bearStats[i].SetBear(bear[i]);
    bearStats[i].GetBearPtr() -> SetMessageBox(messages);
    bearStats[i].SetShouldAppear(true);
  }
}


bool HUD::RemoveDeadCombatants(){
  if(player -> IsDead()){
    return true;
  }
  //FriendBear stuff here. (No return statement)
  for(int i = GetNumBears() - 1; i >= 0; i--){
    if(bearStats[i].GetBearPtr() -> IsDead()){
      Bear tempBear = *bearStats[i].GetBearPtr();
      for(int j = i; j < 3; j++){
        bearStats[j].SetBear( *bearStats[j + 1].GetBearPtr() );
        bearStats[j].SetShouldAppear( bearStats[j + 1].GetShouldAppear() );
      }
      bearStats[3].SetBear(tempBear);
      bearStats[3].SetShouldAppear(false);

      bear = bearStats[0].GetBearPtr();//Now targeting the top bear
    }
  }

  //The battle is over iff the top bear is dead:
  return(!bearStats[0].GetShouldAppear());
}

TurnOf HUD::TakeAction(sf::Event theEvent)
{
  if(isPickingSpell){
    //playerStats.GetSpell(theEvent);
  }
  else{
    if(theEvent.key.code == sf::Keyboard::Up){
      const int targetBearIndex = TargetBearIndex();
      if(0 == targetBearIndex){
        bear = bearStats[GetNumBears() - 1].GetBearPtr();
      }
      else{
        bear = bearStats[targetBearIndex - 1].GetBearPtr();
      }
    }
    else if(theEvent.key.code == sf::Keyboard::Down){
      const int targetBearIndex = TargetBearIndex();
      if(GetNumBears() - 1 == targetBearIndex){
        bear = bearStats[0].GetBearPtr();
      }
      else{
        bear = bearStats[targetBearIndex + 1].GetBearPtr();
      }
    }
    else{
      Action theAction = options.GetAction(theEvent);
      if (theAction == Action::cast) {
        //isPickingSpell = true;
        messages.Update(sf::String("Spellcasting"),
                        sf::String("is unsupported."));//TEMP
      }
      else{
        return player -> TakeAction(theAction, *bear);
      }
    }
  }
  return TurnOf::player;
}

void HUD::draw(){
  messages.draw();

  options.draw();

  playerStats.Update();
  playerStats.draw();

  for(int i = 0; i < 5; i++){
    bearStats[i].Update();
    bearStats[i].draw();
  }

  Highlight();
}

void HUD::Highlight(){
  options.Highlight();

  sf::RectangleShape bearHighlight;
  bearHighlight.setFillColor(ClearYellow);

  if( bearStats[1].GetShouldAppear() ){
    for(int i = 0; i < 4; i++){
      if(bearStats[i].GetBearPtr() == bear){
        bearHighlight.setSize(bearStats[i].GetNameBoxSize());
        bearHighlight.setPosition(bearStats[i].GetNameBoxPosition());
        window -> draw(bearHighlight);
      }
    }
  }

}

int HUD::TargetBearIndex(){
  int targetBearIndex = 0;
  for(int i = 0; i < 4; i++){
    if(bearStats[i].GetBearPtr() == bear){
      targetBearIndex = i;
    }
  }
  return targetBearIndex;
}
