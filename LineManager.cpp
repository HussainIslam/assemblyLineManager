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
    /*assemblyLine.resize(stations.size());
    for (size_t i = 0; i < station.size(); i++) {
      if (i == 0) { assemblyLine.at(i) = indexStartingStation; }
      else { assemblyLine.at(i) = indexNextStation.at(assemblyLine.at(i-1)); }
    }*/
    
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
    while (!waitingQueue.empty()) {
      if (!waitingQueue.empty()) {
        *(stations.at(firstStation)) += std::move(waitingQueue.front());
        waitingQueue.pop_front();
      }
      for (size_t i = 0; i < stations.size(); i++) {
        stations.at(i)->fill(os);
      }
      size_t index = firstStation;
      CustomerOrder temp{};
      while (index != stations.size()) {
        stations.at(index)->pop(temp);
        if (temp.isItemFilled(stations.at(index)->getName())) {
          if (index == lastStation) {
            if (temp.isFilled()) {
              completed.push_back(std::move(temp));
            }
            else {
              incomplete.push_back(std::move(temp));
            }
          }
          else {
            index = nextStations.at(index);
            *(stations.at(index)) += std::move(temp);
          }
        }
        else {
          index = nextStations.at(index);
        }
      }
    }
    if (completed.size() + incomplete.size() == numberOfOrders) {
      allProcessed = true;
    }
    
    return allProcessed;


    //  bool allProcessed{ false };
    //  size_t noItemInProcess{ 0 };
    //  //loop until the waitingQueue
    //  while (!waitingQueue.empty()) {
    //    //if (!waitingQueue.empty()) {
    //      *(stations.at(0)) += std::move(waitingQueue.front());
    //      waitingQueue.pop_front();
    //      ++noItemInProcess;
    //    //}
    //    for (size_t i = 0; i < noItemInProcess; i++) {
    //      stations.at(i)->fill(os);
    //    }
    //    for (size_t i = 0; i < noItemInProcess; i++) {
    //      CustomerOrder temp{};
    //      if (i == stations.size() - 1) {
    //        stations.at(i)->pop(temp);
    //        if (stations.at(i)->hasAnOrderToRelease()) {
    //          completed.push_back(std::move(temp));
    //        }
    //        else {
    //          incomplete.push_back(std::move(temp));
    //        }
    //      }
    //      else {
    //        stations.at(i)->pop(temp);
    //        *(stations.at(i + 1)) += std::move(temp);
    //      }
    //      
    //    }
    //  }
    //  
    //  size_t extraStations{ stations.size() - noItemInProcess };
    //  while (noItemInProcess) {
    //    for (size_t i = extraStations; i < (noItemInProcess + extraStations); i++) {
    //      stations.at( i )->fill(os);
    //    }
    //    for (size_t i = extraStations; i < (noItemInProcess + extraStations); i++) {
    //      CustomerOrder temp{};
    //      if (i == stations.size() - 1) {
    //        stations.at(i)->pop(temp);
    //        if (stations.at(i)->hasAnOrderToRelease()) {
    //          completed.push_front(std::move(temp));
    //        }
    //        else {
    //          incomplete.push_front(std::move(temp));
    //        }
    //      }
    //      else {
    //        stations.at(i)->pop(temp);
    //        *(stations.at(i + 1)) += std::move(temp);
    //      }
    //    }

    //    noItemInProcess--;
    //  }
    //  
    //  allProcessed = true;
    //  
    //  return allProcessed;
    //}
    }
}