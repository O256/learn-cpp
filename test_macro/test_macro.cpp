#include "test_macro.h"

bool test(int a) {
  if (a == 0) {
    return false;
  } else {
    return true;
  }
}

int main(int argc, char **argv) {
  IF_NOT(test(0))
  return 0;
}
