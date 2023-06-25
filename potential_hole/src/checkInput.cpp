#include "checkInput.hpp"
#include <ctype.h>

int isOkInputNumber(char *charString) {
  for (int i = 0; charString[i] != '\0'; i++) {
    bool isNumber = isdigit(charString[i]);
    if (!isNumber) {
      return 0;
    }
  }
  return 1;
}

int isOkInputWidth(char *symbol) {
  int length = 0;
  for (int i = 0; symbol[i] != '\0'; i++) {
    length++;
  }
  if (length != 1) {
    return 0;
  }
  if (symbol[0] == 'a' || symbol[0] == 's') {
    return 1;
  }

  return 0;
}
