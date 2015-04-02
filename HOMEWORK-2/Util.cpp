#include <random>
#include "Util.h"

// random integer from l to r inclusive
int randint(int l, int r) {
    return l + rand() % (r - l + 1);
}