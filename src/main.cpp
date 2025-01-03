#include "../header/Manual.h"
#include "../header/System.h"
#include "../header/Taste.h"

string RESTAURANTS_FILE;
string DISTRICTS_FILE;
string DISCOUNTS_FILE;

int main(int argc, char* argv[]) {
    RESTAURANTS_FILE = argv[1];
    DISTRICTS_FILE = argv[2];
    DISCOUNTS_FILE = argv[3];
    Taste uTaste;
    System system(&uTaste);
    system.run();
}
