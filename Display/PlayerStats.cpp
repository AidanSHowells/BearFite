#include <string>//For std::to_string
#include <iostream>//For std::cerr
#include "PlayerStats.h"
#include "Display/Color.h"
#include "Display/AddSpace.h"
#include "Player.h"

PlayerStats::PlayerStats(
  sf::Font& titleFont,
  sf::Font& mainFont,
  Player& thePlayer,
  sf::Vector2f thePosition, //Default is sf::Vector2f(600, 0)
  sf::Vector2f theSize      //Default is sf::Vector2f(200, 580)
):
player(&thePlayer),
position(thePosition),
size(theSize)
{
  //Make the background rectangles
  background.setSize(size);
  background.setFillColor(Color::HUDBackground);
  background.setPosition(position.x, position.y);

  moreBackground.setSize(sf::Vector2f(size.x, 600 + 1 - size.y));
  moreBackground.setFillColor(Color::HUDBackground);
  moreBackground.setPosition(position.x, size.y + 1);

  //Make the header
  header.setFont(titleFont);
  header.setString("   YOUR STATUS");
  header.setCharacterSize(20);
  header.setFillColor(Color::DefaultText);
  header.setPosition(position.x, position.y - 5);

  //Make the health and drank info
  //Note: There's no point setting dynamic strings here; Update() handles them
  health[0].setFont(titleFont);
  health[0].setString("Health:");
  health[1].setFont(mainFont);
  health[2].setFont(titleFont);
  health[2].setString("Dranks:");
  health[3].setFont(mainFont);
  health[4].setFont(titleFont);
  health[4].setString("Exp. Needed:");
  health[5].setFont(mainFont);
  health[6].setFont(titleFont);
  health[6].setString("Level:");
  health[7].setFont(mainFont);
  health[8].setFont(titleFont);
  health[8].setString("Spellcasting Level:");
  health[9].setFont(mainFont);
  health[10].setFont(titleFont);
  health[10].setString("Body Count:");
  health[11].setFont(mainFont);
  health[12].setFont(titleFont);
  health[12].setString("Virginities:");
  health[13].setFont(mainFont);
  health[14].setFont(titleFont);
  health[14].setString("Bear:");
  health[15].setFont(mainFont);
  for(int i = 0; i < numHealth; i++){
    health[i].setCharacterSize(15);
    health[i].setFillColor(Color::DefaultText);
    health[i].setPosition(position.x, position.y + float(15 + 20 * (i/2)));
  }

  //Make the ability score header
  ability[0].setFont(titleFont);
  ability[0].setCharacterSize(15);
  ability[0].setFillColor(Color::DefaultText);
  ability[0].setString("Ablilities:");//Calc. version reference: Do not "fix"
  baseAbilityHeight[0] = position.y + 55;
  ability[0].setPosition(position.x, baseAbilityHeight[0]);

  //Make the ability score info
  for(int i = 1; i < numAbility; i += 2){
    ability[i].setFont(mainFont);
    ability[i].setCharacterSize(15);
    ability[i].setFillColor(Color::DefaultText);
    baseAbilityHeight[i] = position.y + float(62 + (i % 6) * 10);
    ability[i].setPosition(position.x + float(100 * ( i / 6) ),
                           baseAbilityHeight[i]);

    ability[i+1].setFont(mainFont);
    ability[i+1].setCharacterSize(15);
    ability[i+1].setFillColor(Color::DefaultText);
    baseAbilityHeight[i+1] = position.y + float(62 + (i % 6) * 10);
    ability[i+1].setPosition(position.x + float(100 * (i / 6) ),
                             baseAbilityHeight[i+1]);
  }
  ability[1].setString("STR:");
  ability[3].setString("DEX:");
  ability[5].setString("CON:");
  ability[7].setString("INT:");
  ability[9].setString("WIS:");
  ability[11].setString("CHA:");

  //Make the spells header
  spell[0].setFont(titleFont);
  spell[0].setCharacterSize(15);
  spell[0].setFillColor(Color::DefaultText);
  spell[0].setString("Spells:");
  baseSpellHeight[0] = position.y + 130;
  spell[0].setPosition(position.x, baseSpellHeight[0]);

  //Make the feats header
  featsHeader[0].setFont(titleFont);
  featsHeader[0].setCharacterSize(15);
  featsHeader[0].setFillColor(Color::DefaultText);
  featsHeader[0].setString("Feats:");

  featsHeader[1].setFont(mainFont);
  featsHeader[1].setCharacterSize(15);
  featsHeader[1].setFillColor(Color::PowerPool);

  //Make the spells/feats info
  for(int i = 1; i < maxSpells; i++){
    spell[i].setFont(mainFont);
    spell[i].setCharacterSize(15);
    spell[i].setFillColor(Color::DefaultText);

    spellCount[i].setFont(mainFont);
    spellCount[i].setCharacterSize(15);
    spellCount[i].setFillColor(Color::DefaultText);

    baseSpellHeight[i] = position.y + float(128 + 20 * i);
  }

  //Divide up the spells
  for(int i = 0; i < numDivLine; i++){
    divLine[i].setSize(sf::Vector2f(200,1));
    divLine[i].setFillColor(sf::Color::Black);
    divLine[i].setPosition(position.x, position.y + float(137 + 10 + i * 60) );
  }

  //Make the feats header than shows on the second page
  feats[0].setFont(titleFont);
  feats[0].setCharacterSize(15);
  feats[0].setFillColor(Color::DefaultText);
  feats[0].setString("Extra Feats:");
  feats[0].setPosition(position.x, position.y + 250);

  //Make the second-page-feat info
  for(int i = 1; i < maxExtraFeats; i++){
    feats[i].setFont(mainFont);
    feats[i].setCharacterSize(15);
    feats[i].setFillColor(Color::DefaultText);
    feats[i].setPosition(position.x, position.y + 248 + 20 * i);
  }

  //Make the button that changes which page you're on
  moreStats.setFont(titleFont);
  moreStats.setCharacterSize(15);
  moreStats.setFillColor(Color::DefaultText);
  moreStats.setPosition(moreBackground.getPosition());
  moreStats.move(75,-2);
  moreStats.setString("0:More");
  moreHighlight.AdjustToFit(moreStats.getGlobalBounds());
}

