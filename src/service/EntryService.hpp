#ifndef SERVICE_ENTRYSERVICE_HPP
#define SERVICE_ENTRYSERVICE_HPP

#include "storage/TagebuchRepository.hpp"
#include <string>
#include <vector>

class EntryService {
  public:
    // Öffentliche Anwendungsfälle der Tagebuch-Funktionalität.
    void createEntry();
    void editEntry();
    void showEntry();
    void deleteEntry();
    void searchhashtagEntry();

  private:
    // Bearbeitet einen Eintrag direkt über ein gegebenes Datum.
    void bearbeiteEintragMitDatum(const std::string& date, const std::string& fehlerText);
    // Zeigt einen Eintrag direkt über ein gegebenes Datum.
    void zeigeEintragMitDatum(const std::string& date);
    // Fragt bei vorhandenem Tages-Eintrag nach Folgeaktion.
    void behandleBestehendenTageseintrag(const std::string& date);
    // Zeigt einen Eintrag nur an, ohne Folgeaktionen.
    void onlyshowEntry(const std::string& date);
    // Kapselt den wiederverwendeten Bearbeitungsablauf.
    void bearbeiteEintragInteraktiv(
        const std::string& date, std::vector<std::string>& lines, const std::string& fehlerText);
    // Schreibt den bestehenden Änderungsvermerk ans Ende der Datei.
    void haengeAenderungsvermerkAn(const std::string& date, const std::string& originalLine);
    // Akzeptiert die bisherigen Bestätigungsvarianten.
    static bool istJaAntwort(const std::string& antwort);
    // Einheitliche Zeilenausgabe mit fortlaufender Nummerierung.
    static void zeigeZeilen(const std::vector<std::string>& lines);

    // Zentrale Dateioperationen für alle Use Cases.
    TagebuchRepository repository;
};

#endif
