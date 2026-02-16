#ifndef UTIL_DATUMSUTILS_HPP
#define UTIL_DATUMSUTILS_HPP

#include <string>

[[nodiscard]] std::string aktuellesDatumAlsString();
// Konvertiert TT.MM.JJJJ nach Ganzzahl DDMMYYYY für einfache Bereichsvergleiche.
[[nodiscard]] int datumOhnePunkteAlsZahl(std::string datum);

#endif
