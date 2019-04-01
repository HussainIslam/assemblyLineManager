/***************************************
Name: Md. Hussainul Islam Sajib
Email: mhisajib@myseneca.ca
Id: 137651170
Assignment: Project - Milestone 2
Date: 12 March 2019
****************************************/
#include "Station.h"

namespace sict {
  Station::Station(const std::string& src) : item(src) {
    stationName = item.getName();
  }

  void Station::display(std::ostream& os) const {
    item.display(os,true);
  }

  void Station::fill(std::ostream& os) {
    if (!orders.empty()) { orders.front().fillItem(item, os); }
  }

  const std::string& Station::getName() const { return item.getName(); }

  bool Station::hasAnOrderToRelease() const {
    bool releaseState{ false };
    if (!orders.empty()) {
      if (!item.getQuantity()) {
        releaseState = true;
      }
      else {
        releaseState = orders.front().isItemFilled(stationName);
      }
    }
    return releaseState;
  }

  Station& Station::operator--() {
    --item;
    return *this;
  }

  Station& Station::operator+=(CustomerOrder&& order) {
    orders.push_back(std::move(order));
    return *this;
  }

  bool Station::pop(CustomerOrder& ready) {
    bool filled{ false };
    if (!orders.empty()) {
      filled = orders.front().isItemFilled(stationName);
      ready = std::move(orders.front());
      orders.pop_front();
    }
    return filled;
  }

  void Station::validate(std::ostream& os) const {
    os << "getName(): " << item.getName() << std::endl;
    os << "getSerialNumber(): " << item.getSerialNumber() << std::endl;
    os << "getQuantity(): " << item.getQuantity() << std::endl;
  }

}