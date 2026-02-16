#include "TagebuchRepository.hpp"

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

const fs::path& TagebuchRepository::datenOrdnerPfad() {
    // Einmalig initialisiert, dann für alle Repository-Operationen wiederverwendet.
    static const fs::path datenOrdner = "data";
    return datenOrdner;
}

void TagebuchRepository::erstelleDatenOrdner() const {
    fs::create_directories(datenOrdnerPfad());
}

bool TagebuchRepository::schreibeNeuenEintrag(
    const std::string& datum, const std::vector<std::string>& zeilen) const {
    std::ofstream file(eintragPfad(datum));
    if (!file.is_open()) {
        return false;
    }

    for (const auto& zeile : zeilen) {
        file << zeile << "\n";
    }
    return true;
}

bool TagebuchRepository::leseEintrag(
    const std::string& datum, std::vector<std::string>& zeilen) const {
    return leseDatei(eintragPfad(datum), zeilen);
}

bool TagebuchRepository::leseDatei(
    const std::filesystem::path& dateiPfad, std::vector<std::string>& zeilen) const {
    std::ifstream file(dateiPfad);
    if (!file) {
        return false;
    }

    std::string line;
    // Liest unverändert zeilenweise, da Bearbeitung/Anzeige zeilenbasiert funktioniert.
    while (std::getline(file, line)) {
        zeilen.push_back(line);
    }
    return true;
}

bool TagebuchRepository::ueberschreibeEintrag(
    const std::string& datum, const std::vector<std::string>& zeilen) const {
    std::ofstream out_file(eintragPfad(datum), std::ios::trunc);
    if (!out_file) {
        return false;
    }

    for (const auto& updated_line : zeilen) {
        out_file << updated_line << '\n';
    }
    return true;
}

bool TagebuchRepository::haengeAn(const std::string& datum, const std::string& text) const {
    std::ofstream append_file(eintragPfad(datum), std::ios::app);
    if (!append_file) {
        return false;
    }

    append_file << text;
    return true;
}

bool TagebuchRepository::existiertEintrag(const std::string& datum) const {
    return fs::exists(eintragPfad(datum));
}

bool TagebuchRepository::entferneEintrag(const std::string& datum) const {
    return fs::remove(eintragPfad(datum));
}

std::vector<std::filesystem::directory_entry> TagebuchRepository::listeDateienImDataOrdner() const {
    std::vector<std::filesystem::directory_entry> dateien;
    if (!fs::exists(datenOrdnerPfad())) {
        return dateien;
    }

    for (const auto& entry : fs::directory_iterator(datenOrdnerPfad())) {
        dateien.push_back(entry);
    }
    return dateien;
}

std::string TagebuchRepository::eintragPfad(const std::string& datum) const {
    return (datenOrdnerPfad() / (datum + ".txt")).string();
}
