#ifndef SERVICE_ENTRYSERVICE_HPP
#define SERVICE_ENTRYSERVICE_HPP

#include <string>

class EntryService {
  public:
    void createEntry();
    void editEntry();
    void showEntry();
    void deleteEntry();
    void searchhashtagEntry();

  private:
    void onlyshowEntry(std::string date);
};

#endif
