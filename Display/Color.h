#ifndef COLOR_H
#define COLOR_H

#include <SFML/Graphics/Color.hpp>

namespace Color{
  static const sf::Color Gray = sf::Color(192,192,192);
  static const sf::Color LightBlue = sf::Color(224,238,224);

  
  static const sf::Color HUDBackground = Gray;//or LightBlue or sf::Color::White
  static const sf::Color PowerPool = sf::Color(235,0,0);
  static const sf::Color Highlight = sf::Color(255,255,0,153);
  static const sf::Color ButtonIndicator = sf::Color(0,220,0);
  static const sf::Color DefaultText = sf::Color::Black;
}

#endif
