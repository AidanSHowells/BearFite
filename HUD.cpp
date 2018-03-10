#include "HUD.h"
#include <string>//For std::to_string
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


int numDigits(int number){
  if(number == 0){return 1;}

  int digits = 0;
  if (number < 0){digits = 1;}//So the '-' counts as a digit
  while (number) {
    number /= 10;//Integer division ftw
    digits++;
  }
  return digits;
}


MessageBox::MessageBox(
  sf::RenderWindow& theWindow,
  sf::Font& titleFont,
  sf::Font& mainFont,
  sf::String theTitle,
  sf::Vector2f thePosition, //Default is sf::Vector2f(0, 0)
  sf::Vector2f theSize      //Default is sf::Vector2f(200, 400)
):
  window(&theWindow),
  position(thePosition),
  size(theSize)
  //numLines(int(theSize.y / 20))//My guess is that the number of lines of text
  //displayed should be the integer part of size.y/20. Fix it if you disagree
  //NOTE: numLines currently isn't dynamic because I'm not convinced I
  //      understand "new" and "delete[]" well enought to safely use them.
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
    line[i].setPosition(position.x, position.y + 20 * i);
  }
}

//Destructor removed since line[] is no longer dynamically allocated
//MessageBox::~MessageBox(){delete[] line;}

void MessageBox::Update(sf::String inputString){
  //Move everything down one
  for(int i = numLines - 1; i > 1; i--){
    line[i].setString(line[i-1].getString());
  }
  //Make the top line inputString
  line[1].setString(sf::String(">") += inputString);
}

void MessageBox::Update(sf::String inputString1, sf::String inputString2){
  //Move everything down one
  for(int i = numLines - 1; i > 1; i--){
    line[i].setString(line[i-1].getString());
  }
  //Make the top line inputString2
  line[1].setString(sf::String(" ") += inputString2);

  //Now move everything down one again and make the top line inputString1
  Update(inputString1);
}

void MessageBox::Update(sf::String inputString, int imputInt){
  //Move everything down one
  for(int i = numLines - 1; i > 1; i--){
    line[i].setString(line[i-1].getString());
  }
  //Make the top line inputInt
  sf::String spacing = "";
  for(int i = 0; i < 22 - numDigits(imputInt); i++){
    spacing += sf::String(" ");
  }
  line[1].setString(spacing += sf::String(std::to_string(imputInt)));

  //Now move everything down one again and make the top line inputString
  Update(inputString);
}

void MessageBox::draw(){
  //Recall that a->b is equivalent to (*a).b
  window -> draw(background);
  for(int i = 0; i < numLines; i++){
    window -> draw(line[i]);
  }
}


OptionsBox::OptionsBox(
  sf::RenderWindow& theWindow,
  sf::Font& titleFont,
  sf::Font& mainFont,
  sf::Vector2f thePosition, //Default is sf::Vector2f(0,405)
  sf::Vector2f theSize,     //Default is sf::Vector2f(800, 195)
  float dividerPosition     //Default is 420.0f
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

  //Make the first title
  punch[0].setFont(titleFont);
  punch[0].setString("PUNCH:Where Punch Bear?");
  punch[0].setCharacterSize(30);
  punch[0].setFillColor(sf::Color::Black);
  punch[0].setPosition(position.x, position.y);

  //Make the first set of options
  for(int i = 1; i < 4; i++){
    punch[i].setFont(mainFont);
    punch[i].setCharacterSize(30);
    punch[i].setFillColor(sf::Color::Black);
    punch[i].setPosition(position.x, position.y + 40 * i);
  }
  punch[1].setString("1:Leg");
  punch[2].setString("2:Eye");
  punch[3].setString("3:John Hopkins");

  //Make the second title
  notPunch[0].setFont(titleFont);
  notPunch[0].setString("NOT PUNCH:What Do?");
  notPunch[0].setCharacterSize(30);
  notPunch[0].setFillColor(sf::Color::Black);
  notPunch[0].setPosition(divPosition + 10, position.y);

  //Make the second set of options
  for(int i = 1; i < 4; i++){
    notPunch[i].setFont(mainFont);
    notPunch[i].setCharacterSize(30);
    notPunch[i].setFillColor(sf::Color::Black);
    notPunch[i].setPosition(divPosition + 10, position.y + 40 * i);
  }
  notPunch[1].setString("4:Quaff Drank");
  notPunch[2].setString("5:Cast Spell");
  notPunch[3].setString("6:Flee");

  //Make the first set of bounding boxes
  for(int i = 0; i < 3; i++){
    textBox[i] = punch[i + 1].getGlobalBounds();
  }

  //Make the second set of bounding boxes
  for(int i = 3; i < 6; i++){
    textBox[i] = notPunch[i - 2].getGlobalBounds();
  }
}

