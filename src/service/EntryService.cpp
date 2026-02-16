#include "EntryService.hpp"

#include "domain/Entry.hpp"
#include "util/DatumsUtils.hpp"
#include <iostream>
#include <limits>
#include <string>
#include <vector>

void EntryService::createEntry() {
    Entry eintrag;

    // Datum wird bei Erstellung gesetzt und als Dateiname genutzt.
    eintrag.datum = aktuellesDatumAlsString();
    repository.erstelleDatenOrdner();

    if (repository.existiertEintrag(eintrag.datum)) {
        behandleBestehendenTageseintrag(eintrag.datum);
        return;
    }

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

    if (repository.schreibeNeuenEintrag(eintrag.datum, eintrag.inDateiZeilen())) {
        std::cout << "Eintrag gespeichert unter data/" << eintrag.datum << ".txt\n";
    } else {
        std::cerr << "Fehler beim Speichern des Eintrags!\n";
    }
}


void EntryService::behandleBestehendenTageseintrag(const std::string& date) {
    std::cout << "Fuer heute (" << date << ") existiert bereits ein Eintrag." << std::endl;
    std::cout << "Willst du ihn anschauen oder bearbeiten?" << std::endl;
    std::cout << "1. Eintrag anschauen." << std::endl;
    std::cout << "2. Eintrag bearbeiten." << std::endl;
    std::cout << "0. Zurueck." << std::endl;
    std::cout << "Deine Auswahl: ";

    int auswahl;
    std::cin >> auswahl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (auswahl) {
    case 1:
        zeigeEintragMitDatum(date);
        break;
    case 2:
        bearbeiteEintragMitDatum(date, "Datei konnte nicht gelesen werden.\n");
        break;
    default:
        break;
    }
}

// ------------------------------------------------------------------------------------------------
//                                  EINTRÄGE BEARBEITEN
// ------------------------------------------------------------------------------------------------

void EntryService::editEntry() {
    std::cout << "Welches Datum willst du bearbeiten (TT.MM.JJJJ)?" << std::endl;
    std::string date;
    std::cin >> date;

    bearbeiteEintragMitDatum(date, "Failed to open Datei to write!\n");
}

void EntryService::bearbeiteEintragMitDatum(const std::string& date, const std::string& fehlerText) {
    std::vector<std::string> lines;
    if (!repository.leseEintrag(date, lines)) {
        std::cerr << "Datei konnte nicht gelesen werden.\n";
        return;
    }

    bearbeiteEintragInteraktiv(date, lines, fehlerText);
}

// ------------------------------------------------------------------------------------------------
//                                  EINTRÄGE ANSCHAUEN
// ------------------------------------------------------------------------------------------------

void EntryService::showEntry() {
    std::cout << "Welches Datum willst du anschauen (TT.MM.JJJJ)?" << std::endl;
    std::string date;
    std::cin >> date;

    zeigeEintragMitDatum(date);
}

void EntryService::zeigeEintragMitDatum(const std::string& date) {
    std::vector<std::string> lines;
    if (!repository.leseEintrag(date, lines)) {
        std::cerr << "Datei konnte nicht gelesen werden.\n";
        return;
    }

    zeigeZeilen(lines);

    std::string answer;
    std::cout << "Willst du diesen Eintrag: " << date << " bearbeiten? (Ja oder Nein)" << std::endl;
    std::cin >> answer;
    std::cin.ignore(); // Leerzeichen ignorieren
    if (istJaAntwort(answer)) {
        bearbeiteEintragInteraktiv(date, lines, "Datei konnte nicht gelesen werden.\n");
    }
}

void EntryService::onlyshowEntry(const std::string& date) {
    std::vector<std::string> lines;
    if (!repository.leseEintrag(date, lines)) {
        std::cerr << "Datei konnte nicht gelesen werden.\n";
        return;
    }

    zeigeZeilen(lines);
}

