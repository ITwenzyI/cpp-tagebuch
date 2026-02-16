#include "MenuController.hpp"

namespace {
// Menüwerte als benannte Konstanten statt verstreuter Zahlen.
constexpr int HAUPTMENUE_TAGEBUCH = 1;
constexpr int ALLTAG_NEUER_EINTRAG = 1;
constexpr int ALLTAG_EINTRAG_ANZEIGEN = 2;
constexpr int ALLTAG_EINTRAG_BEARBEITEN = 3;
constexpr int ALLTAG_EINTRAG_ENTFERNEN = 4;
constexpr int ALLTAG_HASHTAG_SUCHE = 5;
} // namespace

MenuController::MenuController(
    ConsoleRenderer& renderer, ConsoleInput& input, EntryService& entryService)
    : renderer(renderer), input(input), entryService(entryService) {
}

int MenuController::starte() {
    int choice;
    int choice_alltag;
    do {
        renderer.zeigeHauptmenue();
        choice = input.leseZahl();

        if (choice == HAUPTMENUE_TAGEBUCH) {
            renderer.zeigeAlltagMenue();
            choice_alltag = input.leseZahl();

            switch (choice_alltag) {
                // Delegiert die gewählte Aktion an den Service.
                case ALLTAG_NEUER_EINTRAG:
                    entryService.createEntry();
                    break;
                case ALLTAG_EINTRAG_ANZEIGEN:
                    entryService.showEntry();
                    break;
                case ALLTAG_EINTRAG_BEARBEITEN:
                    entryService.editEntry();
                    break;
                case ALLTAG_EINTRAG_ENTFERNEN:
                    entryService.deleteEntry();
                    break;
                case ALLTAG_HASHTAG_SUCHE:
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
