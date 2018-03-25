#include <cstdlib>//include random number generator

int Roll(int diceNumber, int diceType){//roll (diceNumber)d(diceType).
  int total = 0;
  for (int i = 0; i < diceNumber; i++) {
    total += ((rand() % diceType) + 1);
  }
  return (total);
}
