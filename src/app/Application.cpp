#include "Application.hpp"

#include "service/EntryService.hpp"
#include "ui/ConsoleInput.hpp"
#include "ui/ConsoleRenderer.hpp"
#include "ui/MenuController.hpp"
#include <windows.h>

int Application::starte() {
    // Erzwingt UTF-8 für korrekte Konsolenausgabe unter Windows.
    SetConsoleOutputCP(CP_UTF8);

    // Composition Root: erstellt konkrete Abhängigkeiten und verdrahtet sie.
    EntryService entryService;
    ConsoleRenderer renderer;
    ConsoleInput input;
    MenuController menuController(renderer, input, entryService);

    return menuController.starte();
}
