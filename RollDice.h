#ifndef ROLLDICE_H
#define ROLLDICE_H

enum class RollMod{none, wild, consistant};

int Roll(const int diceNumber,
         const int diceType,
         const RollMod modifier = RollMod::none);

#endif

/*To use this, you have to "#include" <cstdlib> and <ctime> and plop a
 *"srand(unsigned(time(NULL)));" into your code right after "int main(){".
 *I wish I had a good way to work around this and make "RollDice"
 *self-contained, but I don't.
 */
