#include <iostream>
#include "AddSpace.h"

sf::String AddSpacing(const sf::String& inputString,
                      size_t totalLength,
                      bool addToFront)
{
  sf::String spacing = "";
  if(totalLength < inputString.getSize()){
    std::cerr << "Warning! ";
    std::cerr << "AddSpacing was told to add spacing to make the string ";
    std::cerr << "\"" << std::string(inputString) << "\" " << totalLength;
    std::cerr << " characters long, which may cause issues.\n\n";
  }
  else{
    for(size_t i = 0; i < totalLength - inputString.getSize(); i++){
      spacing += sf::String(" ");
    }
  }
  if(addToFront){
    return(spacing + inputString);
  }
  else{
    return(inputString + spacing);
  }
}
