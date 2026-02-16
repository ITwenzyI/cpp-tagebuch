#include "EntryService.hpp"

#include "domain/Entry.hpp"
#include "storage/TagebuchRepository.hpp"
#include <algorithm> // für std::remove
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

void EntryService::createEntry() {
    Entry eintrag;
    TagebuchRepository repository;

    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d.%m.%Y");
    eintrag.datum = oss.str();

    std::cout << "Eintrag für " << eintrag.datum << " erstellen:\n" << std::endl;
    std::cout << "Author: " << std::endl;
    std::getline(std::cin, eintrag.author);
    std::cout << "#Training: ";
    std::getline(std::cin, eintrag.training);
    std::cout << "#Essen: ";
    std::getline(std::cin, eintrag.essen);
    std::cout << "#Schlaf: ";
    std::getline(std::cin, eintrag.schlaf);
    std::cout << "#Stimmung: ";
    std::getline(std::cin, eintrag.stimmung);
    std::cout << "#Produktivität: ";
    std::getline(std::cin, eintrag.produktivitaet);
    std::cout << "#Freizeit: ";
    std::getline(std::cin, eintrag.freizeit);
    std::cout << "#Geld: ";
    std::getline(std::cin, eintrag.geld);

    repository.erstelleDatenOrdner();

    if (repository.schreibeNeuenEintrag(eintrag.datum, eintrag.inDateiZeilen())) {
        std::cout << "Eintrag gespeichert unter data/" << eintrag.datum << ".txt\n";
    } else {
        std::cerr << "Fehler beim Speichern des Eintrags!\n";
    }
}

// ------------------------------------------------------------------------------------------------
//                                  EINTRÄGE BEARBEITEN
// ------------------------------------------------------------------------------------------------

void EntryService::editEntry() {
    TagebuchRepository repository;

    std::cout << "Welches Datum willst du bearbeiten (TT.MM.JJJJ)?" << std::endl;
    std::string date;
    std::cin >> date;

    std::vector<std::string> lines;
    if (!repository.leseEintrag(date, lines)) {
        std::cerr << "Datei konnte nicht gelesen werden.\n";
        return;
    }

    size_t line_edit;
    for (line_edit = 0; line_edit < lines.size(); ++line_edit) {
        std::cout << line_edit + 1 << "." << lines[line_edit] << std::endl;
    }
    std::cout << "Welchen Zeile willst du in dem Eintrag " << date << " bearbeiten? (Zahl)"
              << std::endl;
    std::cin >> line_edit;
    std::cout << "Du willst also die Zeile: " << line_edit << " bearbeiten? (Ja oder Nein)"
              << std::endl;
    std::string answer;
    std::cin >> answer;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
        '\n'); // Leert Speicher also das \n von oben cin answer :D

    std::string new_content;
    std::string original_line2;
    if (answer == "Ja" || answer == "ja") {
        std::cout << "Gebe den neuen Text für die Zeile: " << line_edit << " ein." << std::endl;
        std::getline(
            std::cin, new_content); // Liest ganze Zeile ein auch mit Leerzeichen
                                    // std::cin >> new_content; liest nur 1 Wort ein = Problem

        std::string original_line = lines[line_edit - 1];
        original_line2 = original_line;

        // Finde die Position vom Doppelpunkt
        size_t pos = original_line.find(":");

        if (pos != std::string::npos) {
            std::string prefix = original_line.substr(0, pos + 1); // z.B. "#Training:"
            lines[line_edit - 1] = prefix + " " + new_content;     // neue Zeile zusammensetzen
        } else {
            std::cerr << "Ungültiges Format! Kein ':' gefunden.\n";
        }
    }

    if (!repository.ueberschreibeEintrag(date, lines)) {
        std::cerr << "Failed to open Datei to write!\n";
        return;
    }

    // 1. Aktuelles Datum
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d.%m.%Y");
    std::string dateStr = oss.str();

    // 2. Kategorie aus ursprünglicher Zeile extrahieren
    std::string category;
    size_t pos2 = original_line2.find(":");
    if (pos2 != std::string::npos) {
        category = original_line2.substr(0, pos2);
    }

    // 3. Änderungsvermerk unten anhängen
    if (!repository.haengeAn(date,
            "------------------------------\nZuletzt bearbeitet am: " + dateStr
                + " (Bearbeitet: " + category + ")\n")) {
        std::cerr << "Fehler beim Anhängen des Änderungsvermerks.\n";
    }
}

