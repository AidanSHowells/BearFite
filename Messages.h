#ifndef MESSAGES_H
#define MESSAGES_H

#include <SFML/Graphics.hpp>

/*The MessageBox class is for boxes displaying messages to the player. When
 *constructed, specify the window that the font displays in, the font the title
 *uses, the font everything else uses, and the title itself. Optionally, specify
 *the position and size of the box. Member functions are "Update", which takes a
 *string and makes it the first message displayed (more details below), and
 *"draw", which draws the message box to the window.
 */

class Bear;

//TEMP: These belong ... somewhere else. No sure where, honestly
enum class Action {nothing, leg, eye, john_hopkins, quaff, cast, flee};
enum class TurnOf {player, bear, neither};

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
    void Update(const sf::String& inputString,
                bool makeLine = false);//Details of Update below
    void Update(const sf::String& inputString1,
                const sf::String& inputString2,
                bool makeLine = false);
    void Update(const sf::String& inputString1,
                const sf::String& inputString2,
                const sf::String& inputString3);
    void Update(const sf::String& inputString1,
                const sf::String& inputString2,
                const sf::String& inputString3,
                const sf::String& inputString4);
    void Update(const sf::String& inputString1,
                const sf::String& inputString2,
                const sf::String& inputString3,
                const sf::String& inputString4,
                const sf::String& inputString5);
    void Update(const sf::String& inputString1,
                const sf::String& inputString2,
                const sf::String& inputString3,
                const sf::String& inputString4,
                const sf::String& inputString5,
                const sf::String& inputString6);
    void Update(const sf::String& inputString,
                int inputInt,
                bool makeLine = false);
    void Update(const sf::String& inputString, const Bear& inputBear);
    //void Update(sf::String inputString, Bear inputBear, Status inputStatus);
    void draw();//"Draw" would be consistant with our funcion naming convention,
                //but "draw" is consistant with SFML

  private:
    sf::RenderWindow* window;
    const sf::Vector2f position;
    const sf::Vector2f size;
    static const int numLines = 23;
    static const int numDivLines = numLines - 2;
    sf::Text line[numLines];
    sf::RectangleShape divLine[numDivLines];
    bool displayDivLine[numDivLines];
    //sf::Text* line = new sf::Text[numLines];
    sf::RectangleShape background;
    void SetTopString(const sf::String& inputString, bool makeLine = false);
    sf::String markChar = ">";
};

/*MessageBox::Update can take a single sf::String, add a '>' to the front, and
 *make that sf::String the first thing displayed in the message box. Given extra
 *arguments, it adds those to the dispay as well, each argument below the
 *arguments listed before it. If a later argument is a sf::String, it gets a
 *space prepended. If it is an int, it is right aligned, and if it is a object
 *of class Bear, the bear's name is displayed (right aligned).
 */

#endif
