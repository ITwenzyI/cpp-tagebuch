#ifndef ENTRYMANAGER_HPP
#define ENTRYMANAGER_HPP
#include <string>

class EntryManager {
  public:
    void createEntry();
    void editEntry();
    void showEntry();
    void onlyshowEntry(std::string date);
    void deleteEntry();
    void searchhashtagEntry();
};

#endif
