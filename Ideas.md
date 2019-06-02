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
* Speed (DEX & INT)

### Metamagic I (INT)
* Broaden
  * Next spell (or few spells?) targets all bears if it would only target one
  * Ends once the player casts a non-metamagic spell, even if that spell is unaffected by Broaden
* Maximize Spell
  * Next (couple?) spell(s) has maximized effects
  * Ends once the player casts a non-metamagic spell, even if that spell is unaffected by Maximize
* Contingency
  * Works similarly to D&D
  * ?Can only be cast outside of battle?
  * Player can only have one in effect at a time

### Metamagic II (INT) (Requires the player to have Metamagic I)
* Instant Spell
  * Casting this spell does not use the player's turn.
  * Furthermore, if the player's next action is to cast another spell, casting that spell doesn't use the player's turn either
  * ?Cannot be cast via inself?
* Free Spell
  * The turn after casting this spell, the player can cast any spell they know for free
* Unleash Magic
  * Does not use the player's turn
  * Functions as if casting Broaden, Maximize spell, and Free spell simultanuously
  * ?Cannot be cast via "Instant Spell"?

### Conjuration (INT & CON)
* Call
  * Summons a low-level (relative to you) bear to fight for you
  * You have to fight the bear once all other enemies are defeated (Chance based on CHA that you don't have to?)
* Dominate (Will Save)
  * Target enemy bear fights on the player's side
  * You have to fight the bear once all other enemies are defeated (Chance based on CHA that you don't have to?)
  * ?Perhaps this should switch with Call, or you shouldn't have to fight the bear?
* Summon
  * Works like Call, except the summoned bear is higher level
  * Has the possibility of summoning a boss bear
  * In unlikely event that you are fighting a long bear and this spell summons a long bear:
    * The long bears make love and leave the fight
    * Your CHA is permanently increased by 1 point ("You feel sexually enlightened")
    * You have to fight any remaining enemy bears (e.g. homology bears, if the enemy long bear wasn't exact)

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

## Feats
Possible feats that the player can take

### General
* Types of Feats:
  * Permanent: Once you take then, always on
  * Toggleable: Can be switched on and off. Unless otherwise stated, each feat can be toggled at any point
  * Power pool: Player has a "power pool" which they draw on to use these feats. Some feats will cost more than others
* Some feats have ability score requirements to take.
  * This is indicated in parentheses after the name of the feat below
* ?Some toggleable feats have multiple levels.?
  * You take one level at a time.
  * The second time you take such a feat, more options are added to the toggle, which is moved into the slot below the feat (so that the feat now counts double towards the cap).
  * When taking the third level (when applicable), an extra option is added to the second line (so the feat still only counts double, not triple)
* There should be an option outside of battle to set the defaults for toggleable feats
* During player construction, can pick:
  * One permanent feat (from a partial list of permanent feats?)
  * One feat or spelltree (no restrictions)
* The player will regularly be given the option to get either new spells or new feats
  * If they pick "feat", they will be given a random list of feats to choose from
  * The random list will only contain feats that the player could possibly take
* 18 feat cap. Having more than 1 spelltree caps you at 9 feats. Having more than 4 spelltrees caps you at zero feats
  * Viewed from the other perspective, this is a 7 spelltree cap, where having more than 0 feats caps you at 4 spelltrees and more than 9 feats caps you at 1 spelltree
  * First three permanent feats don't take up space on the in-battle menu, and don't count towards the feat cap
* Player should occasionally be given the option to switch out old spells/feats for new spells/feats. (In theory this could make "Hidden power" broken, but in practice if getting a spellcasting-oriented  character to the point where they have 9 feats with only one spell is easy enough for it to be a sensible strategy, then we have bigger issues)

### Permanent Feats:
* Studied Dodge (INT > 12): Pick one species of bear to have (medium) AC bonus against. Can take this feat multiple times (new bear each time; INT requirement increases). [**ADDED**]
* Escape Artist: Improved odds of fleeing battle [**ADDED**]
* Eau de poisson: Medium improvement to odds of bear being love, small decrease in chance of Djinn bear
* Honey scent: Small decrease in odds of bear being love, medium improvement to chance of Djinn bear
* Deepen Pool: Increase power pool max size
* Boost (---): +1 to corresponding ability score. Really six feats, one per ability score
* Master Bargainer: Capped CHA-based chance of surviving attacks that would otherwise kill
* Bear Watcher (INT + WIS): Can see more information about enemy bears
* Blind for Bear: Powerful enough physical attacks give a accuracy penalty to the target
* Insanity: All rolls from here on out are "wild" (maybe this should come with some sort of bonus so that it's not objectively bad)
* Zen master: All rolls from here on out are "consistent"

### Toggleable Feats:
* Power Attack (STR > 8 + 3 / lvl): Same as D&D. Multiple levels? [**ADDED**]
* Whirlwind Attack (DEX > 14): Regular attack targets all bears with accuracy penalty [**ADDED**]
* Focused dodge (WIS > 11): Pick one specific bear on battlefield to have (small) AC bonus against. (Can change bear every turn)
* Smoke Screen: Everyone on the battlefield gets an AC bonus. Multiple levels?
* Close combat: Everyone on the battlefield gets an AC penalty. Multiple levels?
* Training wheels: Only can be turned on during the first turn of battle. Reduces player damage, but increases experience

### Power Pool Feats:
* Gulper: Quaffs drank without using turn [**ADDED**]
* Cobra Strike: Next crit is for double (triple? 420?) damage. Doesn't persist between battles. [**ADDED** with damage set to 69]
* Double Attack (STR + DEX): Two (physical) attacks in one turn
* Multi Attack (STR + DEX + double attack): Three (physical) attacks in one turn (costs more than double attack?)
* Hidden power (CON > 17, or CON > 11 and will now have enough feats to rule out getting more than one spell tree): +1 to current number of each spell (costs extra if player has more than one spelltree?)
* Uncanny dodge: Medium AC bonus for some number of turns
* All-Out Attack: Next attack guaranteed nat 60
* Lucky: Player d60 rolls are with advantage for the rest of the battle (roll two dice, take the larger.)


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
