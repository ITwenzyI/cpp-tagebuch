#include "ConsoleInput.hpp"

#include <iostream>
#include <limits>

int ConsoleInput::leseZahl() {
    int wert;
    std::cin >> wert;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return wert;
}

std::string ConsoleInput::leseWort() {
    std::string wort;
    std::cin >> wort;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return wort;
}

std::string ConsoleInput::leseZeile() {
    std::string zeile;
    std::getline(std::cin, zeile);
    return zeile;
}
