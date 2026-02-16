
#include "service/EntryService.hpp"
#include "ui/ConsoleInput.hpp"
#include "ui/ConsoleRenderer.hpp"
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <windows.h>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    EntryService entryService;
    ConsoleRenderer renderer;
    ConsoleInput input;

    int choice;
    int choice_alltag;
    do {
        renderer.zeigeHauptmenue();
        choice = input.leseZahl();

        if (choice == 1) {
            renderer.zeigeAlltagMenue();
            choice_alltag = input.leseZahl();

            switch (choice_alltag) {
            case 1:
                entryService.createEntry();
                break;
            case 2:
                entryService.showEntry();
                break;
            case 3:
                entryService.editEntry();
                break;
            case 4:
                entryService.deleteEntry();
                break;
            case 5:
                entryService.searchhashtagEntry();
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
