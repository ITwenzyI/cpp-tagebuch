#ifndef UI_MENUCONTROLLER_HPP
#define UI_MENUCONTROLLER_HPP

#include "service/EntryService.hpp"
#include "ConsoleInput.hpp"
#include "ConsoleRenderer.hpp"

class MenuController {
  public:
    // Verwendet Dependency Injection für UI- und Service-Komponenten.
    MenuController(ConsoleRenderer& renderer, ConsoleInput& input, EntryService& entryService);
    // Enthält die zentrale Menüschleife der Konsolenanwendung.
    int starte();

  private:
    ConsoleRenderer& renderer;
    ConsoleInput& input;
    EntryService& entryService;
};

#endif
