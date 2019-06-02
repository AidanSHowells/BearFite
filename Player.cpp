#include "Player.h"
#include "Bear.h"
#include "RollDice.h"
#include "Spell.h"
#include "Feats.h"
#include "BearBattle.h"
#include <algorithm>//for std::max and std::min
#include <iostream>//for std::cerr


Player::Player(){
  body.hitDieSize = 6;
  body.baseHealth = 50;

  maxHealth = body.UpdateHealth(body.baseHealth,
                                level,
                                GetAbil(int(Abil::CON)),
                                numVirginities);

  health = maxHealth;
}

void Player::SetMessageBox(MessageBox& theMessages){Messages = &theMessages;}

int Player::GetHealth(){
  health = std::min(health, GetMaxHealth());

  return health;
}

int Player::GetMaxHealth(){
  maxHealth = body.UpdateHealth(maxHealth,
                                level,
                                GetAbil(int(Abil::CON)),
                                numVirginities);

  return maxHealth;
}

int Player::GetAbil(const int index, const bool isCheckingDeath) const {
  int abil = baseAbil.at(index) + abilBuff.at(index);
  if(index == int(Abil::STR)){
    abil += 6 * IsRaging() + 4 * IsWarCrying() + 10 * HasBigFist();
  }
  if(index == int(Abil::DEX)){
    abil += 4 * HasBigFist() + 6 * IsHasted() - 6 * IsSlowed();
    if(!isCheckingDeath && IsParalyzed()){
      abil = std::min(1, abil);
    }
  }
  if(index == int(Abil::CON)){
    abil += 6 * IsRaging() + 4 * IsWarCrying() + 10 * HasBigFist();
  }
  if(index == int(Abil::INT)){
    abil += -4 * IsRaging();
  }
  if(index == int(Abil::WIS)){

  }
  if(index == int(Abil::CHA)){
    abil += -4 * IsRaging();
  }
  return abil;
}

void Player::BuffAbil(const int index, const int buff){
  abilBuff.at(index) += buff;
}

int Player::GetAC(const BearID attacker) const {
  int AC = baseAC + armor + GetAbil(int(Abil::DEX)) - 10;
  if(HasFeatActive(FeatID::studied_dodge, attacker)){
    AC += 20;
  }
  return AC;
}

void Player::Hurt(int dmg){health -= dmg;}

bool Player::IsDead(){
  if(GetHealth() <= 0){
    return true;
  }
  for(int i = 0; i < int(Abil::NUM_ABIL); i++){
    if(GetAbil(i, true) < 1){
      return true;
    }
  }
  return false;
}

TurnOf Player::TakeAction(const Action theAction,
                          Bear& theBear,
                          std::vector<Bear*> enemyBears)
{
  TurnOf nextTurn;
  if(IsSafe() &&
    (theAction == Action::leg ||
    theAction == Action::eye ||
    theAction == Action::john_hopkins))
  {
    Messages -> Update(sf::String("Don't be naughty"));
    nextTurn = TurnOf::player;
  }
  else if(theAction == Action::leg){
    nextTurn = TurnOf::bear;
    if(HasFeatActive(FeatID::whirlwind_attack)){
      for(std::size_t i = 0; i < enemyBears.size(); i++){
        LegPunch(*(enemyBears.at(i)));
      }
    }
    else{
      LegPunch(theBear);
    }
  }
  else if(theAction == Action::eye){
    nextTurn = TurnOf::bear;
    if(HasFeatActive(FeatID::whirlwind_attack)){
      for(std::size_t i = 0; i < enemyBears.size(); i++){
        EyePunch(*(enemyBears.at(i)));
      }
    }
    else{
      EyePunch(theBear);
    }
  }
  else if(theAction == Action::john_hopkins){
    Messages -> Update(sf::String("John Hopkins punching"),
                       sf::String("is unsupported."));//TEMP
    nextTurn = TurnOf::player;//TEMP
  }
  else if(theAction == Action::quaff){
    nextTurn = Quaff();
  }
  else if(theAction == Action::cast){
    Messages -> Update(sf::String("Whoops!"), sf::String("Spellcasting Error"));
    nextTurn = TurnOf::player;
  }
  else if(theAction == Action::flee){
    nextTurn = Flee(theBear);
  }
  else if(theAction == Action::nothing){
    nextTurn = TurnOf::player;
  }
  else{
    std::cerr << "Warning! ";
    std::cerr << "Use of Action unknown to Player::TakeAction.\n";
    nextTurn = TurnOf::player;
  }

  if(timeStopTime > 0 && TurnOf::bear == nextTurn){
    timeStopTime--;
    nextTurn = TurnOf::player;
  }

  return nextTurn;
}

