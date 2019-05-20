#include "CustomerOrder.h"

namespace sict {
  //default constructor for CustomerOrder class
  CustomerOrder::CustomerOrder() {}

  //extracts tokes from strings passed to it and stores in 
  //respective data members. This constructor also sets the
  //value of the next position in the source string
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

  //Move constructor for the CustomerOrder class
  CustomerOrder::CustomerOrder(CustomerOrder&& src) { 
    if (this != &src) { *this = std::move(src); }
  }

  //Destructor for the CustomerOrder class
  CustomerOrder::~CustomerOrder() { delete[]itemArray; }

  //Fills the orders with the itemSet passed to it
  //and displays whether the particular item of the order
  //has been filled or not.
  void CustomerOrder::fillItem(ItemSet& item, std::ostream& os) {
    for (size_t i = 0; i < numOfItem; i++) {
      if (item.getName() == itemArray[i].itemName) {
        if (item.getQuantity() > 0 && itemArray[i].filledStatus == false) {
          itemArray[i].filledStatus = true;
          itemArray[i].itemSerial = item.getSerialNumber();
          if (item.getQuantity() > 0) --item;
          os << " Filled " << customerName << " [" << productName << "][" << itemArray[i].itemName << "][" << itemArray[i].itemSerial << ']' << std::endl;;
        }
        else if (item.getQuantity() > 0 && itemArray[i].filledStatus) {
          os << " Unable to fill " << customerName << " [" << productName << "][" << itemArray[i].itemName << "][" << itemArray[i].itemSerial << "] already filled" << std::endl;;
        }
        else {
          os << " Unable to fill " << customerName << " [" << productName << "][" << itemArray[i].itemName << "][" << itemArray[i].itemSerial << "] out of stock" << std::endl;
        }
      }
    }
  }

  //returns boolean value of whether all the orders 
  //has been filled or not
  bool CustomerOrder::isFilled() const {
    int allFilled{ 1 };
    for (size_t i = 0; i < numOfItem; i++) {
      allFilled *= static_cast<int>(itemArray[i].filledStatus);
    }
    return static_cast<bool>(allFilled);
  }

  //returns boolean value of whether a particular item has been filled
  bool CustomerOrder::isItemFilled(const std::string& item) const {
    int allFilled{ 1 };
    for (size_t i = 0; i < numOfItem; i++) {
      if (itemArray[i].itemName == item) {
        allFilled *= static_cast<int>(itemArray[i].filledStatus);
      }
    }
    return static_cast<bool>(allFilled);
  }

  //returns the name of the custoemr and the product as string
  std::string CustomerOrder::getNameProduct() const {
    std::string nameProduct = customerName + " [" + productName + ']';
    return nameProduct;
  }

  //displays to the standard output the details of the order based on
  //whether to display details of the order or not
  void CustomerOrder::display(std::ostream& os, bool showDetail) const {
    if (!showDetail) {
      os.width(utilities.getFieldWidth());
      os << customerName;
      os << " [" << productName << ']' << std::endl;
      if (numOfItem > 0) {
        for (size_t i = 0; i < numOfItem; i++) {
          for (size_t i = 0; i < utilities.getFieldWidth()+1; i++) { os << ' '; }
          os << itemArray[i].itemName << std::endl;
        }
      }
    }
    else {
      os.width(utilities.getFieldWidth());
      os << customerName;
      os << " [" << productName << ']' << std::endl;
      if (numOfItem > 0) {
        for (size_t i = 0; i < numOfItem; i++) {
          for (size_t i = 0; i < utilities.getFieldWidth()+1; i++) { os << ' '; }
          os << '[' << itemArray[i].itemSerial << "] " << itemArray[i].itemName;
          os << " - " << (itemArray[i].filledStatus ? "FILLED" : "MISSING") << std::endl;
        }
      }
    }
  }

  //Move assignment operator for the CustomerOrder objects
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