/***************************************
Name: Md. Hussainul Islam Sajib
Email: mhisajib@myseneca.ca
Id: 137651170
Assignment: Project - Milestone 3
Date: 31 March 2019
****************************************/

#include <iostream>
#include <string>
#include "ItemSet.h"
#include "Utilities.h"

namespace sict {
  //extracts token from string and stores in data members of itemSet
  ItemSet::ItemSet(const std::string& src) {
    size_t next_pos{ 0 };
    name = utility.extractToken(src,next_pos);
    if (name.size() > utility.getFieldWidth()){
      utility.setFieldWidth(name.size());
    }
    if (next_pos <= src.size()) {
      serialNumber = std::stoul(utility.extractToken(src, next_pos));
    }
    if (next_pos <= src.size()) {
      quantity = std::stoul(utility.extractToken(src, next_pos));
    }
    if (next_pos <= src.size()) {
      description = utility.extractToken(src, next_pos);
    }
  }
  
  //move constructor of ItemSet class
  ItemSet::ItemSet(ItemSet&& src) {
    name = src.name;
    serialNumber = src.serialNumber;
    quantity = src.quantity;
    description = src.description;
    src.name = "";
    src.serialNumber = 0;
    src.quantity = 0;
  }

  //returns the name of the item
  const std::string& ItemSet::getName() const { return name; }
  
  //returns serial number of item
  const unsigned int ItemSet::getSerialNumber() const { return serialNumber; }
  
  //returns quantity of a product
  const unsigned int ItemSet::getQuantity() const { return quantity; }
  
  //reduces the quantity by 1 and increases the serial number by 1
  ItemSet& ItemSet::operator--() {
    quantity--; serialNumber++;
    return *this;
  }

  //displays ItemSet object to the standard output with formatting
  //based on whether to display full details or not
  void ItemSet::display(std::ostream& os, bool full) const {
    if (full) {
      os.width(utility.getFieldWidth());
      os << std::left;
      os.fill(' ');
      os << name;
      os << " [";
      os.fill('0');
      os.width(5);
      os << serialNumber;
      os.fill(' ');
      os << "] Quantity ";
      os << std::left;
      os.width(3);
      os << quantity;
      os << " Description: ";
      os << description;
      os << std::endl;
    }
    else {
      os.width(utility.getFieldWidth());
      os << std::left;
      os.fill(' ');
      os << name;
      os << " [";
      os.fill('0');
      os.width(5);
      os << serialNumber + 1 << ']';
      os << std::endl;
    }
  }
}