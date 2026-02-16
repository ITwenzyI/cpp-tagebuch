#ifndef UI_CONSOLEINPUT_HPP
#define UI_CONSOLEINPUT_HPP

#include <string>

class ConsoleInput {
  public:
    int leseZahl();
    std::string leseWort();
    std::string leseZeile();
};

#endif
