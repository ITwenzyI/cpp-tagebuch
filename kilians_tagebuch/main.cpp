
#include <iostream>
#include "EntryManager.hpp"
#include <windows.h>
#include <io.h>
#include <fcntl.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    EntryManager entrymanager;

    int choice;
    int choice_alltag;
    do {
        std::cout << "\n|====| Kilians Digitales Tagebuch |====|\n";
        std::cout << "\n";
        std::cout << "1. Tagebuch. \n";
        std::cout << "0. Beenden.\n";
        std::cout << "\n";
        std::cout << "Deine Auswahl: ";
        std::cin >> choice;
        std::cin.ignore(); // Leerzeichen ignorieren

        if (choice == 1) {
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
            std::cin >> choice_alltag;
            std::cin.ignore(); // Leerzeichen ignorieren

            switch (choice_alltag) {
                case 1: entrymanager.createEntry(); break;
                case 2: entrymanager.showEntry(); break;
                case 3: entrymanager.editEntry(); break;
                case 4: entrymanager.deleteEntry(); break;
                case 5: entrymanager.searchhashtagEntry(); break;
                default: std::cerr << "Danke dir :)!\n"; return 0;

            }
        }

    } while (choice != 0);

    std::cerr << "Danke dir :)!\n";
    return 0;
}