void PlayerStats::Update( const sf::Vector2f mousePos,
                          const bool isPickingSpell,
                          const bool canCastSpells )
{
  //Health
  sf::String playerHealth = std::to_string(player -> GetHealth());
  playerHealth += "/";
  playerHealth += std::to_string(player -> GetMaxHealth());
  health[1].setString(AddSpacing(playerHealth, 22) );

  //Dranks
  health[3].setString(AddSpacing(std::to_string(player -> GetNumDranks()), 22));

  //Exp
  health[5].setString(AddSpacing(std::to_string(player -> GetExpNeeded()), 22));

  //Level
  sf::String level = std::to_string(player -> GetLevel());
  health[7].setString(AddSpacing(level, 22));

  //Spellcasting Level
  sf::String spellLevel = std::to_string(player -> GetSpellcastingLevel());
  health[9].setString(AddSpacing(spellLevel, 22));

  //Body Count
  sf::String bodyCount = std::to_string(player -> GetBodyCount());
  health[11].setString(AddSpacing(bodyCount, 22));

  //Virginities
  sf::String numVirginities = std::to_string(player -> GetNumVirginities());
  health[13].setString(AddSpacing(numVirginities, 22));

  //Bear
  health[15].setString(AddSpacing(player -> GetLastBear(), 23));

  //Ability scores
  for(int i = 1; i <= 6; i++){
    ability[2*i].setString(AddSpacing(std::to_string(player->GetAbil(i-1)),10));
  }
  for(int i = 0; i < numAbility; i++){
    ability[i].setPosition( ability[i].getPosition().x,
                            baseAbilityHeight[i] + 120 * (!onMainMenu) );
  }

  //Spells
  int numPlayerSpells = 0;
  for(int i = 1; i < maxSpells; i++){
    spell[i].setPosition(position.x, baseSpellHeight[i]);
    spellCount[i].setPosition(position.x, baseSpellHeight[i]);
    if(player -> GetMaxNumSpell(i - 1) == 0){
      spell[i].setString(sf::String(""));
      spellCount[i].setString(sf::String(""));
    }
    else{
      numPlayerSpells = i;
      spell[i].setString(player -> GetSpellName(i - 1));
      sf::String count = std::to_string(player -> GetNumSpell(i - 1));
      sf::String max = std::to_string(player -> GetMaxNumSpell(i - 1));
      spellCount[i].setString(AddSpacing(count, 18) + sf::String("/") + max);
      spellCount[i].setFillColor(Color::DefaultText);
    }
  }

  if(numPlayerSpells <= 3){
    numReservedSpellTrees = 1;
  }
  else if(numPlayerSpells <= 12){
    numReservedSpellTrees = 4;
  }
  else{
    numReservedSpellTrees = 7;
  }

  const float featHeight = position.y + float(145 + numReservedSpellTrees * 60);
  featsHeader[0].setPosition(position.x, featHeight);
  featsHeader[1].setPosition(position.x, featHeight);

  sf::String count = std::to_string(player -> GetPower());
  sf::String max = std::to_string(player -> GetPowerPoolSize());
  featsHeader[1].setString(AddSpacing(count + sf::String("/") + max, 21));

  for(int featIndex = 0; featIndex < GetNumFeats(); featIndex++){
    int spellIndex = GetFeatStartingIndex() + featIndex;

    spell[spellIndex].move(0,12);
    spellCount[spellIndex].move(0,12);

    sf::String name = player -> GetRegularFeat(featIndex);
    spell[spellIndex].setString(AddSpacing(name,19,false));

    if((player -> FeatCost(featIndex)) > 0){
      sf::String cost = "-" + std::to_string(player -> FeatCost(featIndex));
      spellCount[spellIndex].setString(AddSpacing(cost, 21));
      spellCount[spellIndex].setFillColor(Color::PowerPool);
      if(player -> FeatIsActive(featIndex)){
        spell[spellIndex].setFillColor(Color::PowerPool);
      }
      else{
        spell[spellIndex].setFillColor(Color::DefaultText);
      }
    }
    else{
      spellCount[spellIndex].setString(sf::String(""));
      if(player -> FeatIsToggleable(featIndex)){
        button[spellIndex].SetText(spell[spellIndex]);
        if(onMainMenu){
          button[spellIndex].UpdateHighlighting(mousePos);
          button[spellIndex].SetState(player -> FeatIsActive(featIndex));
        }
      }
    }
  }

  for(int i = 1; i <= GetNumExtraFeats(); i++){
    feats[i].setString( player -> GetExtraFeat(i - 1) );
  }
  for(int i = GetNumExtraFeats() + 1; i < maxExtraFeats; i++){
    feats[i].setString("");
  }

  //Make sure the highlight boxes are the right size
  for(int i = 0; i < maxSpells - 1; i++){
    sf::FloatRect spellBox = spell[i + 1].getGlobalBounds();
    sf::FloatRect countBox = spellCount[i + 1].getGlobalBounds();
    spellBox.width = countBox.left + countBox.width - spellBox.left;
    spellBox.top--;
    spellBox.height += 2;
    spellHighlight[i].AdjustToFit(spellBox);
  }

  //If they're hovering over a valid spell, update selectedSpellIndex
  for(int i = 0; i < maxSpells - 1; i++){
    if(spellHighlight[i].Contains(mousePos) && IsValidSpellIndex(i)){
      selectedSpellIndex = i;
    }
  }

  //Highlight spells/feats
  if(onMainMenu && canCastSpells){
    for(int i = 0; i < maxSpells - 1; i++){
      spellHighlight[i].UpdateState(mousePos);
    }
    if(isPickingSpell){//Highlight even if not hovering
      spellHighlight[selectedSpellIndex].UpdateState(true);
    }
  }
  else{
    spellHighlight[selectedSpellIndex].UpdateState(false);
  }

  //Highlight the "More" button:
  if(isPickingSpell){
    moreHighlight.UpdateState(false);
  }
  else{
    moreHighlight.UpdateState(mousePos);
  }
}

