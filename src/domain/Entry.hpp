#ifndef DOMAIN_ENTRY_HPP
#define DOMAIN_ENTRY_HPP

#include <string>
#include <vector>

class Entry {
  public:
    // Entspricht der Dateinamenskonvention TT.MM.JJJJ.
    std::string datum;
    std::string author;
    std::string training;
    std::string essen;
    std::string schlaf;
    std::string stimmung;
    std::string produktivitaet;
    std::string freizeit;
    std::string geld;

    // Baut die persistierte Textrepräsentation in der bestehenden Reihenfolge.
    [[nodiscard]] std::vector<std::string> inDateiZeilen() const;
};

#endif
