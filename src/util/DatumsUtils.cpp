#include "DatumsUtils.hpp"

#include <algorithm>
#include <ctime>
#include <iomanip>
#include <sstream>

std::string aktuellesDatumAlsString() {
    const std::time_t zeitstempel = std::time(nullptr);
    const std::tm lokaleZeit = *std::localtime(&zeitstempel);

    std::ostringstream stream;
    stream << std::put_time(&lokaleZeit, "%d.%m.%Y");
    return stream.str();
}

int datumOhnePunkteAlsZahl(std::string datum) {
    datum.erase(std::remove(datum.begin(), datum.end(), '.'), datum.end());
    return std::stoi(datum);
}
