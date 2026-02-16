#ifndef UI_MENUCONTROLLER_HPP
#define UI_MENUCONTROLLER_HPP

#include "service/EntryService.hpp"
#include "ConsoleInput.hpp"
#include "ConsoleRenderer.hpp"

class MenuController {
  public:
    MenuController(ConsoleRenderer& renderer, ConsoleInput& input, EntryService& entryService);
    int starte();

  private:
    ConsoleRenderer& renderer;
    ConsoleInput& input;
    EntryService& entryService;
};

#endif
