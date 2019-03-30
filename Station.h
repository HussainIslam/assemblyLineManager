/***************************************
Name: Md. Hussainul Islam Sajib
Email: mhisajib@myseneca.ca
Id: 137651170
Assignment: Project - Milestone 2
Date: 12 March 2019
****************************************/
#ifndef SICT_STATION_H
#define SICT_STATION_H
#include <deque>
#include "CustomerOrder.h"
#include "ItemSet.h"

namespace sict {
  class Station {
    std::deque<CustomerOrder> orders{};
    std::string stationName;
    ItemSet item;
  public:
    Station(const std::string&);
    void display(std::ostream& os) const;
    void fill(std::ostream& os);
    const std::string& getName() const;
    bool hasAnOrderToRelease() const;
    Station& operator--();
    Station& operator+=(CustomerOrder&& order);
    bool pop(CustomerOrder& ready);
    void validate(std::ostream& os) const;

    Station(const Station&) = delete;
    Station(Station&&) = delete;
    Station& operator=(const Station&) = delete;
    Station& operator=(Station&&) = delete;
  };
}

#endif // !SICT_STATION_H
