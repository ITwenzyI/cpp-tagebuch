#ifndef SERVICE_ENTRYSERVICE_HPP
#define SERVICE_ENTRYSERVICE_HPP

#include "EntryManager.hpp"

class EntryService {
  public:
    void createEntry();
    void showEntry();
    void editEntry();
    void deleteEntry();
    void searchhashtagEntry();

  private:
    EntryManager entryManager;
};

#endif
