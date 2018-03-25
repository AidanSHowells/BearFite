#include <cstdlib>//include random number generator

int Roll(int diceNumber, int diceType){//roll (diceNumber)d(diceType).
  int total = 0;
  for (int i = 0; i < diceNumber; i++) {
    int tempNum = rand();
    while(tempNum >= RAND_MAX - (RAND_MAX % diceType)){
      tempNum = rand();
    }
    total += ((tempNum % diceType) + 1);
  }
  return (total);
}
