/***************************************
Name: Md. Hussainul Islam Sajib
Email: mhisajib@myseneca.ca
Id: 137651170
Assignment: Project - Milestone 2
Date: 12 March 2019
****************************************/

#ifndef SICT_CUSTOMERORDER_H_
#define SICT_CUSTOMERORDER_H_
#include <iostream>
#include "ItemSet.h"
#include "Utilities.h"

namespace sict {
  struct ItemInfo; 

  class CustomerOrder {
    std::string customerName{};
    std::string productName{};
    ItemInfo* itemArray = nullptr;
    size_t numOfItem{ 0 };
    Utilities utilities;
  public:
    CustomerOrder();
    CustomerOrder(const std::string&);
    CustomerOrder(CustomerOrder&) = delete;
    CustomerOrder(CustomerOrder&&);
    ~CustomerOrder();
    void fillItem(ItemSet& item, std::ostream& os);
    bool isFilled() const;
    bool isItemFilled(const std::string& item) const;
    std::string getNameProduct() const;
    void display(std::ostream& os, bool showDetail = false) const;
    CustomerOrder& operator=(CustomerOrder&) = delete;
    CustomerOrder& operator=(CustomerOrder&&);
  };

  struct ItemInfo {
    std::string itemName{};
    unsigned int itemSerial{0};
    bool filledStatus{false};
  };

}



#endif // !SICT_CUSTOMERORDER_H_
