#include "Entry.hpp"

std::vector<std::string> Entry::inDateiZeilen() const {
    return {
        "       Erstellt von " + author + " am " + datum + ". :)",
        "#Training: " + training,
        "#Essen: " + essen,
        "#Schlaf: " + schlaf,
        "#Stimmung: " + stimmung,
        "#Produktivität: " + produktivitaet,
        "#Freizeit: " + freizeit,
        "#Geld: " + geld,
    };
}
