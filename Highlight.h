#ifndef HIGHLIGHT_H
#define HIGHLIGHT_H

#include <SFML/Graphics.hpp>

class HighlightBox : public sf::Drawable{
  public:
    HighlightBox(const sf::FloatRect& rectToHighlight = sf::FloatRect(0,0,0,0));
    void AdjustToFit(const sf::FloatRect& rectToHighlight);
    void AppearIfContains(sf::Vector2f mouseLocation);
  private:
    sf::RectangleShape box;
    bool shouldAppear = false;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
