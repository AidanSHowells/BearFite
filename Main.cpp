#include <SFML/Graphics.hpp>

/*We might want to be using "https://github.com/TankOs/SFGUI" instead of
 *the hacky bullshit I implemented for the buttons. I'm worried about function
 *over form for the moment.
 */

/*If we decide not to do the above, someone on the forums had a good idea about
 *buttons: "Well, i would do it with rectangleshapes. You got an image file that
 *contains for example 3 states of the button: not clicked, mouse over and
 *clicked. For every event you set the rectangleshape."
 */

int main(){
  //Declare variables
  bool onSplashPage = true;

  // create the window
  sf::RenderWindow mainWindow(sf::VideoMode(849, 637), "BearFite",sf::Style::Titlebar | sf::Style::Close);

  /*Another option for the above is the following, which allows for changing
   *the size of the window:
   *sf::RenderWindow mainWindow(sf::VideoMode(849, 637), "BearFite");
   *If we decide to go this route, we'll need to put some of the stuff below
   *inside of the first while loop (probably clear, draw, and display).
   */

  //Load the font
  sf::Font courierNew;
  if (!courierNew.loadFromFile("Resources/cour.ttf")){
    return EXIT_FAILURE;
  }

  //Load the splash page
  sf::Texture longTexture;
  if(!longTexture.loadFromFile("Resources/SplashPage.png")){
    return EXIT_FAILURE;
  }
  sf::Sprite splashPage;
  splashPage.setTexture(longTexture);

  // clear the window with black color
  mainWindow.clear(sf::Color::Black);

  //Draw the bears
  mainWindow.draw(splashPage);

  //Display
  mainWindow.display();

  // run the program as long as the window is open
  while (mainWindow.isOpen() && onSplashPage){
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (mainWindow.pollEvent(event)){
      //If they click (with any button), we leave the splash page
      if (event.type == sf::Event::MouseButtonPressed){
        onSplashPage = false;
      }
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed){
        mainWindow.close();
      }
    }
  }
  // clear the window with black color
  mainWindow.clear(sf::Color::Black);

  //Make ze rectangle
  sf::RectangleShape textRect(sf::Vector2f(250, 50));
  textRect.setFillColor(sf::Color(192,192,192));//Set the color
  textRect.setPosition(300, 300);//Move (to the middle, for the moment)
  sf::FloatRect textBox = textRect.getGlobalBounds();//bounding box for textRect

  //Make some text
  sf::Text myText;
  myText.setFont(courierNew);//Select the font
  myText.setString("Click to Start");//Set the string to display
  myText.setCharacterSize(24);//Set the character size (in pixels, not points!)
  myText.setFillColor(sf::Color::Red);//Set the color
  myText.setPosition(310, 305);//Move it into the center of textRect

  //Display the current frame
  mainWindow.draw(textRect);
  mainWindow.draw(myText);
  mainWindow.display();

  while (mainWindow.isOpen()){
    sf::Event event;
    while (mainWindow.pollEvent(event)){
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed){
        mainWindow.close();
      }
      if (event.type == sf::Event::MouseButtonPressed){
        //create a 2 dimensional vector, and check if it's in the box
        sf::Vector2f click(event.mouseButton.x, event.mouseButton.y);
        if(textBox.contains(click)){
          //launch BearFite
        }
      }
    }
  }

  return 0;
}
