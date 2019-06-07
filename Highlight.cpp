#include "Highlight.h"


HighlightBox::HighlightBox(const sf::FloatRect& rectToHighlight){
  AdjustToFit(rectToHighlight);
  box.setFillColor(sf::Color(255,255,0,153));
}

void HighlightBox::AdjustToFit(const sf::FloatRect& rectToHighlight){
  box.setSize(sf::Vector2f(rectToHighlight.width,rectToHighlight.height));
  box.setPosition(rectToHighlight.left,rectToHighlight.top);
}

void HighlightBox::UpdateState(const sf::Vector2f mouseLocation){
  shouldAppear = box.getGlobalBounds().contains(mouseLocation);
}

bool HighlightBox::Contains(const sf::Vector2f clickLocation) const{
  return box.getGlobalBounds().contains(clickLocation);
}

void HighlightBox::draw(sf::RenderTarget& target, sf::RenderStates states)const{
  if(shouldAppear){
    target.draw(box, states);
  }
}
