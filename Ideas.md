# Ideas
This is the place for results of brainstorming sessions which have not yet been implemented.

## Spells
Thoughts on player spellcasting:

### General
* maxSpells is determined by INT, and Spell regeneration is determined by WIS
* Any given PC won't get access to all spells

### Already Implemented
* Vampirism (STR & CHA) (As implemented, this doesn't acutally use STR) 
* Elements (INT)
* Transformation (INT)
* Life (CHA)
* Safety (WIS)

### Metamagic (INT)
* Maximize Spell
  * Next (couple?) spells have maximized effects
* Contingency
  * Works similarly to D&D
  * Can only be cast outside of battle
  * Player can only have one in effect at a time
* Free Spell
  * The turn after casting this spell, the player can cast any spell they know for free

### Conjuration (INT & CON)
* Call
  * Summons a low-level (relative to you) bear to fight for you
  * You have to fight the bear once all other enemies are defeated
* Dominate (Will Save)
  * Target enemy bear fights on the player's side
  * You have to fight the bear once all other enemies are defeated
  * ?Perhaps this should switch with Call, or you shouldn't have to fight the bear?
* Summon
  * Works like Call, except the summoned bear is higher level
  * Has the possibility of summoning a boss bear
  * In unlikely event that you are fighting a long bear and this spell summons a long bear:
    * The long bears make love and leave the fight
    * Your CHA is permanently increased by 1 point ("You feel sexually enlightened")
    * You have to fight any remaining enemy bears (e.g. homology bears, if the enemy long bear wasn't exact)

### Speed (DEX & INT)
* Slow (Will Save)
  * Slowes the bear
* Haste
  * Speeds the player
* Time stop
  * Player can attack bear while time is stopped

### Restoration (INT & WIS)
* Divination (Will Save)
  * You learn all there is to know about the target bear
* Erase (Will Save)
  * Resets some aspects of the target bear to default values
* Dispel (Will Save)
  * Like Erase, but affects more aspects of the target bear

### Defense (INT & WIS)
* Shield
  * Increases AC
* Spell Ward
  * Provides protection from spells and spell-like abilities
* Aegis
  

## Bear Modifiers
Possible modifiers that bears can have:

### Friendly
* Appears with an allied bear of lesser level
* Allied bears have to be close in alignment
* Lesser form of Gregarious (more allied bears)
* Lesser form of Numerous (allied bears are identical, instead of lower level)

### Hungry
* -5 to CON
* Fish spell results in love
* Bear always argry

### Mother
* Appears with allied babby bear(s) in tow

### Life Saving
* This modifier will never appear in the HUD before the bear uses it
* ?The first time an attack would kill the bear, it doesn't?
* ?All subsequent times, the bear has a 66% survival chance?
* ?A failed attempt to kill the bear through damage resets health to 5?

### Paladin
* Alignment changes to LG
* All stats except INT and CHA get increased slightly
* INT decreased
* CHA greatly increased
* Spell saves increase
* Automatically Gregarious

### Vampire
* Alignment changes to CE
* INT greatly increased
* After every attack player must make a save, else bear is healed
* Automatically Life Saving