// ------------------------------------------------------------------------------------------------
//                                  EINTRÄGE ANSCHAUEN
// ------------------------------------------------------------------------------------------------

void EntryService::showEntry() {
    TagebuchRepository repository;

    std::cout << "Welches Datum willst du anschauen (TT.MM.JJJJ)?" << std::endl;
    std::string date;
    std::cin >> date;

    std::vector<std::string> lines;
    if (!repository.leseEintrag(date, lines)) {
        std::cerr << "Datei konnte nicht gelesen werden.\n";
        return;
    }

    for (size_t l = 0; l < lines.size(); ++l) {
        std::cout << l + 1 << "." << lines[l] << std::endl;
    }

    std::string answer;
    std::cout << "Willst du diesen Eintrag: " << date << " bearbeiten? (Ja oder Nein)" << std::endl;
    std::cin >> answer;
    std::cin.ignore(); // Leerzeichen ignorieren
    if (answer == "Ja" || answer == "ja") {
        int line_edit;
        std::cout << "Welchen Zeile willst du in dem Eintrag " << date << " bearbeiten? (Zahl)"
                  << std::endl;
        std::cin >> line_edit;
        std::cout << "Du willst also die Zeile: " << line_edit << " bearbeiten? (Ja oder Nein)"
                  << std::endl;
        std::string answer2;
        std::cin >> answer2;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
            '\n'); // Leert Speicher also das \n von oben cin answer :D

        std::string original_line2;
        std::string new_content;
        if (answer2 == "Ja" || answer2 == "ja") {
            std::cout << "Gebe den neuen Text für die Zeile: " << line_edit << " ein." << std::endl;
            std::getline(std::cin, new_content); // Liest ganze Zeile ein auch mit Leerzeichen

            std::string original_line = lines[line_edit - 1];
            original_line2 = original_line;

            // Finde die Position vom Doppelpunkt
            size_t pos = original_line.find(":");

            if (pos != std::string::npos) {
                std::string prefix = original_line.substr(0, pos + 1); // z.B. "#Training:"
                lines[line_edit - 1] = prefix + " " + new_content;     // neue Zeile zusammensetzen
            } else {
                std::cerr << "Ungültiges Format! Kein ':' gefunden.\n";
            }
        }

        if (!repository.ueberschreibeEintrag(date, lines)) {
            std::cerr << "Datei konnte nicht gelesen werden.\n";
            return;
        }

        // 1. Aktuelles Datum
        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%d.%m.%Y");
        std::string dateStr = oss.str();

        // 2. Kategorie aus ursprünglicher Zeile extrahieren
        std::string category;
        size_t pos2 = original_line2.find(":");
        if (pos2 != std::string::npos) {
            category = original_line2.substr(0, pos2);
        }

        // 3. Änderungsvermerk unten anhängen
        if (!repository.haengeAn(date,
                "------------------------------\nZuletzt bearbeitet am: " + dateStr
                    + " (Bearbeitet: " + category + ")\n")) {
            std::cerr << "Fehler beim Anhängen des Änderungsvermerks.\n";
        }
    }
}

void EntryService::onlyshowEntry(std::string date) {
    TagebuchRepository repository;

    std::vector<std::string> lines;
    if (!repository.leseEintrag(date, lines)) {
        std::cerr << "Datei konnte nicht gelesen werden.\n";
        return;
    }

    for (size_t l = 0; l < lines.size(); ++l) {
        std::cout << l + 1 << "." << lines[l] << std::endl;
    }
}

