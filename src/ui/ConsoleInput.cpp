#include "ConsoleInput.hpp"

#include <iostream>
#include <limits>

int ConsoleInput::leseZahl() {
    int wert;
    std::cin >> wert;
    // Entfernt verbleibende Zeichen, damit Folgeeingaben nicht gestört werden.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return wert;
}

std::string ConsoleInput::leseWort() {
    std::string wort;
    std::cin >> wort;
    // Gleiches Verhalten wie bei Zahlen: Restpuffer wird geleert.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return wort;
}

std::string ConsoleInput::leseZeile() {
    std::string zeile;
    std::getline(std::cin, zeile);
    return zeile;
}
