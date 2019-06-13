#ifndef BEARSTATS_H
#define BEARSTATS_H

#include <SFML/Graphics.hpp>
#include "Bear.h"
#include "Display/Highlight.h"

/*The BearStats class is for displaying the stats of the bear. When
 *constructed, specify the font the title uses, the font everything else uses,
 *and the bear whose stats are being displayed. Optionally, specify the position
 *and size of the box. //FINISH
 *
 */

class BearStats : public sf::Drawable{
  public:
    BearStats();
    BearStats(sf::Font& titleFont,
              sf::Font& mainFont,
              Bear theBear,
              bool titleBar = true,
              sf::Vector2f thePosition = sf::Vector2f(205, 0),
              sf::Vector2f theSize = sf::Vector2f(390, 23) );//48 if hasTitleBar
    void Update();
    void SetBear(const Bear& theNewBear);
    Bear* GetBearPtr();
    bool GetShouldAppear() const;
    void SetShouldAppear(bool shouldBearAppear);
    sf::FloatRect GetNameBox() const {return bearInfo[1].getGlobalBounds();}
  private:
    Bear bear;
    const sf::Vector2f position;
    const sf::Vector2f size;

    static const int numBackground = 3;
    static const int numBearInfo = 6;
    sf::RectangleShape background[numBackground];
    sf::Text bearInfo[numBearInfo];

    bool hasTitleBar;
    bool shouldAppear = false;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