// ------------------------------------------------------------------------------------------------
//                                  EINTRÄGE LÖSCHEN
// ------------------------------------------------------------------------------------------------

void EntryService::deleteEntry() {
    TagebuchRepository repository;

    std::cerr << "Welches Datum willst du entfernen (TT.MM.JJJJ)?" << std::endl;
    std::string date;
    std::cin >> date;

    onlyshowEntry(date);
    std::string answer;
    std::cerr << "Du willst also diesen Eintrag vom " << date << " entfernen?" << std::endl;
    std::cin >> answer;
    std::cin.ignore();
    if (answer == "Ja" || answer == "ja") {
        if (repository.existiertEintrag(date)) {
            if (repository.entferneEintrag(date)) {
                std::cerr << "Eintrag wurde entfernt.\n";
            } else {
                std::cerr << "Eintrag konnte nicht entfernt werden!\n";
            }
        } else {
            std::cerr << "Datei existiert nicht.\n";
        }
    }
}

// ------------------------------------------------------------------------------------------------
//                                  EINTRÄGE SUCHEN #
// ------------------------------------------------------------------------------------------------

void EntryService::searchhashtagEntry() {
    TagebuchRepository repository;

    std::string hashtag;
    std::cout << "Nach welchem # willst du Suchen (Zur Auswahl: Training, Essen, Schlaf, Stimmung, "
                 "Produktivität, Freizeit und Geld)?"
              << std::endl;
    std::cin >> hashtag;
    std::string startDate, endDate;
    std::cout << "In welchem Zeitraum willst du den #" << hashtag << " suchen und ausgeben?"
              << std::endl;
    std::cout << "Start-Datum (TT.MM.JJJJ) : " << std::endl;
    std::cin >> startDate;
    std::cout << "End-Datum (TT.MM.JJJJ) : " << std::endl;
    std::cin >> endDate;
    // Punkte aus Datum entfernen
    startDate.erase(std::remove(startDate.begin(), startDate.end(), '.'), startDate.end());
    endDate.erase(std::remove(endDate.begin(), endDate.end(), '.'), endDate.end());

    // In int umwandeln
    int start = std::stoi(startDate);
    int end = std::stoi(endDate);

    for (const auto& entry : repository.listeDateienImDataOrdner()) {
        std::string filename = entry.path().filename().string(); // z.B. "04.05.2025.txt"

        // Nur .txt-Dateien verarbeiten
        if (filename.size() < 11 || filename.substr(filename.size() - 4) != ".txt") {
            continue;
        }

        // ".txt" entfernen → z.B. "04.05.2025"
        std::string dateString = filename.substr(0, filename.size() - 4);

        // Punkte entfernen → z.B. "04052025"
        dateString.erase(std::remove(dateString.begin(), dateString.end(), '.'), dateString.end());

        // In Zahl umwandeln
        int fileDate = std::stoi(dateString);

        // Prüfen, ob im Zeitraum
        if (fileDate >= start && fileDate <= end) {
            // Datei liegt im Zeitraum → hier kannst du später öffnen und nach Hashtag suchen
            std::string path = entry.path().string(); // vollständiger Pfad

            std::ifstream file(path);
            if (!file) {
                std::cerr << "Datei konnte nicht gelesen werden.\n";
                continue;
            }

            std::string line;
            bool foundInFile = false;

            while (std::getline(file, line)) {
                if (line.find(hashtag) != std::string::npos) {
                    if (!foundInFile) {
                        std::cout << "=== " << filename.substr(0, filename.size() - 4) << " ===\n";
                        foundInFile = true;
                    }
                    std::cout << line << "\n";
                }
            }

            file.close();
        }
    }
    std::string happy;
    std::cout << "Bist du Zufrieden?" << std::endl;
    std::cin >> happy;
}