TurnOf Player::Cast(const int index, BattleHUD& environment){
  int spellTreeIndex = index / 3;
  int spellIndex = index % 3;
  SpellID spellToCast = spellList.at(spellTreeIndex).spellIDList.at(spellIndex);
  TurnOf nextTurn;

  if(IsSafe() && Spell(spellToCast).IsOffensive()){
    Messages -> Update(sf::String("Don't be naughty"));
    nextTurn = TurnOf::player;
  }
  else{
    spellList.at(spellTreeIndex).numSpells.at(spellIndex) --;
    nextTurn = Spell(spellToCast).Cast(*this, environment);
  }

  if(timeStopTime > 0 && TurnOf::bear == nextTurn){
    timeStopTime--;
    nextTurn = TurnOf::player;
  }

  return nextTurn;
}

int Player::GetSpellSchoolBonus(const SpellSchool school){
  int bonus;
  if(school == SpellSchool::STR){
    bonus = GetAbil(int(Abil::STR)) + 2 * GetAbil(int(Abil::INT));
  }
  else if(school == SpellSchool::DEX){
    bonus = GetAbil(int(Abil::DEX)) + 2 * GetAbil(int(Abil::INT));
  }
  else if(school == SpellSchool::CON){
    bonus = GetAbil(int(Abil::CON)) + 2 * GetAbil(int(Abil::INT));
  }
  else if(school == SpellSchool::INT){
    bonus = 3 * GetAbil(int(Abil::INT));
  }
  else if(school == SpellSchool::WIS){
    bonus = ( 3 * GetAbil(int(Abil::WIS)) + 3 * GetAbil(int(Abil::INT)) )/2;
  }
  else if(school == SpellSchool::CHA){
    bonus = ( 3 * GetAbil(int(Abil::CHA)) + 3 * GetAbil(int(Abil::INT)) )/2;
  }
  else if (school == SpellSchool::WIS_CHA){
    bonus = GetAbil(int(Abil::INT)) + GetAbil(int(Abil::WIS))
            + GetAbil(int(Abil::CHA));
  }
  else{
    std::cerr << "Warning! ";
    std::cerr << "Use of SpellSchool unknown to Player::GetSpellSchoolBonus.\n";
    std::cerr << "The index of the invalid SpellSchool was ";
    std::cerr << int(school) << ".\n\n";
    bonus = 0;
  }
  return bonus;
}

sf::String Player::GetSpellName(const int index){
  if(index < 0 || index >= 3 * GetNumSpellTrees()){
    return sf::String("");
  }

  int spellTreeIndex = index / 3;
  int spellIndex = index % 3;
  SpellID spellID = spellList.at(spellTreeIndex).spellIDList.at(spellIndex);
  return Spell(spellID).GetName();
}

int Player::GetNumSpell(const int index){
  if(index < 0 || index >= 3 * GetNumSpellTrees()){
    return 0;
  }
  else{
    int spellTreeIndex = index / 3;
    int spellIndex = index % 3;
    return spellList.at(spellTreeIndex).numSpells.at(spellIndex);
  }
}

int Player::GetMaxNumSpell(const int index){
  if(index < 0 || index >= 3 * GetNumSpellTrees()){
    return 0;
  }
  else{
    int spellTreeIndex = index / 3;
    int spellIndex = index % 3;
    return spellList.at(spellTreeIndex).maxSpells.at(spellIndex);
  }
}

void Player::UnlockSpellTree(SpellTree tree){
  spellList.push_back(tree);
}

bool Player::TouchAttackSucceeds(const Bear& bear) const{
  return (Roll(1,60) + GetTouchAttackBonus() >= bear.GetAC(Action::cast));
}

void Player::MakeSweetLove(){
  Messages -> Update("You have lost", "your virginity.", true);
  Messages -> Update("Bear is love.");
  numVirginities--;
}

void Player::TimerTick(){
  hastedTime = std::max(0, hastedTime - 1);
  slowedTime = std::max(0, slowedTime - 1);
  paralyzedTime = std::max(0, paralyzedTime - 1);
  ragingTime = std::max(0, ragingTime - 1);
  warCryingTime = std::max(0, warCryingTime - 1);
  bigFistTime = std::max(0, bigFistTime - 1);
  santuaryTime = std::max(0, santuaryTime -1);
  timeStopTime = std::max(0, timeStopTime -1);
}

