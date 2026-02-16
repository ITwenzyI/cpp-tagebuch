#ifndef UI_CONSOLEINPUT_HPP
#define UI_CONSOLEINPUT_HPP

#include <string>

class ConsoleInput {
  public:
    // Liest eine Ganzzahl und bereinigt den Rest der Eingabezeile.
    int leseZahl();
    // Liest ein einzelnes Wort bis zum nächsten Trennzeichen.
    std::string leseWort();
    // Liest eine komplette Zeile inklusive Leerzeichen.
    std::string leseZeile();
};

#endif
