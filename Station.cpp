/***************************************
Name: Md. Hussainul Islam Sajib
Email: mhisajib@myseneca.ca
Id: 137651170
Assignment: Project - Milestone 2
Date: 12 March 2019
****************************************/
#include "Station.h"

namespace sict {
  //constructor for the Station class. Passes the source string to 
  //item data member and also assigns the name of the station
  Station::Station(const std::string& src) : item(src) {
    stationName = item.getName();
  }

  //displays the item data member to the standard output
  void Station::display(std::ostream& os) const {
    item.display(os,true);
  }

  //fills the order at the front of the queue
  void Station::fill(std::ostream& os) {
    if (!orders.empty()) { orders.front().fillItem(item, os); }
  }

  //returns the name of the item as std::string
  const std::string& Station::getName() const { return item.getName(); }

  //returns boolean value about whether an order is ready to be released
  //from the station or short of quantity
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

  //reduces the quantity of the item by calling the overloaded
  //operator of itemSet
  Station& Station::operator--() {
    --item;
    return *this;
  }

  //Overloaded operator to move an order passed as an argument
  //to the back of the queue of orders
  Station& Station::operator+=(CustomerOrder&& order) {
    orders.push_back(std::move(order));
    return *this;
  }

  //inserts the order at the front of the queue to the
  //argument passed to it "order" and returns whether
  //the order was filled or not
  bool Station::pop(CustomerOrder& ready) {
    bool filled{ false };
    if (!orders.empty()) {
      filled = orders.front().isItemFilled(stationName);
      ready = std::move(orders.front());
      orders.pop_front();
    }
    return filled;
  }

  //Manually validates the Station object by displaying to standard output
  void Station::validate(std::ostream& os) const {
    os << " getName(): " << item.getName() << std::endl;
    os << " getSerialNumber(): " << item.getSerialNumber() << std::endl;
    os << " getQuantity(): " << item.getQuantity() << std::endl;
  }

}