bool PlayerStats::SpellChoiceProcessStarted(MessageBox& messages){
  if(!onMainMenu){
    messages.Update(sf::String("Cannot cast from here"),
                    sf::String("(press 0 for spells)") );
    return false;
  }

  bool playerHasSpells = false;
  for(int i = 0; i < maxSpells && !playerHasSpells; i++){
    playerHasSpells = IsValidSpellIndex(i);
  }

  if(playerHasSpells){
    messages.Update("Press Esc to cancle", "and Enter to select", true);

    //Start with the first usable spell selected by using GetSpell()
    selectedSpellIndex = -1;
    sf::Event scrollDown;
    scrollDown.type = sf::Event::KeyPressed;
    scrollDown.key.code = sf::Keyboard::Down;
    int dummyInt = 420;
    GetSpell(scrollDown, dummyInt);
  }
  else{
    messages.Update("No Spells To Cast");
  }

  return playerHasSpells;
}

void PlayerStats::ToggleMenu(const sf::Event event){
  if(event.type == sf::Event::KeyPressed){
    if( event.key.code == sf::Keyboard::Num0 ||
        event.key.code == sf::Keyboard::Numpad0)
    {
      onMainMenu = !onMainMenu;
    }
  }
  else if(event.type == sf::Event::MouseButtonPressed){
    sf::Vector2f clickLocation(float(event.mouseButton.x),
                               float(event.mouseButton.y) );
    if(moreHighlight.Contains(clickLocation)){
      onMainMenu = !onMainMenu;
    }
  }
}

