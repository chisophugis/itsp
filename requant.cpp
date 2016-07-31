#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main(int, char **) {

  uint32_t Val;
  uint32_t Save = 0;

  while (scanf("%u", &Val) == 1) {
    // Use up-down analysis to verify that things are right.
    uint32_t W = Save + Val;
    if (W < Save) { // Overflow.
      //return 1;
      W = uint32_t(-1); // Saturate.
    }
    enum { kShift = 30 };
    uint32_t Requantized = W >> kShift;
    printf("%d\n", Requantized);
    Save = W & ((1u << kShift) - 1);
  }

  return 0;
}
