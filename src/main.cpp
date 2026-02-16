
#include "EntryManager.hpp"
#include "ui/ConsoleRenderer.hpp"
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    EntryManager entrymanager;
    ConsoleRenderer renderer;

    int choice;
    int choice_alltag;
    do {
        renderer.zeigeHauptmenue();
        std::cin >> choice;
        std::cin.ignore(); // Leerzeichen ignorieren

        if (choice == 1) {
            renderer.zeigeAlltagMenue();
            std::cin >> choice_alltag;
            std::cin.ignore(); // Leerzeichen ignorieren

            switch (choice_alltag) {
            case 1:
                entrymanager.createEntry();
                break;
            case 2:
                entrymanager.showEntry();
                break;
            case 3:
                entrymanager.editEntry();
                break;
            case 4:
                entrymanager.deleteEntry();
                break;
            case 5:
                entrymanager.searchhashtagEntry();
                break;
            default:
                renderer.zeigeDanke();
                return 0;
            }
        }

    } while (choice != 0);

    renderer.zeigeDanke();
    return 0;
}