void PlayerStats::ToggleFeats(const sf::Event event){
  if(onMainMenu && event.type == sf::Event::MouseButtonPressed){
    sf::Vector2f clickLocation(float(event.mouseButton.x),
                               float(event.mouseButton.y) );
    for(int featIndex = 0; featIndex < GetNumFeats(); featIndex++){
      if(player -> FeatIsToggleable(featIndex)){
        int spellIndex = GetFeatStartingIndex() + featIndex;
        if(button[spellIndex].Contains(clickLocation)){
          player -> ToggleFeat(featIndex);
          button[spellIndex].SetState(player -> FeatIsActive(featIndex));
        }
      }
    }
  }
}

bool PlayerStats::GetSpell(const sf::Event theEvent, int& index){
  if(theEvent.type == sf::Event::KeyPressed){
    if(theEvent.key.code == sf::Keyboard::Escape){
      index = changedMindAboutCasting;
      return true;
    }
    if(theEvent.key.code == sf::Keyboard::Up){
      selectedSpellIndex--;
      while(!IsValidSpellIndex(selectedSpellIndex) && selectedSpellIndex >= 0){
        selectedSpellIndex--;
      }
      if(selectedSpellIndex < 0){
        selectedSpellIndex = maxSpells;
        while(!IsValidSpellIndex(selectedSpellIndex)){
          selectedSpellIndex--;
        }
      }
    }
    else if(theEvent.key.code == sf::Keyboard::Down){
      selectedSpellIndex++;
      while(!IsValidSpellIndex(selectedSpellIndex) &&
            selectedSpellIndex < maxSpells)
      {
        selectedSpellIndex++;
      }
      if(selectedSpellIndex >= maxSpells){
        selectedSpellIndex = 0;
        while(!IsValidSpellIndex(selectedSpellIndex)){
          selectedSpellIndex++;
        }
      }
    }
    else if(theEvent.key.code == sf::Keyboard::Return){
      if(!IsValidSpellIndex(selectedSpellIndex)){
        std::cerr << "Warning! GetSpell tried to select the invalid spellIndex";
        std::cerr << " " << selectedSpellIndex << "\n\n";
        index = noChoice;
        return true;
      }
      else if(player -> GetNumSpell(selectedSpellIndex) > 0){
        index = selectedSpellIndex;
        return true;
      }
      else{
        index = selectedSpellIndex - GetFeatStartingIndex() + 1;
        return false;
      }
    }
  }

  else if(theEvent.type == sf::Event::MouseButtonPressed){
    sf::Vector2f clickLocation(float(theEvent.mouseButton.x),
                               float(theEvent.mouseButton.y) );
    for(int i = 0; i < maxSpells - 1; i++){
      if(spellHighlight[i].Contains(clickLocation) && IsValidSpellIndex(i)){
        if(player -> GetNumSpell(i) > 0){
          index = i;
          return true;
        }
        else{
          index = i - GetFeatStartingIndex() + 1;
          return false;
        }
      }
    }
  }

  index = noChoice;
  return true;
}