void Player::PostBattleReset(){
  hastedTime = 0;
  slowedTime = 0;
  paralyzedTime = 0;
  ragingTime = 0;
  warCryingTime = 0;
  bigFistTime = 0;
  santuaryTime = 0;
  timeStopTime = 0;
  power = powerPoolSize;//TEMP
  if(HasFeatActive(FeatID::cobra_strike)){
    Toggle(FeatID::cobra_strike);
  }
}

void Player::AddFeat(const FeatID theFeat, const BearID theBear){
  Feat newFeat(theFeat, theBear);
  for(std::size_t i = 0; i < featList.size(); i++){
    //The Feat constructor ignores theBear if the feat doesn't care about it.
    //So in that case we can have newFeat.targetBearID != theBear.
    if( theFeat == featList.at(i).featID &&
        newFeat.targetBearID == featList.at(i).targetBearID )
    {
      std::cerr << "Warning! Failed to add feat \"";
      std::cerr << std::string(newFeat.name) << "\"\n";
      std::cerr << "The player already has that feat\n\n";
      return;
    }
  }
  if(newFeat.cost > 0){
    bool done = false;
    for(std::size_t i = 0; !done && i < featList.size(); i++){
      if(featList.at(i).cost == 0){
        featList.insert(featList.begin() + i, newFeat);
        done = true;
      }
    }
    if(!done){
      featList.push_back(newFeat);
    }
  }
  else if(newFeat.permanent){
    bool done = false;
    for(std::size_t i = 0; !done && i < featList.size(); i++){
      if(featList.at(i).cost == 0 && !(featList.at(i).permanent)){
        featList.insert(featList.begin() + i, newFeat);
        done = true;
      }
    }
    if(!done){
      featList.push_back(newFeat);
    }
  }
  else{
    featList.push_back(newFeat);
  }
}

bool Player::FeatIsToggleable(const int index) const {
  const Feat theFeat = featList.at(index);
  return (!(theFeat.permanent) && (0 == theFeat.cost));
}

TurnOf Player::ActivateFeat(const int index){
  Feat& theFeat = featList.at(index);
  if(theFeat.permanent){
    std::cerr << "Warning! Cannot activate permanent feats like \"";
    std::cerr << std::string(theFeat.name) << "\"\n";
    std::cerr << "(The index of this feat in the player\'s feat list is ";
    std::cerr << index << ", if that helps)\n\n";
  }
  else{
    power -= theFeat.cost;
    theFeat.active = true;
    if(theFeat.featID == FeatID::gulper){
      if(TurnOf::player == Quaff()){
        power += theFeat.cost;//If Quaff returns TurnOf::player then quaffing
                              //failed. We're nice and so we give a refund
      }
      theFeat.active = false;
    }
  }
  return TurnOf::player;
}

void Player::ToggleFeat(const int index){
  Feat& theFeat = featList.at(index);
  if(!FeatIsToggleable(index)){
    std::cerr << "Warning! The feat \"" << std::string(theFeat.name) << "\" ";
    std::cerr << "is not toggleable\n\n";
  }
  else{
    theFeat.active = !theFeat.active;
  }
}

bool Player::HasFeatActive(const FeatID theFeat) const {
  for (size_t i = 0; i < featList.size(); i++) {
    if(featList.at(i).featID == theFeat && featList.at(i).active){
      return true;
    }
  }

  return false;
}

bool Player::HasFeatActive(const FeatID theFeat, const BearID theBear) const {
  for(size_t i = 0; i < featList.size(); i++){
    if( featList.at(i).featID == theFeat &&
        featList.at(i).targetBearID == theBear &&
        featList.at(i).active)
    {
      return true;
    }
  }
  return false;
}

void Player::SetAbil(std::array<int,int(Abil::NUM_ABIL)> newAbil){
  baseAbil = newAbil;
}

int Player::GetLegAttackBonus() const {
  int attackBonus = GetAbil(int(Abil::STR)) - 10;
  if(HasFeatActive(FeatID::power_attack)){
    attackBonus -= 5;
  }
  if(HasFeatActive(FeatID::whirlwind_attack)){
    attackBonus -= 10;
  }
  return attackBonus;
}

int Player::GetLegDamageBonus() const {
  int damageBonus = (GetAbil(int(Abil::STR)) - 10)/2;
  if(HasFeatActive(FeatID::power_attack)){
    damageBonus += 5;
  }
  return damageBonus;
}

