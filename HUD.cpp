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

void MessageBox::Update(sf::String inputString1,
                        sf::String inputString2,
                        sf::String inputString3)
{
  //Move everything down one
  for(int i = numLines - 1; i > 1; i--){
    line[i].setString(line[i-1].getString());
  }
  //Make the top line inputString3
  line[1].setString(sf::String(" ") += inputString3);

  //Now put in the first two strings
  Update(inputString1, inputString2);
}

void MessageBox::Update(sf::String inputString1,
                        sf::String inputString2,
                        sf::String inputString3,
                        sf::String inputString4)
{
  //Move everything down one
  for(int i = numLines - 1; i > 1; i--){
    line[i].setString(line[i-1].getString());
  }
  //Make the top line inputString4
  line[1].setString(sf::String(" ") += inputString4);

  //Now put in the first three strings
  Update(inputString1, inputString2, inputString3);
}

void MessageBox::Update(sf::String inputString, int inputInt){
  //Move everything down one
  for(int i = numLines - 1; i > 1; i--){
    line[i].setString(line[i-1].getString());
  }
  //Make the top line inputInt
  sf::String spacing = "";
  for(int i = 0; i < 22 - numDigits(inputInt); i++){
    spacing += sf::String(" ");
  }
  line[1].setString(spacing += sf::String(std::to_string(inputInt)));

  //Now move everything down one again and make the top line inputString
  Update(inputString);
}

void MessageBox::Update(sf::String inputString, Bear inputBear){
  //Move everything down one
  for(int i = numLines - 1; i > 1; i--){
    line[i].setString(line[i-1].getString());
  }
  sf::String outputString = inputBear.GetName() + "bear";
  sf::String spacing = "";
  for(int i = 0; i < 22 - outputString.getSize(); i++){
    spacing += sf::String(" ");
  }
  line[1].setString(spacing + outputString);

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
  sf::Vector2f thePosition, //Default is sf::Vector2f(0,465)
  sf::Vector2f theSize,     //Default is sf::Vector2f(595, 135)
  float dividerPosition     //Default is 350.0f
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
  punch[0].setCharacterSize(25);
  punch[0].setFillColor(sf::Color::Black);
  punch[0].setPosition(position.x, position.y);

  //Make the first set of options
  for(int i = 1; i < numPunch; i++){
    punch[i].setFont(mainFont);
    punch[i].setCharacterSize(25);
    punch[i].setFillColor(sf::Color::Black);
    punch[i].setPosition(position.x, position.y + 30 * i);
  }
  punch[1].setString("1:Leg");
  punch[2].setString("2:Eye");
  punch[3].setString("3:John Hopkins");

  //Make the second title
  notPunch[0].setFont(titleFont);
  notPunch[0].setString("ELSE:What Do?");
  notPunch[0].setCharacterSize(25);
  notPunch[0].setFillColor(sf::Color::Black);
  notPunch[0].setPosition(divPosition + 10, position.y);

  //Make the second set of options
  for(int i = 1; i < numNotPunch; i++){
    notPunch[i].setFont(mainFont);
    notPunch[i].setCharacterSize(25);
    notPunch[i].setFillColor(sf::Color::Black);
    notPunch[i].setPosition(divPosition + 10, position.y + 30 * i);
  }
  notPunch[1].setString("4:Quaff Drank");
  notPunch[2].setString("5:Cast Spell");
  notPunch[3].setString("6:Flee");

  //Make the first set of bounding boxes
  for(int i = 0; i < numPunch - 1; i++){
    textBox[i] = punch[i + 1].getGlobalBounds();
  }

  //Make the second set of bounding boxes
  for(int i = 3; i < numTextBox; i++){
    textBox[i] = notPunch[i - 2].getGlobalBounds();
  }
}

