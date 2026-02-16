#include "TagebuchRepository.hpp"

#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void TagebuchRepository::erstelleDatenOrdner() const {
    fs::create_directories("data");
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

bool TagebuchRepository::leseEintrag(const std::string& datum, std::vector<std::string>& zeilen) const {
    std::ifstream file(eintragPfad(datum));
    if (!file) {
        return false;
    }

    std::string line;
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
    if (!fs::exists("data")) {
        return dateien;
    }

    for (const auto& entry : fs::directory_iterator("data")) {
        dateien.push_back(entry);
    }
    return dateien;
}

std::string TagebuchRepository::eintragPfad(const std::string& datum) const {
    return "data/" + datum + ".txt";
}
