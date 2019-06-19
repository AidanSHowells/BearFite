#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include <array>//For std::array
#include <vector>
#include "Display/Messages.h"
#include "Display/Options.h"
#include "BearStats.h"
#include "PlayerStats.h"
#include "Bear.h"
#include "Display/Highlight.h"

class Player;
enum class TurnOf;
enum class Winner;

/*A HUD object contains one object corresponding to each piece of the
 *HUD, and is responsible for managing these objects (plus any HUD
 *functionality involving multiple of the objects) so that the the programmer
 *doesn't have to corral all of the objects individually. Public member function
 *"Update" makes sure all the information to display is up to date. It takes a
 *boolean which updates whether the player is allowed to select from the
 *options, and the position of the mouse in sf::Vector2f form. Always call
 *Update right before drawing the HUD. BattleHUD is a type of HUD (read: derived
 *class) which includes bear information and is used for battles.
 */

class HUD : public sf::Drawable{
  public:
    HUD(sf::Font& titleFont,
        sf::Font& mainFont,
        Player& thePlayer,
        const std::vector <sf::String>& optionString,
        int optionsListBreakPoint,
        bool optionsHaveTwoTitles = true,
        bool battleMode = false);
    MessageBox messages;
    OptionsBox options;
    PlayerStats playerStats;

    Player* GetPlayerPtr(){return player;}
    void Update(const sf::Vector2f mousePos, const bool optionsAvailable);

  protected:
    Player* player;

  private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


class BattleHUD : public HUD{
  public:
    BattleHUD(sf::Font& titleFont,
              sf::Font& mainFont,
              Player& thePlayer,
              const std::array<Bear,4>& bears);
    BearStats bearStats[4];
    BearStats friendBearStats;
    Bear* GetBearPtr(){return bearStats[targetBearIndex].GetBearPtr();}
    std::vector<Bear*> GetAllEnemyBears();
    int GetNumEnemyBears() const;
    int RemoveDeadCombatants(Winner& winner);//Updates winner; returns dranks
    //void AddFriendBear(Bear* friendBearPtr);
    TurnOf TakeAction(sf::Event theEvent);
    void Update(const sf::Vector2f mousePos, const bool optionsAvailable);

  private:
    int targetBearIndex = 0;
    bool canPickFromOptions = true;
    bool isPickingSpell = false;
    HighlightBox bearHighlight;

    void Highlight() const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};


#endif
