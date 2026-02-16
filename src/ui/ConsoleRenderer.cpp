#include "ConsoleRenderer.hpp"

#include <iostream>

void ConsoleRenderer::zeigeHauptmenue() const {
    std::cout << "\n|====| Kilians Digitales Tagebuch |====|\n";
    std::cout << "\n";
    std::cout << "1. Tagebuch. \n";
    std::cout << "0. Beenden.\n";
    std::cout << "\n";
    std::cout << "Deine Auswahl: ";
}

void ConsoleRenderer::zeigeAlltagMenue() const {
    std::cout << "\n-- Alltags Tagebuch --\n";
    std::cout << "\n";
    std::cout << "1. Neuen Eintrag erstellen.\n";
    std::cout << "2. Eintrag anzeigen.\n";
    std::cout << "3. Eintrag bearbeiten.\n";
    std::cout << "4. Eintrag entfernen.\n";
    std::cout << "5. Nach # suchen.\n";
    std::cout << "0. Beenden!\n";
    std::cout << "\n";
    std::cout << "Deine Auswahl: ";
}

void ConsoleRenderer::zeigeDanke() const {
    std::cerr << "Danke dir :)!\n";
}
