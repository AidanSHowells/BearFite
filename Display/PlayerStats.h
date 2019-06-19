#ifndef PLAYERSTATS_H
#define PLAYERSTATS_H

#include <SFML/Graphics.hpp>
#include "Display/Messages.h"
#include "Display/Highlight.h"
#include "Display/Button.h"

class Player;

/*The PlayerStats class is for displaying the stats of the player. When
 *constructed, specify the font the title uses, the font everything else uses,
 *and the player whose stats are being displayed. Optionally, specify the
 *position and size of the box. //FINISH
 *
 */


class PlayerStats : public sf::Drawable{
  public:
    PlayerStats(sf::Font& titleFont,
                sf::Font& mainFont,
                Player& thePlayer,
                sf::Vector2f thePosition = sf::Vector2f(600, 0),
                sf::Vector2f theSize = sf::Vector2f(200, 580) );
    void Update(const sf::Vector2f mousePos,
                const bool isPickingSpell,
                const bool canCastSpells);
    bool SpellChoiceProcessStarted(MessageBox& messages);
    void ToggleMenu(const sf::Event event);
    void ToggleFeats(const sf::Event event);
    bool GetSpell(const sf::Event theEvent, int& index);//true=spell, false=feat
    enum getSpellResult{noChoice = -1, changedMindAboutCasting = -2};
  private:
    Player* player;
    const sf::Vector2f position;
    const sf::Vector2f size;
    sf::RectangleShape background;
    sf::RectangleShape moreBackground;
    int selectedSpellIndex = 0;
    bool onMainMenu = true;
    int numReservedSpellTrees = 4;

    static const int numHealth = 18;
    static const int numAbility = 13;
    static const int maxSpells = 22;
    static const int maxExtraFeats = 4;
    static const int numDivLine = 7;

    sf::Text header;
    sf::Text health[numHealth];
    sf::Text ability[numAbility];
    float baseAbilityHeight[numAbility];
    sf::Text featsHeader[2];
    sf::Text spell[maxSpells];
    sf::Text spellCount[maxSpells];
    Button button[maxSpells];
    sf::Text feats[maxExtraFeats];
    float baseSpellHeight[maxSpells];
    HighlightBox spellHighlight[maxSpells];
    sf::RectangleShape divLine[numDivLine];
    sf::Text moreStats;
    HighlightBox moreHighlight;

    bool IsValidSpellIndex(const int spellIndex) const;
    int GetFeatStartingIndex() const {return(3 * numReservedSpellTrees + 1);}
    int GetNumFeats() const;
    int GetNumExtraFeats() const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