bool PlayerStats::IsValidSpellIndex(const int spellIndex) const{
  //Here a "valid spell index" is the index for a spell *or power pool feat*
  //that the player has enough power to cast. Better teminology welcome
  int featIndex = spellIndex - GetFeatStartingIndex() + 1;
  if(featIndex < 0 || featIndex >= GetNumFeats()){
    return(player -> GetNumSpell(spellIndex) > 0);
  }
  else{
    int cost = player -> FeatCost(featIndex);
    bool active = player -> FeatIsActive(featIndex);
    bool canBeActive = (cost > 0) && (player -> GetPower() >= cost);
    return((player -> GetNumSpell(spellIndex) > 0) || (canBeActive && !active));
  }
}

int PlayerStats::GetNumFeats() const {
  if(maxSpells - GetFeatStartingIndex() < player -> GetNumRegularFeats() ){
    std::cerr << "Warning! The player has more spells and feats than the HUD ";
    std::cerr << "is designed to handle\n\n";
    return(maxSpells - GetFeatStartingIndex());
  }
  return(player -> GetNumRegularFeats());
}

int PlayerStats::GetNumExtraFeats() const {
  if(maxExtraFeats <= player -> GetNumExtraFeats() ){
    std::cerr << "Warning! The player has more extra feats than the HUD ";
    std::cerr << "is designed to handle\n\n";
    return maxExtraFeats - 1;
  }
  return(player -> GetNumExtraFeats());
}

void PlayerStats::draw(sf::RenderTarget& target, sf::RenderStates states) const{
  target.draw(background, states);
  target.draw(moreBackground, states);
  target.draw(header, states);
  if(onMainMenu){
    for(int i = 0; i < 4; i++){
      target.draw(health[i], states);
    }
  }
  else{
    for(int i = 0; i < numHealth; i++){
      target.draw(health[i], states);
    }
  }
  for(int i = 0; i < numAbility; i++){
    target.draw(ability[i], states);
  }
  if(onMainMenu){
    if(7 != numReservedSpellTrees){
      target.draw(featsHeader[0], states);
      target.draw(featsHeader[1], states);
    }
    for(int i = 0; i < maxSpells; i++){
      target.draw(spell[i], states);
      target.draw(spellCount[i], states);
      if(IsValidSpellIndex(i)){
        target.draw(spellHighlight[i], states);
      }
    }
    for(int featIndex = 0; featIndex < GetNumFeats(); featIndex++){
      if(player -> FeatIsToggleable(featIndex)){
        int spellIndex = GetFeatStartingIndex() + featIndex;
        target.draw(button[spellIndex], states);
      }
    }
    for(int i = 0; i < numReservedSpellTrees; i++){
      target.draw(divLine[i], states);
    }
    if(7 != numReservedSpellTrees){
      target.draw(divLine[numReservedSpellTrees], states);
    }
  }
  else{
    for(int i = 0; i < maxExtraFeats; i++){
      target.draw(feats[i], states);
    }
  }
  target.draw(moreStats, states);
  target.draw(moreHighlight, states);
}
