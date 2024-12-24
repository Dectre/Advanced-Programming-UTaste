#include <iostream>

#include "Manual.h"
#include "System.h"
#include "Taste.h"

int main() {
    Taste uTaste;
    System system(&uTaste);
    system.run();
}
