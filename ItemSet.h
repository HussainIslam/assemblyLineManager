#include "Utilities.h"

#ifndef SICT_ITEMSET_H_
#define SICT_ITEMSET_H_
namespace sict {
  class ItemSet {
    std::string name{};
    unsigned int serialNumber{ 0 };
    unsigned int quantity{ 0 };
    std::string description{};
    Utilities utility;

  public:
    ItemSet(const std::string&);
    ItemSet(const ItemSet&) = delete;
    ItemSet(ItemSet&&);
    const std::string& getName() const;
    const unsigned int getSerialNumber() const;
    const unsigned int getQuantity() const;
    ItemSet& operator--();
    ItemSet& operator=(const ItemSet&) = delete;
    ItemSet&& operator=(ItemSet&&) = delete;
    void display(std::ostream& os, bool full) const;
  };

}


#endif