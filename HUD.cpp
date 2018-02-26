#include <SFML/Graphics.hpp>
#include <string>//For std::to_string


/*Eventually, there is going to be a base class "HUD" from which all other
 *classes in this file are derived.
 */

/*The MessageBox class is for boxes displaying messages to the player. When
 *constructed, specify the window that the font displays in, the font the title
 *uses, the font everything else uses, and the title itself. Optionally, specify
 *the position and size of the box. Member functions are "Update", which takes a
 *string and makes it the first message displayed (shifting everything else down
 *one), and "draw", which draws the message box to the window.
 */

/*The OptionsBox class is for listing the options available to the player. When
 *constructed, specify the window that the font displays in, the font the titles
 *use, and the font everything else uses. Optionally, specify the position and
 *size of the box, as well as the horizontal position of the divider line.
 *Member function is "draw", which draws the options box to the window.
 */




/*Why force the person creating a HUD object to provide fonts? Two reasons.
 *First, constructors can't return values, so I can't tell the constructor to
 *return an error code if the font fails to load. This makes it harder to fail
 *gracefully. Second, it's not as simple as loading fonts in the constructor
 *and assigning them to the text. From the "sf::Font" documentation: "It is
 *important to note that the sf::Text instance doesn't copy the font that it
 *uses, it only keeps a reference to it. Thus, a sf::Font must not be destructed
 *while it is used by a sf::Text (i.e. never write a function that uses a local
 *sf::Font instance for creating a text)."
 */


//Note that if the message box has a width of 200, one can fit 22 characters


//This should eventually end up in HUD.cpp (as opposed to in HUD.h)
//I use upper case to be consistant with SFML
sf::Color Gray = sf::Color(192,192,192);


class MessageBox{
  public:
    MessageBox(sf::RenderWindow& theWindow,
               sf::Font& titleFont,
               sf::Font& mainFont,
               sf::String theTitle,
               sf::Vector2f thePosition = sf::Vector2f(0,0),
               sf::Vector2f theSize = sf::Vector2f(200, 400) );
    //General note: The way to write a sf::Vector2f literal is sf::Vector2f(0,0)

    ~MessageBox();
    void Update(sf::String inputString);//With a width of 200, you can fit 22
                                        //characters (counting leading '>')
    void draw();//"Draw" would be consistant with our funcion naming convention,
                //but "draw" is consistant with SFML

  private:
    sf::RenderWindow* window;
    const sf::Vector2f position;
    const sf::Vector2f size;
    const int numLines;
    sf::Text* line = new sf::Text[numLines];
    sf::RectangleShape background;

};


class OptionsBox{
  public:
    OptionsBox(sf::RenderWindow& theWindow,
               sf::Font& titleFont,
               sf::Font& mainFont,
               sf::Vector2f thePosition = sf::Vector2f(0,405),
               sf::Vector2f theSize = sf::Vector2f(800, 195),
               float dividerPosition = 420 );
    void draw();//"Draw" would be consistant with our funcion naming convention,
                //but "draw" is consistant with SFML

  private:
    sf::RenderWindow* window;
    const sf::Vector2f position;
    const sf::Vector2f size;
    const float divPosition;
    sf::RectangleShape background;
    sf::RectangleShape divLine;
    sf::Text punchTitle;
    sf::Text punch[3];
    sf::Text notPunchTitle;
    sf::Text notPunch[3];
};


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
  numLines(int(theSize.y) / 20)//My guess is that the number of lines of text
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
  line[1].setString(inputString);
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
  punchTitle.setFont(titleFont);
  punchTitle.setString("PUNCH:Where Punch Bear?");
  punchTitle.setCharacterSize(30);
  punchTitle.setFillColor(sf::Color::Black);
  punchTitle.setPosition(position.x, position.y);

  //Make the first set of options
  for(int i = 0; i < 3; i++){
    punch[i].setFont(mainFont);
    punch[i].setCharacterSize(30);
    punch[i].setFillColor(sf::Color::Black);
    punch[i].setPosition(position.x, position.y + 30 * (i + 1) );
  }
  punch[0].setString("1:Leg");
  punch[1].setString("2:Eye");
  punch[2].setString("3:John Hopkins");

  //Make the second title
  notPunchTitle.setFont(titleFont);
  notPunchTitle.setString("NOT PUNCH:What Do?");
  notPunchTitle.setCharacterSize(30);
  notPunchTitle.setFillColor(sf::Color::Black);
  notPunchTitle.setPosition(divPosition + 10, position.y);

  //Make the second set of options
  for(int i = 0; i < 3; i++){
    notPunch[i].setFont(mainFont);
    notPunch[i].setCharacterSize(30);
    notPunch[i].setFillColor(sf::Color::Black);
    notPunch[i].setPosition(divPosition + 10, position.y + 30 * (i + 1) );
  }
  notPunch[0].setString("4:Quaff Drank");
  notPunch[1].setString("5:Cast Spell");
  notPunch[2].setString("6:Flee");
}

void OptionsBox::draw(){
  //Recall that a->b is equivalent to (*a).b
  window -> draw(background);
  window -> draw(divLine);
  window -> draw(punchTitle);
  for(int i = 0; i < 3; i++){
    window -> draw(punch[i]);
  }
  window -> draw(notPunchTitle);
  for(int i = 0; i < 3; i++){
    window -> draw(notPunch[i]);
  }
}


//The main function is temporary; it makes testing features easier
int main(){

  //Declare some strings
  sf::String TEMP[4];
  TEMP[0] = ">Carp, You miss.";
  TEMP[1] = ">You got bear for 69";
  TEMP[2] = ">Bear spare you.";
  TEMP[3] = ">Bear bash you for 69";


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


  while (window.isOpen()){
    sf::Event event;
    while (window.pollEvent(event)){
      if (event.type == sf::Event::Closed){
        window.close();
      }
      if (event.type == sf::Event::KeyPressed){
        if (event.key.code == sf::Keyboard::Num0 || event.key.code == sf::Keyboard::Numpad0){
          messages.Update(TEMP[0]);
        }
        if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1){
          messages.Update(TEMP[1]);
        }
        if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2){
          messages.Update(TEMP[2]);
        }
        if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3){
          messages.Update(TEMP[3]);
        }
      }
    }

    window.clear();
    messages.draw();
    options.draw();
    window.display();
  }

  return 0;
}
