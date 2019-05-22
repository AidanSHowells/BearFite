#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include <array>//For std::array
#include "Messages.h"
#include "Bear.h"

class Player;
enum class TurnOf;
enum class Winner;

/*The main class here (defined last for dependency reasons) is class HUD.
 *An object of this class contains one object corresponding to each piece of the
 *HUD, and is responsible for managing these objects (plus any HUD
 *functionality involving multiple of the objects) so that the the programmer
 *doesn't have to corral all of the objects individually. Member function "draw"
 *draws all member HUD objects to the window. Member function "Highlight"
 *helps indicate to the user what options are available, and hightlights any
 *clickable hitboxes that the user hovers over.
 */

/*The OptionsBox class is for listing the options available to the player. When
 *constructed, specify the window that the font displays in, the font the titles
 *use, and the font everything else uses. Optionally, specify the position and
 *size of the box, as well as the horizontal position of the divider line.
 *Member functions are "draw", which draws the options box to the window,
 *"GetChoice", which takes an sf::Event argument and returns the index of the
 *option the player picked (zero for nothing), and "Highlight", which should be
 *called right before window.display() and which highlights any clickable things
 *that the user is hovering over.
 */

/*The PlayerStats class is for displaying the stats of the player. When
 *constructed, specify the window that the font displays in, the font the title
 *uses, the font everything else uses, and the player whose stats are being
 *displayed. Optionally, specify the position and size of the box. //FINISH
 *
 */

/*The BearStats class is for displaying the stats of the bear. When
 *constructed, specify the window that the font displays in, the font the title
 *uses, the font everything else uses, and the bear whose stats are being
 *displayed. Optionally, specify the position and size of the box. Member
 *function "draw" draws the object to the window. Member function "Update"
 *updates the displayed stats of the bear. Note that as currently constructed
 *(with default size) the bear's health can be at most 9,999,999.
 */


class OptionsBox{
  public:
    OptionsBox(sf::RenderWindow& theWindow,
               sf::Font& titleFont,
               sf::Font& mainFont,
               const std::array <sf::String, 8>& optionString
                 = {"PUNCH:Where Punch Bear?","1:Leg","2:Eye","3:John Hopkins",
                    "ELSE:What Do?","4:Quaff Drank","5:Cast Spell","6:Flee"},
               bool boxHasTwoTitles = true);
    int GetChoice(sf::Event theEvent);
    void Highlight();
    void draw();//See comment in MessageBox
  private:
    sf::RenderWindow* window;
    const sf::Vector2f position = sf::Vector2f(0,465);
    const sf::Vector2f size = sf::Vector2f(595, 135);
    const float divPosition = 350.0f;
    sf::RectangleShape background;
    sf::RectangleShape divLine;

    static const int maxNumOptions = 8;

    const bool hasTwoTitles;
    const int sizeOfFirstList;  //Includes the title
    const int sizeOfSecondList; //Includes the second title, if one exists
    const int numOptions;       //Includes the title(s)
    const int numHighlightBoxes;

    sf::Text optionsText[maxNumOptions];
    sf::FloatRect highlightBox[maxNumOptions];
};


class BearStats{
  public:
    BearStats();
    BearStats(sf::RenderWindow& theWindow,
              sf::Font& titleFont,
              sf::Font& mainFont,
              Bear theBear,
              bool titleBar = true,
              sf::Vector2f thePosition = sf::Vector2f(205, 0),
              sf::Vector2f theSize = sf::Vector2f(390, 23) );//48 if hasTitleBar
    void Update();
    void SetBear(const Bear& theNewBear);
    Bear* GetBearPtr();
    bool GetShouldAppear();
    void SetShouldAppear(bool shouldBearAppear);
    sf::Vector2f GetNameBoxPosition();
    sf::Vector2f GetNameBoxSize();
    void draw();//See comment in MessageBox
  private:
    sf::RenderWindow* window;
    Bear bear;
    const sf::Vector2f position;
    const sf::Vector2f size;

    static const int numBackground = 3;
    static const int numBearInfo = 6;
    sf::RectangleShape background[numBackground];
    sf::Text bearInfo[numBearInfo];

    bool hasTitleBar;
    bool shouldAppear = false;
};


class PlayerStats{
  public:
    PlayerStats(sf::RenderWindow& theWindow,
              sf::Font& titleFont,
              sf::Font& mainFont,
              Player& thePlayer,
              sf::Vector2f thePosition = sf::Vector2f(600, 0),
              sf::Vector2f theSize = sf::Vector2f(200, 580) );
    void Update();
    bool SpellChoiceProcessStarted(MessageBox& messages);
    int GetSpell(const sf::Event theEvent);
    void HighlightSpells(bool isPickingSpell);
    void draw();//See comment in MessageBox
    enum getSpellResult{noChoice = -1, changedMindAboutCasting = -2};
  private:
    sf::RenderWindow* window;
    Player* player;
    const sf::Vector2f position;
    const sf::Vector2f size;
    sf::RectangleShape background;
    sf::RectangleShape moreBackground;
    int selectedSpellIndex;
    bool onMainMenu = true;
    int numReservedSpellTrees = 4;

    static const int numHealth = 4;
    static const int numAbility = 13;
    static const int maxSpells = 22;
    static const int numDivLine = 7;

    sf::Text header;
    sf::Text health[numHealth];
    sf::Text ability[numAbility];
    sf::Text featsHeader;
    sf::Text spell[maxSpells];
    float baseSpellHeight[maxSpells];
    sf::FloatRect highlightBox[maxSpells];
    sf::RectangleShape divLine[numDivLine];
    sf::Text moreStats;
};


class HUD{
  public:
    HUD(sf::RenderWindow& theWindow,
            sf::Font& titleFont,
            sf::Font& mainFont,
            Player& thePlayer);
    MessageBox messages;
    OptionsBox options;
    PlayerStats playerStats;
    sf::RenderWindow* GetWindowPtr(){return window;}
    Player* GetPlayerPtr(){return player;}
    //void ProcessInput();
    void draw();

  protected:
    sf::RenderWindow* window;
    Player* player;

  private:
    void Highlight();
};


class BattleHUD : public HUD{
  public:
    BattleHUD(sf::RenderWindow& theWindow,
              sf::Font& titleFont,
              sf::Font& mainFont,
              Player& thePlayer,
              const Bear& theBear);
    BearStats bearStats[5];
    Bear* GetBearPtr(){return bear;}
    std::vector<Bear*> GetAllEnemyBears();
    int GetNumBears();//The number of bears that exist
    void AddEnemyBears(std::vector<Bear>& bears);
    void RemoveDeadCombatants(Winner& theWinner);//Updates theWinner
    //void AddFriendBear(Bear* friendBearPtr);
    TurnOf TakeAction(sf::Event theEvent);
    void draw();

  private:
    Bear* bear;//A pointer to the bear currently being targeted
    void Highlight();
    int TargetBearIndex();
    bool isPickingSpell = false;//The behavior of Hightlight changes based on
                                //whether the user is picking spells or not
};


#endif
