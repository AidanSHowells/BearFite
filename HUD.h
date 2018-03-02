#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>

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
 *Member functions are "draw", which draws the options box to the window,
 *"GetAction", which takes an sf::Event argument and returns an Action if one
 *should occur, and "Highlight", which should be called right before
 *window.display() and which highlights any clickable things that the user is
 *hovering over.
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
               sf::Vector2f theSize = sf::Vector2f(200, 400) );
    //General note: The way to write a sf::Vector2f literal is sf::Vector2f(0,0)

    ~MessageBox();
    void Update(sf::String inputString);
    void Update(sf::String inputString1, sf::String inputString2);
    void Update(sf::String inputString, int imputInt);
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
    Action GetAction(sf::Event theEvent);
    void Highlight();
    void draw();//"Draw" would be consistant with our funcion naming convention,
                //but "draw" is consistant with SFML

  private:
    sf::RenderWindow* window;
    const sf::Vector2f position;
    const sf::Vector2f size;
    const float divPosition;
    sf::RectangleShape background;
    sf::RectangleShape divLine;
    sf::Text punch[4];
    sf::Text notPunch[4];
    sf::FloatRect textBox[6];
};


#endif