void EntryService::bearbeiteEintragInteraktiv(
    const std::string& date, std::vector<std::string>& lines, const std::string& fehlerText) {
    // Vor der Auswahl wird immer der aktuelle Stand mit Zeilennummern gezeigt.
    zeigeZeilen(lines);

    size_t line_edit;
    std::cout << "Welchen Zeile willst du in dem Eintrag " << date << " bearbeiten? (Zahl)"
              << std::endl;
    std::cin >> line_edit;
    std::cout << "Du willst also die Zeile: " << line_edit << " bearbeiten? (Ja oder Nein)"
              << std::endl;

    std::string answer;
    std::cin >> answer;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
        '\n'); // Leert Speicher also das \n von oben cin answer :D

    std::string originalLine;
    if (istJaAntwort(answer)) {
        std::cout << "Gebe den neuen Text für die Zeile: " << line_edit << " ein." << std::endl;

        std::string new_content;
        std::getline(std::cin, new_content); // Liest ganze Zeile ein auch mit Leerzeichen

        originalLine = lines[line_edit - 1];

        // Es wird nur der Wertteil ersetzt, der Kategorie-Präfix bleibt unverändert.
        const size_t pos = originalLine.find(":");

        if (pos != std::string::npos) {
            const std::string prefix = originalLine.substr(0, pos + 1); // z.B. "#Training:"
            lines[line_edit - 1] = prefix + " " + new_content; // neue Zeile zusammensetzen
        } else {
            std::cerr << "Ungültiges Format! Kein ':' gefunden.\n";
        }
    }

    if (!repository.ueberschreibeEintrag(date, lines)) {
        std::cerr << fehlerText;
        return;
    }

    // Änderungsvermerk bleibt wie bisher immer am Dateiende.
    haengeAenderungsvermerkAn(date, originalLine);
}

void EntryService::haengeAenderungsvermerkAn(
    const std::string& date, const std::string& originalLine) {
    std::string category;
    const size_t pos2 = originalLine.find(":");
    if (pos2 != std::string::npos) {
        category = originalLine.substr(0, pos2);
    }

    if (!repository.haengeAn(date,
            "------------------------------\nZuletzt bearbeitet am: " + aktuellesDatumAlsString() +
                " (Bearbeitet: " + category + ")\n")) {
        std::cerr << "Fehler beim Anhängen des Änderungsvermerks.\n";
    }
}

bool EntryService::istJaAntwort(const std::string& antwort) {
    return antwort == "Ja" || antwort == "ja";
}

void EntryService::zeigeZeilen(const std::vector<std::string>& lines) {
    for (size_t index = 0; index < lines.size(); ++index) {
        std::cout << index + 1 << "." << lines[index] << std::endl;
    }
}

// ------------------------------------------------------------------------------------------------
//                                  EINTRÄGE LÖSCHEN
// ------------------------------------------------------------------------------------------------

void EntryService::deleteEntry() {
    std::cerr << "Welches Datum willst du entfernen (TT.MM.JJJJ)?" << std::endl;
    std::string date;
    std::cin >> date;

    onlyshowEntry(date);
    std::string answer;
    std::cerr << "Du willst also diesen Eintrag vom " << date << " entfernen?" << std::endl;
    std::cin >> answer;
    std::cin.ignore();
    if (istJaAntwort(answer)) {
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
    std::string hashtag;
    std::cout << "Nach welchem # willst du Suchen (Zur Auswahl: Training, Essen, Schlaf, Stimmung, "
                 "Produktivität, Freizeit und Geld)?"
              << std::endl;
    std::cin >> hashtag;

    std::string startDate;
    std::string endDate;
    std::cout << "In welchem Zeitraum willst du den #" << hashtag << " suchen und ausgeben?"
              << std::endl;
    std::cout << "Start-Datum (TT.MM.JJJJ) : " << std::endl;
    std::cin >> startDate;
    std::cout << "End-Datum (TT.MM.JJJJ) : " << std::endl;
    std::cin >> endDate;

    const int start = datumOhnePunkteAlsZahl(startDate);
    const int end = datumOhnePunkteAlsZahl(endDate);

    // Durchsucht nur Datumsdateien im bekannten Format.
    for (const auto& entry : repository.listeDateienImDataOrdner()) {
        const std::string filename = entry.path().filename().string(); // z.B. "04.05.2025.txt"

        // Nur .txt-Dateien verarbeiten
        if (filename.size() < 11 || filename.substr(filename.size() - 4) != ".txt") {
            continue;
        }

        // ".txt" entfernen → z.B. "04.05.2025"
        const std::string dateString = filename.substr(0, filename.size() - 4);
        const int fileDate = datumOhnePunkteAlsZahl(dateString);

        // Prüfen, ob im Zeitraum
        if (fileDate >= start && fileDate <= end) {
            // Datei liegt im Zeitraum → hier kannst du später öffnen und nach Hashtag suchen
            std::vector<std::string> dateiZeilen;
            if (!repository.leseDatei(entry.path(), dateiZeilen)) {
                std::cerr << "Datei konnte nicht gelesen werden.\n";
                continue;
            }

            bool foundInFile = false;
            for (const auto& line : dateiZeilen) {
                if (line.find(hashtag) != std::string::npos) {
                    if (!foundInFile) {
                        std::cout << "=== " << filename.substr(0, filename.size() - 4) << " ===\n";
                        foundInFile = true;
                    }
                    std::cout << line << "\n";
                }
            }
        }
    }

    std::string happy;
    std::cout << "Bist du Zufrieden?" << std::endl;
    std::cin >> happy;
}




