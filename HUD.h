#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include <array>//For std::array
#include "Messages.h"
#include "Bear.h"
#include "Highlight.h"
#include "Button.h"

class Player;
enum class TurnOf;
enum class Winner;

/*The main class here (defined last for dependency reasons) is class HUD.
 *An object of this class contains one object corresponding to each piece of the
 *HUD, and is responsible for managing these objects (plus any HUD
 *functionality involving multiple of the objects) so that the the programmer
 *doesn't have to corral all of the objects individually. Public member function
 *"Update" makes sure all the information to display is up to date. It takes a
 *boolean which updates whether the player is allowed to select from the
 *options. Always call Update before drawing the HUD. BattleHUD is a type of HUD
 *(read: derived class) which includes bear information and is used for battles.
 */

/*The OptionsBox class is for listing the options available to the player. When
 *constructed, specify the window that the font displays in, the font the titles
 *use, and the font everything else uses. Optionally, specify the position and
 *size of the box, as well as the horizontal position of the divider line.
 *Public member functions "GetChoice", which takes an sf::Event argument and
 *returns the index of the option the player picked (zero for nothing), and
 *"Highlight", which should be called after the box has been drawn and which
 *highlights any clickable things that the user is hovering over.
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
 *displayed. Optionally, specify the position and size of the box. //FINISH
 *
 */


class OptionsBox : public sf::Drawable{
  public:
    OptionsBox(sf::RenderWindow& theWindow,
               sf::Font& titleFont,
               sf::Font& mainFont,
               const std::array <sf::String, 8>& optionString
                 = {"PUNCH:Where Punch Bear?","1:Leg","2:Eye","3:John Hopkins",
                    "ELSE:What Do?","4:Quaff Drank","5:Cast Spell","6:Flee"},
               bool boxHasTwoTitles = true);
    int GetChoice(sf::Event theEvent);
    void Highlight() const;
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

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


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
    sf::Vector2f GetNameBoxPosition() const;
    sf::Vector2f GetNameBoxSize() const;
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


class PlayerStats : public sf::Drawable{
  public:
    PlayerStats(sf::RenderWindow& theWindow,
              sf::Font& titleFont,
              sf::Font& mainFont,
              Player& thePlayer,
              sf::Vector2f thePosition = sf::Vector2f(600, 0),
              sf::Vector2f theSize = sf::Vector2f(200, 580) );
    void Update();
    bool SpellChoiceProcessStarted(MessageBox& messages);
    void ToggleMenu(const sf::Event event);
    void ToggleFeats(const sf::Event event);
    int GetSpell(const sf::Event theEvent);
    void Highlight(bool isPickingSpell, bool canCastSpells) const;
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

    static const int numHealth = 16;
    static const int numAbility = 13;
    static const int maxSpells = 22;
    static const int numExtraFeats = 4;
    static const int numDivLine = 7;

    sf::Text header;
    sf::Text health[numHealth];
    sf::Text ability[numAbility];
    float baseAbilityHeight[numAbility];
    sf::Text featsHeader;
    sf::Text spell[maxSpells];
    Button button[maxSpells];
    sf::Text feats[numExtraFeats];
    float baseSpellHeight[maxSpells];
    sf::FloatRect highlightBox[maxSpells];
    sf::RectangleShape divLine[numDivLine];
    sf::Text moreStats;
    sf::FloatRect moreHighlightBox;

    int GetFeatStartingIndex() const {return(3 * numReservedSpellTrees + 1);}
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


class HUD : public sf::Drawable{
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

  protected:
    sf::RenderWindow* window;
    Player* player;
};


class BattleHUD : public HUD{
  public:
    BattleHUD(sf::RenderWindow& theWindow,
              sf::Font& titleFont,
              sf::Font& mainFont,
              Player& thePlayer,
              const std::array<Bear,4>& bears);
    BearStats bearStats[4];
    BearStats friendBearStats;
    Bear* GetBearPtr(){return bearStats[targetBearIndex].GetBearPtr();}
    std::vector<Bear*> GetAllEnemyBears();
    int GetNumEnemyBears() const;
    void RemoveDeadCombatants(Winner& theWinner);//Updates theWinner
    //void AddFriendBear(Bear* friendBearPtr);
    TurnOf TakeAction(sf::Event theEvent);
    void Update(bool optionsAvailable);

  private:
    int targetBearIndex = 0;
    bool canPickFromOptions = true;
    bool isPickingSpell = false;//The behavior of Hightlight changes based on
                                //whether the user is picking spells or not

    void Highlight() const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif
