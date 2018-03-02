#include "HUD.h"
#include <string>//For std::to_string

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
  sf::Vector2f thePosition,
  sf::Vector2f theSize
):
  window(&theWindow),
  position(thePosition),
  size(theSize),
  numLines(int(theSize.y / 20))//My guess is that the number of lines of text
  //displayed should be the integer part of size.y/20. Fix it if you disagree
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

MessageBox::~MessageBox(){delete[] line;}

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
  line[1].setString(sf::String("  ") += inputString2);

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

  //line[1].setString(sf::String("  ") += sf::String(std::to_string(imputInt)));

  //Now move everything down one again and make the top line inputString
  Update(inputString);
}

void MessageBox::draw(){
  window -> draw(background);//Recall that -> is a member access operator.
                             //In particular, a->b is equivalent to (*a).b
  for(int i = 0; i < numLines; i++){
    window -> draw(line[i]);
  }
}

OptionsBox::OptionsBox(
  sf::RenderWindow& theWindow,
  sf::Font& titleFont,
  sf::Font& mainFont,
  sf::Vector2f thePosition,
  sf::Vector2f theSize,
  float dividerPosition
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



//The main function and these include statements are temporary; they make it
//easier to test new features
#include "Player.h"
#include "Bear.h"

int main(){


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

  //Create the dialog box
  MessageBox messages(window,courierNewBd,courierNew,"Messages:");

  //Create the options box
  OptionsBox options(window,courierNewBd,courierNew);

  //Make the player and bear
  Player player(messages);
  Bear bear(messages);


  while (window.isOpen()){
    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){
        window.close();
      }
      if (event.type == sf::Event::KeyPressed ||
          event.type == sf::Event::MouseButtonPressed)
      {
        player.TakeAction(options.GetAction(event), bear);
      }

    }


    //Order is important here
    window.clear();
    messages.draw();
    options.draw();
    options.Highlight();
    window.display();
  }

  return 0;
}
