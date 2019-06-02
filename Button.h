#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include "Highlight.h"

class Button : public sf::Drawable{
  public:
    Button();
    void SetText(const sf::Text& theWords);
    bool Contains(const sf::Vector2f clickLocation) const;
    void SetState(const bool isOn){buttonIsOn = isOn;}
    bool IsOn() const {return buttonIsOn;}
    void UpdateHighlighting(const sf::Vector2f mouseLocation);
  private:
    sf::FloatRect hitbox;
    sf::RectangleShape button;
    sf::RectangleShape indicator;
    HighlightBox highlightBox;
    bool buttonIsOn = false;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
