#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>

class Bear;
class Player;

/*The main class here (defined last for dependency reasons) is class Display.
 *An object of this class contains one object corresponding to each piece of the
 *HUD, and is responsible for managing these objects (plus any HUD
 *functionality involving multiple of the objects) so that the the programmer
 *doesn't have to corral all of the objects individually. Member function "draw"
 *draws all member HUD objects to the window. Member function "Highlight"
 *helps indicate to the user what options are available, and hightlights any
 *clickable hitboxes that the user hovers over.
 */

/*The MessageBox class is for boxes displaying messages to the player. When
 *constructed, specify the window that the font displays in, the font the title
 *uses, the font everything else uses, and the title itself. Optionally, specify
 *the position and size of the box. Member functions are "Update", which takes a
 *string and makes it the first message displayed (more details below), and
 *"draw", which draws the message box to the window.
 */

/*The OptionsBox class is for listing the options available to the player. When
 *constructed, specify the window that the font displays in, the font the titles
 *use, and the font everything else uses. Optionally, specify the position and
 *size of the box, as well as the horizontal position of the divider line.
 *Member functions are "draw", which draws the options box to the window,
 *"GetAction", which takes an sf::Event argument and returns an Action if one
 *should occur, and "Highlight", which should be called right before
 *window.display() and which highlights any clickable things that the user is
 *hovering over.
 */

/*The PlayerStats class is for displaying the stats of the player. When
 *constructed, specify the window that the font displays in, the font the title
 *uses, the font everything else uses, and the player whose stats are being
 *displayed. Optionally, specify the position and size of the box. //FINISH
 *
 */

/*The BearStats class is for displaying the stats of the bear. When
 *constructed, specify the window that the font displays in, the font the title
 *uses, the font everything else uses, and the bear whose stats are being
 *displayed. Optionally, specify the position and size of the box. Member
 *function "draw" draws the object to the window. Member function "Update"
 *updates the displayed stats of the bear. Note that as currently constructed
 *(with default size) the bear's health can be at most 9,999,999.
 */

enum class Action {nothing, leg, eye, john_hopkins, quaff, cast, flee};



//Note that if the message box has a width of 200, one can fit 22 characters
class MessageBox{
  public:
    MessageBox(sf::RenderWindow& theWindow,
               sf::Font& titleFont,
               sf::Font& mainFont,
               sf::String theTitle,
               sf::Vector2f thePosition = sf::Vector2f(0,0),
               sf::Vector2f theSize = sf::Vector2f(200, 460) );
    //~MessageBox();//Removed since line[] is no longer dynamically allocated
    void Update(sf::String inputString);//Details of Update below
    void Update(sf::String inputString1, sf::String inputString2);
    void Update(sf::String inputString, int imputInt);
    //void Update(sf::String inputString, Bear imputBear, Status imputStatus);
    void draw();//"Draw" would be consistant with our funcion naming convention,
                //but "draw" is consistant with SFML

  private:
    sf::RenderWindow* window;
    const sf::Vector2f position;
    const sf::Vector2f size;
    static const int numLines = 23;
    sf::Text line[numLines];
    //sf::Text* line = new sf::Text[numLines];
    sf::RectangleShape background;
};

/*MessageBox::Update can take a single sf::String, add a '>' to the front, and
 *make that sf::String the first thing displayed in the message box. Given extra
 *arguments, it adds those to the dispay as well, each argument below the
 *arguments listed before it. If the second argument is a sf::String, it gets a
 *space prepended. If it is an int, it is right aligned, and if it is a object
 *of class Bear, the bear's name is displayed (right aligned).
 */


class OptionsBox{
  public:
    OptionsBox(sf::RenderWindow& theWindow,
               sf::Font& titleFont,
               sf::Font& mainFont,
               sf::Vector2f thePosition = sf::Vector2f(0,465),
               sf::Vector2f theSize = sf::Vector2f(595, 135),
               float dividerPosition = 350.0f );
    Action GetAction(sf::Event theEvent);
    void Highlight();
    void draw();//See comment in MessageBox
  private:
    sf::RenderWindow* window;
    const sf::Vector2f position;
    const sf::Vector2f size;
    const float divPosition;
    sf::RectangleShape background;
    sf::RectangleShape divLine;

    static const int numPunch = 4;
    static const int numNotPunch = 4;
    static const int numTextBox = numPunch + numNotPunch - 2;//-2 for the headers

    sf::Text punch[numPunch];
    sf::Text notPunch[numNotPunch];
    sf::FloatRect textBox[numTextBox];
};


class BearStats{
  public:
    BearStats(sf::RenderWindow& theWindow,
              sf::Font& titleFont,
              sf::Font& mainFont,
              Bear& theBear,
              sf::Vector2f thePosition = sf::Vector2f(205, 0),
              sf::Vector2f theSize = sf::Vector2f(390, 50) );
    void Update();
    void draw();//See comment in MessageBox
  private:
    sf::RenderWindow* window;
    Bear* bear;
    const sf::Vector2f position;
    const sf::Vector2f size;

    static const int numBackground = 3;
    static const int numBearInfo = 6;

    sf::RectangleShape background[numBackground];
    sf::Text bearInfo[numBearInfo];
};


class PlayerStats{
  public:
    PlayerStats(sf::RenderWindow& theWindow,
              sf::Font& titleFont,
              sf::Font& mainFont,
              Player& thePlayer,
              sf::Vector2f thePosition = sf::Vector2f(600, 0),
              sf::Vector2f theSize = sf::Vector2f(200, 600) );
    //void Update();
    void draw();//See comment in MessageBox
  private:
    sf::RenderWindow* window;
    Player* player;
    const sf::Vector2f position;
    const sf::Vector2f size;
    sf::RectangleShape background;

    static const int numHealth = 6;
    static const int numAbility = 13;
    static const int numSpell = 43;
    static const int numDivLine = 7;

    sf::Text header;
    sf::Text health[numHealth];
    sf::Text ability[numAbility];
    sf::Text spell[numSpell];
    sf::RectangleShape divLine[numDivLine];
};


class Display{
  public:
    Display(sf::RenderWindow& theWindow,
            sf::Font& titleFont,
            sf::Font& mainFont,
            Player& thePlayer,
            Bear& theBear);
    MessageBox messages;
    OptionsBox options;
    PlayerStats playerStats;
    BearStats bearStats;
    void draw();
    Action GetAction(sf::Event theEvent);
    //void Highlight();//This should eventually be in charge of all highlighting

  private:
    sf::RenderWindow* window;
    Player* player;
    Bear* bear;
    bool isPickingSpell = false;//The behavior of Hightlight changes based on
                                //whether the user is picking spells or not
};


#endif