void OptionsBox::draw(){
  //Recall that a->b is equivalent to (*a).b
  window -> draw(background);
  window -> draw(divLine);
  for(int i = 0; i < 4; i++){
    window -> draw(punch[i]);
  }
  for(int i = 0; i < 4; i++){
    window -> draw(notPunch[i]);
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
  if(theEvent.type == sf::Event::MouseButtonPressed){
    sf::Vector2f clickLocation(theEvent.mouseButton.x,theEvent.mouseButton.y);

    if (textBox[0].contains(clickLocation)){
      return Action::leg;
    }
    else if (textBox[1].contains(clickLocation)){
      return Action::eye;
    }
    else if (textBox[2].contains(clickLocation)){
      return Action::john_hopkins;
    }
    else if (textBox[3].contains(clickLocation)){
      return Action::quaff;
    }
    else if (textBox[4].contains(clickLocation)){
      return Action::cast;
    }
    else if (textBox[5].contains(clickLocation)){
      return Action::flee;
    }
    else{
      return Action::nothing;
    }
  }
}

void OptionsBox::Highlight(){
  sf::RectangleShape highlight;
  highlight.setFillColor(sf::Color(255,255,0,153));

  for(int i = 0; i < 6; i++){
    if(textBox[i].contains(sf::Vector2f(sf::Mouse::getPosition(*window)))){
      highlight.setSize(sf::Vector2f(textBox[i].width,textBox[i].height));
      highlight.setPosition(textBox[i].left,textBox[i].top);
      window -> draw(highlight);
    }
  }

}


BearStats::BearStats(
  sf::RenderWindow& theWindow,
  sf::Font& titleFont,
  sf::Font& mainFont,
  Bear& theBear,
  sf::Vector2f thePosition, //Default is sf::Vector2f(205, 0)
  sf::Vector2f theSize      //Default is sf::Vector2f(390, 50)
):
window(&theWindow),
bear(&theBear),
position(thePosition),
size(theSize)
{
  //Make the fixed text
  for(int i = 0; i < 6; i += 2){
    bearInfo[i].setFont(titleFont);
    bearInfo[i].setCharacterSize(20);
    bearInfo[i].setFillColor(sf::Color::Black);
  }
  bearInfo[0].setString("Species:");
  bearInfo[0].setPosition(position.x, position.y);
  bearInfo[2].setString("Health:");
  bearInfo[2].setPosition(position.x + 140, position.y);
  bearInfo[4].setString("Modifer:");
  bearInfo[4].setPosition(position.x + 232, position.y);

  //Make the dynamic text
  for(int i = 1; i < 6; i += 2){
    bearInfo[i].setFont(mainFont);
    bearInfo[i].setCharacterSize(20);
    bearInfo[i].setFillColor(sf::Color::Black);
    bearInfo[i].setPosition(bearInfo[i-1].getPosition().x, position.y + 20);
  }
  sf::String spacing = "";//This is used to make the bear's health right-aligned
  for(int i = 0; i < 7 - numDigits(bear -> GetHealth()); i++){
    spacing += sf::String(" ");
  }
  bearInfo[1].setString(bear -> GetName());
  bearInfo[3].setString(spacing += std::to_string(bear -> GetHealth()));
  bearInfo[5].setString("Horse Defense");//FIXME:This should be dynamic

  //Make the background rectangles
  background[0].setPosition(bearInfo[0].getPosition().x, position.y);
  background[1].setPosition(bearInfo[2].getPosition().x - 2, position.y);
  background[2].setPosition(bearInfo[4].getPosition().x - 2, position.y);

  float xPosition[3] = {
    background[1].getPosition().x - background[0].getPosition().x - 2,
    background[2].getPosition().x - background[1].getPosition().x - 2,
    size.x + position.x - background[2].getPosition().x
  };

  for(int i = 0; i < 3; i++){
    background[i].setFillColor(Gray);
    background[i].setSize(sf::Vector2f(xPosition[i],size.y));
  }
}

void BearStats::Update(){
  sf::String spacing = "";//This is used to make the bear's health right-aligned
  for(int i = 0; i < 7 - numDigits(bear -> GetHealth()); i++){
    spacing += sf::String(" ");
  }
  bearInfo[3].setString(spacing += std::to_string(bear -> GetHealth()));
}

void BearStats::draw(){
  //Recall that a->b is equivalent to (*a).b
  for(int i = 0; i < 3; i++){
    window -> draw(background[i]);
  }
  for(int i = 0; i < 6; i++){
    window -> draw(bearInfo[i]);
  }
}


PlayerStats::PlayerStats(
  sf::RenderWindow& theWindow,
  sf::Font& titleFont,
  sf::Font& mainFont,
  Player& thePlayer,
  sf::Vector2f thePosition, //Default is sf::Vector2f(600, 0)
  sf::Vector2f theSize      //Default is sf::Vector2f(200, 400)
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
  header.setString("YOUR STATUS");
  header.setCharacterSize(30);
  header.setFillColor(sf::Color::Black);
  header.setPosition(position.x, position.y);

  //Make the health and drank info
  health[0].setFont(titleFont);
  health[0].setString("Health:");
  health[1].setFont(mainFont);
  health[1].setString("           40/40");//FIXME
  health[2].setFont(titleFont);
  health[2].setString("Dranks:");
  health[3].setFont(mainFont);
  health[3].setString("               5");//FIXME
  for(int i = 0; i < 4; i++){
    health[i].setCharacterSize(20);
    health[i].setFillColor(sf::Color::Black);
    health[i].setPosition(position.x, position.y + 30 + 20 * (i/2));
  }

  //Make the ability score header
  ability[0].setFont(titleFont);
  ability[0].setCharacterSize(20);
  ability[0].setFillColor(sf::Color::Black);
  ability[0].setString("Ablilities:");
  ability[0].setPosition(position.x, position.y + 70);

  //Make the ability score info
  for(int i = 1; i < 13; i += 2){
    ability[i].setFont(mainFont);
    ability[i].setCharacterSize(20);
    ability[i].setFillColor(sf::Color::Black);
    ability[i].setPosition(position.x, position.y + 77 + i * 10);

    ability[i+1].setFont(mainFont);
    ability[i+1].setCharacterSize(20);
    ability[i+1].setFillColor(sf::Color::Black);
    ability[i+1].setPosition(position.x, position.y + 77 + i * 10);
    ability[i+1].setString("           10/10");//FIXME
  }
  ability[1].setString("STR:");
  ability[3].setString("DEX:");
  ability[5].setString("CON:");
  ability[7].setString("INT:");
  ability[9].setString("WIS:");
  ability[11].setString("CHA:");

  //Make the spells header
  spell[0].setFont(titleFont);
  spell[0].setCharacterSize(20);
  spell[0].setFillColor(sf::Color::Black);
  spell[0].setString("Spells:");
  spell[0].setPosition(position.x, position.y + 205);

  //Make the spells info
  for(int i = 1; i < 17; i += 2){
    spell[i].setFont(mainFont);
    spell[i].setCharacterSize(20);
    spell[i].setFillColor(sf::Color::Black);
    spell[i].setPosition(position.x, position.y + 213 + i * 10);

    spell[i+1].setFont(mainFont);
    spell[i+1].setCharacterSize(20);
    spell[i+1].setFillColor(sf::Color::Black);
    spell[i+1].setPosition(position.x, position.y + 213 + i * 10);
    spell[i+1].setString("             5/5");//FIXME
  }
  //FIXME: This whole list should eventually be dynamic
  spell[1].setString("Pleasure:");
  spell[2].setString("           10/10");
  spell[3].setString("Death:");
  spell[5].setString("Fish:");
  spell[7].setString("STR Boost:");
  spell[9].setString("DEX Boost:");
  spell[11].setString("WIS Boost:");
  spell[13].setString("CHA Boost:");
  spell[15].setString("Fireball:");
}

/*
void PlayerStats::PlayerStats(){
  sf::String spacing = "";//This is used to make the bear's health right-aligned
  for(int i = 0; i < 7 - numDigits(bear -> GetHealth()); i++){
    spacing += sf::String(" ");
  }
  bearInfo[3].setString(spacing += std::to_string(bear -> GetHealth()));
}*/

void PlayerStats::draw(){
  //Recall that a->b is equivalent to (*a).b
  window -> draw(background);
  window -> draw(header);
  for(int i = 0; i < 4; i++){
    window -> draw(health[i]);
  }
  for(int i = 0; i < 13; i++){
    window -> draw(ability[i]);
  }
  for(int i = 0; i < 17; i++){
    window -> draw(spell[i]);
  }
}


Display::Display(sf::RenderWindow& theWindow,
        sf::Font& titleFont,
        sf::Font& mainFont,
        Player& thePlayer,
        Bear& theBear
):
messages(theWindow,titleFont,mainFont,"Messages:"),
options(theWindow,titleFont,mainFont),
bearStats(theWindow,titleFont,mainFont,theBear),
playerStats(theWindow,titleFont,mainFont,thePlayer),
window(&theWindow),
player(&thePlayer),
bear(&theBear)
{
  player -> SetMessageBox(messages);
  bear -> SetMessageBox(messages);
}

Action Display::GetAction(sf::Event theEvent){
  Action theAction = options.GetAction(theEvent);
  if (theAction == Action::cast) {
    //Get spells
  }
  return theAction;
}

void Display::draw(){
  messages.draw();

  options.draw();

  //playerStats.Update();
  playerStats.draw();

  bearStats.Update();
  bearStats.draw();

  options.Highlight();
}



//The main function is temporary; it makes it easier to test new features
int main(){

  //bool isPlayerTurn = true; //I think this (a bool inside of the main
  //function) is how we should handle taking turns.


  //Load the fonts
  sf::Font courierNew;
  if (!courierNew.loadFromFile("Resources/cour.ttf")){
    return EXIT_FAILURE;
  }
  sf::Font courierNewBd;
  if (!courierNewBd.loadFromFile("Resources/courbd.ttf")){
    return EXIT_FAILURE;
  }

  //Create the window
  sf::RenderWindow window(sf::VideoMode(800, 600), "BearFite", sf::Style::Titlebar | sf::Style::Close);
  window.setKeyRepeatEnabled(false);

  //Make the player and bear
  Player player;
  Bear bear;

  //Make the HUD
  Display HUD(window,courierNewBd,courierNew,player,bear);


  while (window.isOpen()){
    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){
        window.close();
      }
      if (event.type == sf::Event::KeyPressed ||
          event.type == sf::Event::MouseButtonPressed)
      {
        player.TakeAction(HUD.GetAction(event), bear);
      }

    }


    //Draw the stuff to the screen
    window.clear();
    HUD.draw();
    window.display();
  }

  return 0;
}
