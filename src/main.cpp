#include "Manual.h"
#include "System.h"
#include "Taste.h"

string RESTAURANTS_FILE;
string DISTRICTS_FILE;

int main(int argc, char* argv[]) {
    RESTAURANTS_FILE = argv[1];
    DISTRICTS_FILE = argv[2];
    Taste uTaste;
    System system(&uTaste);
    system.run();
}
