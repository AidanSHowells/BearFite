#include "Button.h"

sf::Color LightGreen = sf::Color(0,220,0);

Button::Button(){
  indicator.setSize(sf::Vector2f(9,9));
  indicator.setFillColor(LightGreen);

  button.setSize(sf::Vector2f(13,13));
  button.setFillColor(sf::Color::Black);
}

void Button::SetText(const sf::Text& words){
  sf::FloatRect hitbox = words.getGlobalBounds();
  button.setPosition(hitbox.left + hitbox.width, hitbox.top);
  indicator.setPosition(hitbox.left + hitbox.width + 2, hitbox.top + 2);

  sf::FloatRect box = button.getGlobalBounds();
  hitbox.width = box.left + box.width - hitbox.left +2;
  hitbox.height = std::max(hitbox.height, box.top + box.height - hitbox.top) +1;

  highlightBox.AdjustToFit(hitbox);
}

bool Button::Contains(const sf::Vector2f clickLocation) const {
  return highlightBox.Contains(clickLocation);
}

void Button::UpdateHighlighting(const sf::Vector2f mouseLocation){
  highlightBox.UpdateState(mouseLocation);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const{
  target.draw(button, states);
  if(buttonIsOn){
    target.draw(indicator, states);
  }
  target.draw(highlightBox);
}
