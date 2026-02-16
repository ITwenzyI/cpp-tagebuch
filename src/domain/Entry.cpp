#include "Entry.hpp"

std::vector<std::string> Entry::inDateiZeilen() const {
    // Das Dateiformat bleibt exakt stabil, weil Einträge zeilenbasiert gelesen/bearbeitet werden.
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
