/***************************************
Name: Md. Hussainul Islam Sajib
Email: mhisajib@myseneca.ca
Id: 137651170
Assignment: Project - Milestone 2
Date: 12 March 2019
****************************************/
#include "LineManager.h"
namespace sict {
  // construstor for the LineManager object that creates a lineManager from the 
  // data that has been passed to it. This replicates the information to data members
  LineManager::LineManager(std::vector<Station*>& station, std::vector<size_t>& indexNextStation, std::vector<CustomerOrder>& order, size_t indexStartingStation, std::ostream& os) {
    //copies the addresses of the stations to data members of the object
    stations.resize(station.size());
    for (size_t i = 0; i < station.size(); i++) {
      stations.at(i) = station.at(i);
    }
    //this moves the orders to the waitingQueue
    for (size_t i = 0; i < order.size(); i++) {
      waitingQueue.push_back(std::move(order.at(i)));
    }
    //copies the argument that stores the index number of the first station
    firstStation = indexStartingStation;
    //resizes the nextStation data member to hold all
    //the index numbers of the subsequent stations
    nextStations.resize(indexNextStation.size());
    //copies the index numbers of the next stations to data member
    for (size_t i = 0; i < nextStations.size(); i++) {
      nextStations.at(i) = indexNextStation.at(i);
    }
    //determines the index number of the last station in the lineManager
    lastStation = firstStation;
    while (lastStation != stations.size()) {
      lastStation = nextStations.at(lastStation);
    }
  }

  void LineManager::display(std::ostream& os) const {
    os << "COMPLETED ORDERS" << std::endl;
    for (auto& i : completed) { i.display(os, true); }
    os << "INCOMPLETE ORDERS" << std::endl;
    for (auto& i : incomplete) { i.display(os, true); }
  }

  bool LineManager::run(std::ostream& os) {
    bool allProcessed{ false };
    size_t numberOfOrders{ waitingQueue.size() };
    //run this loop until the waitingQueue is empty
    while (!waitingQueue.empty()) {
      //if the waitingQueue is not empty move one item from the
      //front of the waitingQueue to the first station on line
      if (!waitingQueue.empty()) {
        *(stations.at(firstStation)) += std::move(waitingQueue.front());
        waitingQueue.pop_front();
      }
      //filling the orders in each of the stations
      for (size_t i = 0; i < stations.size(); i++) {
        stations.at(i)->fill(os);
      }
      size_t index = firstStation;
      CustomerOrder temp{};
      for (size_t i = 0; i < stations.size(); i++) {
        if (stations.at(i)->hasAnOrderToRelease()) {
          stations.at(i)->pop(temp);
          if (i != lastStation) {
            std::string past{stations.at(i)->getName()};
            index = nextStations.at(i);
            std::string next{ stations.at(index)->getName() };
            std::string nameProduct{ temp.getNameProduct() };
            *(stations.at(index)) += std::move(temp);
            os << " --> " << nameProduct << " moved from " << past << " to " << next << std::endl;
          }     //end of if(index != lastStation)
          else {
            if (temp.isFilled()) {
              completed.push_back(std::move(temp));
            }     //end of if(temp.isFilled())
            else {
              incomplete.push_back(std::move(temp));
            }     //end of else(temp.isFilled())
          }     //end of else (index != lastStation)
        }       //end of if(stations.at(index)->hasAnOrderToRelease())
        /*else {
          index = nextStations.at(index);
        }*/
      }
    }
    if (completed.size() + incomplete.size() == numberOfOrders) {
      allProcessed = true;
    }
    
    return allProcessed;

  }
}