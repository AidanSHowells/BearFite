#ifndef ADDSPACE_H
#define ADDSPACE_H

#include <SFML/System/String.hpp>

sf::String AddSpacing(const sf::String& inputString,
                      size_t totalLength,
                      bool addToFront = true);

#endif
