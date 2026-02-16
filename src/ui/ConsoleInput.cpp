#include "ConsoleInput.hpp"

#include <iostream>

int ConsoleInput::leseZahl() {
    int wert;
    std::cin >> wert;
    std::cin.ignore(); // Leerzeichen ignorieren
    return wert;
}

std::string ConsoleInput::leseWort() {
    std::string wort;
    std::cin >> wort;
    std::cin.ignore(); // Leerzeichen ignorieren
    return wort;
}

std::string ConsoleInput::leseZeile() {
    std::string zeile;
    std::getline(std::cin, zeile);
    return zeile;
}
