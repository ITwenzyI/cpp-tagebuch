#include "Application.hpp"

#include "service/EntryService.hpp"
#include "ui/ConsoleInput.hpp"
#include "ui/ConsoleRenderer.hpp"
#include "ui/MenuController.hpp"
#include <windows.h>

int Application::starte() {
    SetConsoleOutputCP(CP_UTF8);

    EntryService entryService;
    ConsoleRenderer renderer;
    ConsoleInput input;
    MenuController menuController(renderer, input, entryService);

    return menuController.starte();
}
