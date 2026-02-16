#ifndef SERVICE_ENTRYSERVICE_HPP
#define SERVICE_ENTRYSERVICE_HPP

#include "storage/TagebuchRepository.hpp"
#include <string>
#include <vector>

class EntryService {
  public:
    void createEntry();
    void editEntry();
    void showEntry();
    void deleteEntry();
    void searchhashtagEntry();

  private:
    void onlyshowEntry(const std::string& date);
    void bearbeiteEintragInteraktiv(
        const std::string& date, std::vector<std::string>& lines, const std::string& fehlerText);
    void haengeAenderungsvermerkAn(const std::string& date, const std::string& originalLine);
    static bool istJaAntwort(const std::string& antwort);
    static void zeigeZeilen(const std::vector<std::string>& lines);

    TagebuchRepository repository;
};

#endif