int Player::GetEyeAttackBonus() const {
  int attackBonus = GetAbil(int(Abil::STR)) - 10 + GetAbil(int(Abil::DEX)) - 10;
  if(HasFeatActive(FeatID::power_attack)){
    attackBonus -= 5;
  }
  if(HasFeatActive(FeatID::whirlwind_attack)){
    attackBonus -= 10;
  }
  return attackBonus;
}

int Player::GetEyeDamageBonus() const {
  int damageBonus = 2*(GetAbil(int(Abil::STR)) - 10) + 5;
  if(HasFeatActive(FeatID::power_attack)){
    damageBonus += 5;
  }
  return damageBonus;
}

int Player::GetTouchAttackBonus() const {
  return 0;//FIXME
}


void Player::LegPunch(Bear& bear){
  int dmg = 0; //Keeps track of the damage of this attack
  int roll = Roll(1,60); //keeps track of roll for handling criticals

  if(roll == 60 ||  timeStopTime > 0
                || roll + GetLegAttackBonus() >= bear.GetAC(Action::leg)){
    if(roll > 60 - legCritThreat){
      dmg = Roll(2,8) + 2 * GetLegDamageBonus();
      if(HasFeatActive(FeatID::cobra_strike)){
        dmg = 69;
        Toggle(FeatID::cobra_strike);
      }
      Messages -> Update("You CRIT bear for:", dmg, true);
    }
    else{
      dmg = Roll(1,8) + GetLegDamageBonus();
      Messages -> Update("You got bear for:", dmg, true);
    }
    bear.Hurt(std::max(1,dmg));
  }
  else{Messages -> Update("Carp, you miss.", true);}
}

void Player::EyePunch(Bear& bear){
  int dmg = 0; //Keeps track of the damage of this attack
  int roll = Roll(1,60); //keeps track of roll for handling criticals
  if(roll == 60 ||  timeStopTime > 0
                ||  roll + GetEyeAttackBonus() >= bear.GetAC(Action::eye)){
    if(roll > 60 - eyeCritThreat){
      dmg = Roll(4,12) + 2 * GetEyeDamageBonus();
      if(HasFeatActive(FeatID::cobra_strike)){
        dmg = 69;
        Toggle(FeatID::cobra_strike);
      }
      Messages -> Update("You CRIT bear for:", std::max(1,dmg), true);
    }
    else{
      dmg = Roll(2,12) + GetEyeDamageBonus();
      Messages -> Update("You got bear for:", std::max(1,dmg), true);
    }
    bear.Hurt(std::max(1,dmg));
  }
  else{Messages -> Update("Carp, you miss.", true);}
}

TurnOf Player::Quaff(){
  if(numDranks < 1){
    Messages -> Update("You're drank pauper.");
    return TurnOf::player;
  }
  else if(health >= maxHealth){
    Messages -> Update("You aren't thirst.");
    return TurnOf::player;
  }
  else{
    Messages -> Update("Down the hatch", true);
    health = std::min(maxHealth, health + 15);//No soft max yet
    numDranks--;
    return TurnOf::bear;
  }
}

TurnOf Player::Flee(Bear& bear){
  int fleeAttempt = Roll(1,60) + GetAbil(int(Abil::DEX));
  if(HasFeatActive(FeatID::escape_artist)){
    fleeAttempt += 10;
  }
  //FIXME: The odds of successfully fleeing need to be fine-tuned
  if(IsHasted() || fleeAttempt >= 30 + bear.GetAbil(int(Abil::DEX))){
    Messages -> Update("You escape bear", true);
    return TurnOf::neither;
  }
  Messages -> Update("Bear still behind you", true);
  return TurnOf::bear;
}

void Player::Toggle(const FeatID theFeat){
  size_t index = featList.size();
  for (size_t i = 0; i < featList.size(); i++) {
    if(featList.at(i).featID == theFeat){
      index = i;
    }
  }
  if(index == featList.size()){
    std::cerr << "Warning! Illegal attempt to toggle the feat \"";
    std::cerr << std::string(Feat(theFeat).name) << "\"\n\n";
  }
  else{
    featList.at(index).active = !(featList.at(index).active);
  }

}

void Player::Toggle(const FeatID theFeat, const BearID theBear){
  size_t index = featList.size();
  for (size_t i = 0; i < featList.size(); i++) {
    if( featList.at(i).featID == theFeat &&
        featList.at(i).targetBearID == theBear )
    {
      index = i;
    }
  }
  if(index == featList.size()){
    std::cerr << "Warning! Illegal attempt to toggle the feat \"";
    std::cerr << std::string(Feat(theFeat, theBear).name) << "\"\n\n";
  }
  else{
    featList.at(index).active = !(featList.at(index).active);
  }
}