void OptionsBox::draw(){
  //Recall that a->b is equivalent to (*a).b
  window -> draw(background);
  window -> draw(divLine);
  for(int i = 0; i < numPunch; i++){
    window -> draw(punch[i]);
  }
  for(int i = 0; i < numNotPunch; i++){
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
  else if(theEvent.type == sf::Event::MouseButtonPressed){
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
  else{
    //FIXME: There should probably be an error message here
  }
}

void OptionsBox::Highlight(){
  sf::RectangleShape highlight;
  highlight.setFillColor(sf::Color(255,255,0,153));

  for(int i = 0; i < numTextBox; i++){
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
  Bear* theBear,
  bool titleBar,            //Default is true
  sf::Vector2f thePosition, //Default is sf::Vector2f(205, 0)
  sf::Vector2f theSize      //Default is sf::Vector2f(390, 23)
):
window(&theWindow),
bear(theBear),
position(thePosition),
size(theSize + sf::Vector2f(0, 25 * int(titleBar)) ),
hasTitleBar(titleBar)
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
  bearInfo[4].setString("Modifer:");
  bearInfo[4].setPosition(position.x + 232, position.y);

  //Make the dynamic text
  for(int i = 1; i < numBearInfo; i += 2){
    bearInfo[i].setFont(mainFont);
    bearInfo[i].setCharacterSize(20);
    bearInfo[i].setFillColor(sf::Color::Black);
    bearInfo[i].setPosition(bearInfo[i-1].getPosition().x,
                            position.y - 3 + 23 * int(hasTitleBar));
  }
  //no need to set name & health here, since Update is called by Display.draw
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

  for(int i = 0; i < numBackground; i++){
    background[i].setFillColor(Gray);
    background[i].setSize(sf::Vector2f(xPosition[i],size.y));
  }
}

void BearStats::Update(){
  if(nullptr != bear){
    bearInfo[1].setString(bear -> GetName());

    sf::String spacing = "";//This is used to make the bear's health right-aligned
    for(int i = 0; i < 7 - numDigits(bear -> GetHealth()); i++){
      spacing += sf::String(" ");
    }
    bearInfo[3].setString(spacing += std::to_string(bear -> GetHealth()));
  }
}

void BearStats::NewBearPtr(Bear* theNewBearPtr){
  bear = theNewBearPtr;
}

Bear* BearStats::GetBearPtr(){
  return bear;
}

void BearStats::draw(){
  if(nullptr != bear){
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
  //no need to set health here, since Update is called by Display.draw
  health[2].setFont(titleFont);
  health[2].setString("Dranks:");
  health[3].setFont(mainFont);
  //no need to set numDranks here, since Update is called by Display.draw
  health[4].setFont(titleFont);
  health[4].setString("Effects:");
  health[5].setFont(mainFont);
  health[5].setString("                  None");//FIXME
  for(int i = 0; i < numHealth; i++){
    health[i].setCharacterSize(15);
    health[i].setFillColor(sf::Color::Black);
    health[i].setPosition(position.x, position.y + 20 + 20 * (i/2));
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
    ability[i].setPosition(position.x + 100*(i/6), position.y + 87 + (i%6)*10);

    ability[i+1].setFont(mainFont);
    ability[i+1].setCharacterSize(15);
    ability[i+1].setFillColor(sf::Color::Black);
    ability[i+1].setPosition(position.x + 100*(i/6), position.y + 87+(i%6)*10);
    ability[i+1].setString("     10/10");//FIXME
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
    spell[i].setPosition(position.x, position.y + 163 + i * 10);

    spell[i+1].setFont(mainFont);
    spell[i+1].setCharacterSize(15);
    spell[i+1].setFillColor(sf::Color::Black);
    spell[i+1].setPosition(position.x, position.y + 163 + i * 10);
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
    divLine[i].setPosition(position.x, position.y + 162 + 10 + i * 60);
  }
}

void PlayerStats::Update(){
  sf::String playerHealth = std::to_string(player -> GetHealth());
  playerHealth += "/";
  playerHealth += std::to_string(player -> GetMaxHealth());

  sf::String spacing = "";//This is used to make things right-aligned
  for(int i = 0; i < 22 - playerHealth.getSize(); i++){
    spacing += " ";
  }
  health[1].setString(spacing + playerHealth);

  spacing = "";
  for(int i = 0; i < 22 - numDigits(player -> GetNumDranks() ); i++){
    spacing += " ";
  }
  health[3].setString(spacing + std::to_string(player -> GetNumDranks()));
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


Display::Display(sf::RenderWindow& theWindow,
        sf::Font& titleFont,
        sf::Font& mainFont,
        Player& thePlayer,
        Bear& theBear
):
messages(theWindow,titleFont,mainFont,"Messages:"),
options(theWindow,titleFont,mainFont),
bearStats{BearStats(theWindow,titleFont,mainFont,&theBear,true),
  BearStats(theWindow,titleFont,mainFont,nullptr,false,sf::Vector2f(205,50)),
  BearStats(theWindow,titleFont,mainFont,nullptr,false,sf::Vector2f(205,75)),
  BearStats(theWindow,titleFont,mainFont,nullptr,false,sf::Vector2f(205,100)),
  BearStats(theWindow,titleFont,mainFont,nullptr,true)},
playerStats(theWindow,titleFont,mainFont,thePlayer),
window(&theWindow),
player(&thePlayer),
bear(&theBear)
{
  player -> SetMessageBox(messages);
  bear -> SetMessageBox(messages);
}

int Display::GetNumBears(){
  int numBears = 4;
  for(int i = 3; i >= 0; i--){
    if(nullptr == bearStats[i].GetBearPtr()){
      numBears = i;
    }
  }
  return numBears;
}

//All parameters but first default to nullptr. This first should bever be null.
//If bear[N]==nullptr, then bear[M] should be nullptr for all  M > N
void Display::AddEnemyBears(Bear* bear0, Bear* bear1, Bear* bear2, Bear* bear3){
  Bear* newBear[4] = {bear0, bear1, bear2, bear3};
  bool error = false;

  for(int i = 0; i < 4; i++){
    if(nullptr == newBear[i]){
      for(int j = i + 1; j < 4; j++){
        if(nullptr != newBear[j]){
          error = true;
        }
      }
    }
  }
  if(error){
    //FIXME: Halt and Catch Fire
  }
  else{
    bool done = false;
    for(int i = 3; i >= 0; i--){
      if(!done && nullptr != newBear[i]){
        for(int j = i; j >= 0; j--){
          bearStats[j].NewBearPtr(newBear[j]);
          newBear[j] -> SetMessageBox(messages);
        }
        done = true;
      }//end if
    }//end for
  }
}

bool Display::RemoveDeadCombatants(){
  if(player -> IsDead()){
    return true;
  }
  //FriendBear stuff here. (No return statement)
  for(int i = GetNumBears() - 1; i >= 0; i--){
    if(bearStats[i].GetBearPtr() -> IsDead()){
      for(int j = i; j < 3; j++){
        bearStats[j].NewBearPtr(bearStats[j + 1].GetBearPtr());
      }
      bearStats[3].NewBearPtr(nullptr);
      bear = bearStats[0].GetBearPtr();//Now targeting the top bear
    }
  }
  return(nullptr == bear);//The battle is over iff the top bear is dead
}

TurnOf Display::TakeAction(sf::Event theEvent)
{
  if(isPickingSpell){
    //playerStats.GetSpell(theEvent);
  }
  else{
    if(theEvent.key.code == sf::Keyboard::Up){
      //FIXME
    }
    else if(theEvent.key.code == sf::Keyboard::Down){
      //FIXME
    }
    else{
      Action theAction = options.GetAction(theEvent);
      if (theAction == Action::cast) {
        //isPickingSpell = true;
        messages.Update("Spellcasting", "is unsupported.");//TEMP
      }
      else{
        return player -> TakeAction(theAction, *bear);
      }
    }
  }
  return TurnOf::player;
}

void Display::draw(){
  messages.draw();

  options.draw();

  playerStats.Update();
  playerStats.draw();

  for(int i = 0; i < 5; i++){
    bearStats[i].Update();
    bearStats[i].draw();
  }

  options.Highlight();
}


//TEMP: Belongs in BearBattle.h
bool BearBattle(Display& theHUD, int& tempInt);

//TEMP: Belongs with the main function
#include <cstdlib>
#include <ctime>
#include "BearList.h"

//The main function is temporary; it makes it easier to test new features
int main(){
  srand(unsigned(time(NULL)));


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

  //Keep track of wins
  int winsvBabby = 0;
  int lossesToBabby = 0;
  int winsvBlack = 0;
  int lossesToBlack = 0;
  int winsvBrown = 0;
  int lossesToBrown = 0;
  int winsvPolar = 0;
  int lossesToPolar = 0;
  int winsvParty = 0;
  int lossesToParty = 0;

  MessageBox messages(window,courierNewBd,courierNew,"Messages:");
  messages.Update("Q = Babby, W = Black",
                  "E = Brown, R = Polar",
                  "T = Babby Party");

  Player player;

  while (window.isOpen()){

    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){
        window.close();
      }
      if (event.type == sf::Event::KeyPressed){
        if(event.key.code == sf::Keyboard::Q ||
           event.key.code == sf::Keyboard::W ||
           event.key.code == sf::Keyboard::E ||
           event.key.code == sf::Keyboard::R ||
           event.key.code == sf::Keyboard::T)
        {
          int bearHealth = 420;
          Bear bearList[4];
          Display HUD(window,courierNewBd,courierNew,player,bearList[0]);
          FindBear(event.key.code, HUD, bearList);


          if(BearBattle(HUD, bearHealth)){
            if(event.key.code == sf::Keyboard::Q){winsvBabby++;}
            if(event.key.code == sf::Keyboard::W){winsvBlack++;}
            if(event.key.code == sf::Keyboard::E){winsvBrown++;}
            if(event.key.code == sf::Keyboard::R){winsvPolar++;}
            if(event.key.code == sf::Keyboard::T){winsvParty++;}
          }
          else{
            if(event.key.code == sf::Keyboard::Q){lossesToBabby++;}
            if(event.key.code == sf::Keyboard::W){lossesToBlack++;}
            if(event.key.code == sf::Keyboard::E){lossesToBrown++;}
            if(event.key.code == sf::Keyboard::R){lossesToPolar++;}
            if(event.key.code == sf::Keyboard::T){lossesToParty++;}
          }
          messages.Update("Your Final Health:", player.GetHealth());
          messages.Update("Bear's Final Health:", bearHealth);
          messages.Update("Last Bear Was:", bearList[0]);

          messages.Update("Against Babby:",
          std::to_string(winsvBabby) + "/" +
          std::to_string(winsvBabby + lossesToBabby));
          messages.Update("Against Black:",
          std::to_string(winsvBlack) + "/" +
          std::to_string(winsvBlack + lossesToBlack));
          messages.Update("Against Brown:",
          std::to_string(winsvBrown) + "/" +
          std::to_string(winsvBrown + lossesToBrown));
          messages.Update("Against Polar:",
          std::to_string(winsvPolar) + "/" +
          std::to_string(winsvPolar + lossesToPolar));
          messages.Update("Against Party:",
          std::to_string(winsvParty) + "/" +
          std::to_string(winsvParty + lossesToParty));

          messages.Update("Q = Babby, W = Black",
                          "E = Brown, R = Polar",
                          "T = Babby Party",
                          "D = Dranks, H = Heal");
        }//endif specific key
        else if(event.key.code == sf::Keyboard::D){
          player.Replenish();
          messages.Update("Your Dranks:", 5);
        }
        else if(event.key.code == sf::Keyboard::H){
          player.Heal();
          messages.Update("Your Health:", player.GetHealth());
        }
      }//endif keypress
    }//end while loop

    window.clear();
    messages.draw();
    window.display();
  }
}
