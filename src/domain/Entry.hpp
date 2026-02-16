#ifndef DOMAIN_ENTRY_HPP
#define DOMAIN_ENTRY_HPP

#include <string>
#include <vector>

class Entry {
  public:
    std::string datum;
    std::string author;
    std::string training;
    std::string essen;
    std::string schlaf;
    std::string stimmung;
    std::string produktivitaet;
    std::string freizeit;
    std::string geld;

    std::vector<std::string> inDateiZeilen() const;
};

#endif
