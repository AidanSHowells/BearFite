#ifndef OPTIONS_H
#define OPTIONS_H

#include <SFML/Graphics.hpp>
#include <array>//For std::array
#include "Highlight.h"

/*The OptionsBox class is for listing the options available to the player. When
 *constructed specify the font the titles use and the font everything else uses.
 *Optionally, specify the text displayed, and if the text includes two titles.
 *Public member functions are "GetChoice", which takes an sf::Event argument and
 *returns the index of the option the player picked (zero for nothing), and
 *"Update", which should be called right before the box is drawn and which
 *keeps the highlighting up to date.
 */


class OptionsBox : public sf::Drawable{
  public:
    OptionsBox(sf::Font& titleFont,
               sf::Font& mainFont,
               const std::vector <sf::String>& optionString,
               int listBreakPoint,
               bool boxHasTwoTitles = true);
    int GetChoice(sf::Event theEvent);
    void Update(const sf::Vector2f mousePosition, const bool highlight);
  private:
    const sf::Vector2f position = sf::Vector2f(0,465);
    const sf::Vector2f size = sf::Vector2f(595, 135);
    const float divPosition = 350.0f;
    sf::RectangleShape background;
    sf::RectangleShape divLine;

    static const int maxNumOptions = 8;

    const bool hasTwoTitles;
    const int numOptions;       //Includes the title(s)
    const int sizeOfFirstList;  //Includes the title
    const int sizeOfSecondList; //Includes the second title, if one exists
    const int numHighlightBoxes;

    sf::Text optionsText[maxNumOptions];
    HighlightBox highlightBox[maxNumOptions];

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
