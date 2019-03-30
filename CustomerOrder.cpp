  /***************************************
  Name: Md. Hussainul Islam Sajib
  Email: mhisajib@myseneca.ca
  Id: 137651170
  Assignment: Project - Milestone 2
  Date: 12 March 2019
  ****************************************/
#include "CustomerOrder.h"

namespace sict {
  CustomerOrder::CustomerOrder() {}

  CustomerOrder::CustomerOrder(const std::string& sourceStr) {
    size_t next_pos{ 0 };
    customerName = utilities.extractToken(sourceStr, next_pos);
    if (customerName.size() > utilities.getFieldWidth()) {
      utilities.setFieldWidth(customerName.size());
    }
    if (next_pos <= sourceStr.size()) {
      productName = utilities.extractToken(sourceStr, next_pos);
    }
    while (next_pos <= sourceStr.size()) {
      ItemInfo* temp;
      temp = new ItemInfo[numOfItem];
      for (size_t i = 0; i < numOfItem; i++) { temp[i] = itemArray[i]; }
      delete[] itemArray;
      itemArray= new ItemInfo [++numOfItem];
      for (size_t i = 0; i < numOfItem - 1; i++) { itemArray[i] = temp[i]; }
      delete[] temp;
      itemArray[numOfItem - 1].itemName = utilities.extractToken(sourceStr, next_pos);
    }
  }

  CustomerOrder::CustomerOrder(CustomerOrder&& src) { 
    if (this != &src) { *this = std::move(src); }
  }

  CustomerOrder::~CustomerOrder() { delete[]itemArray; }

  void CustomerOrder::fillItem(ItemSet& item, std::ostream& os) {
    for (size_t i = 0; i < numOfItem; i++) {
      if (item.getName() == itemArray[i].itemName) {
        if (item.getQuantity() > 0 && itemArray[i].filledStatus == false) {
          itemArray[i].filledStatus = true;
          itemArray[i].itemSerial = item.getSerialNumber();
          if (item.getQuantity() > 0) --item;
          os << " Filled " << customerName << '[' << productName << "][" << itemArray[i].itemName << "][" << itemArray[i].itemSerial << ']' << std::endl;;
        }
        else if (item.getQuantity() > 0 && itemArray[i].filledStatus) {
          os << " Unable to fill " << customerName << '[' << productName << "][" << itemArray[i].itemName << "][" << itemArray[i].itemSerial << "] already filled" << std::endl;;
        }
        else {
          os << " Unable to fill " << customerName << '[' << productName << "][" << itemArray[i].itemName << "][" << itemArray[i].itemSerial << "] out of stock" << std::endl;
        }
      }
    }
  }

  bool CustomerOrder::isFilled() const {
    int allFilled{ 1 };
    for (size_t i = 0; i < numOfItem; i++) {
      allFilled *= static_cast<int>(itemArray[i].filledStatus);
    }
    return static_cast<bool>(allFilled);
  }

  bool CustomerOrder::isItemFilled(const std::string& item) const {
    int allFilled{ 1 };
    for (size_t i = 0; i < numOfItem; i++) {
      if (itemArray[i].itemName == item) {
        allFilled *= static_cast<int>(itemArray[i].filledStatus);
      }
    }
    return static_cast<bool>(allFilled);
  }

  std::string CustomerOrder::getNameProduct() const {
    std::string nameProduct = customerName + '[' + productName + ']';
    return nameProduct;
  }

  void CustomerOrder::display(std::ostream& os, bool showDetail) const {
    if (!showDetail) {
      os.width(utilities.getFieldWidth());
      os << customerName;
      os << '[' << productName << ']' << std::endl;
      if (numOfItem > 0) {
        for (size_t i = 0; i < numOfItem; i++) {
          for (size_t i = 0; i < utilities.getFieldWidth(); i++) { os << ' '; }
          os << itemArray[i].itemName << std::endl;
        }
      }
    }
    else {
      os << customerName << '[' << productName << ']' << std::endl;
      if (numOfItem > 0) {
        for (size_t i = 0; i < numOfItem; i++) {
          for (size_t i = 0; i < utilities.getFieldWidth(); i++) { os << ' '; }
          os << '[' << itemArray[i].itemSerial << "] " << itemArray[i].itemName;
          os << " - " << itemArray[i].filledStatus << std::endl;
        }
      }
    }
  }

  CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) {
    if (this != &src) {
      delete[] itemArray;
      itemArray = nullptr;
      customerName = src.customerName;
      productName = src.productName;
      numOfItem = src.numOfItem;
      itemArray = src.itemArray;
      src.customerName = "";
      src.productName = "";
      src.numOfItem = 0;
      src.itemArray = nullptr;
    }
    return *this;
  }


}