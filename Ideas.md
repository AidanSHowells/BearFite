# Ideas
This is the place for results of brainstorming sessions which have not yet been implemented.

## Spells
Thoughts on player spellcasting:

### General
* class Spell should be friends with class Player and class Bear
* class Bear should have a boolean isBoss
* class Player should have int arrays maxSpells and currSpells
* maxSpells is determined by INT, and Spell regeneration is determined by WIS
* Any given PC won't get access to all spells
* ?Spells should be grouped into tiers?

### Fish
* Bear is munching while under the effect of this spell
* The chance of this spell ending increases with each passing turn
* ?Lower tier version of Invuln?

### Death
* Kills non-boss bears
* Badly wounds boss bears

### Pleasure
* Player loses virginity
* Battle ends

### Reversal
* Bear and Player trade health
* ?Higher/Lower tier version of vampirism?

### Other Possible Spells
* Ability boost (one per stat)
* Ability drain (one per stat)


## Bear Modifiers
Possible modifiers that bears can have:

### Friendly
* Appears with an allied bear of lesser level
* Lesser form of Gregarious (more allied bears)
* Lesser form of Numerous (allied bears are identical, instead of lower level)

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
