#include "LineManager.h"
namespace sict {
  // construstor for the LineManager object that creates a lineManager from the 
  // data that has been passed to it. This replicates the information to data members
  // Also determines the last station in the lineManager and store it in a data member
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
    while (nextStations.at(lastStation) != stations.size()) {
      lastStation = nextStations.at(lastStation);
    }
  }

  //displays all the orders, both complete and incomplete
  void LineManager::display(std::ostream& os) const {
    os << "COMPLETED ORDERS" << std::endl;
    for (auto& i : completed) { i.display(os, true); }
    os << std::endl;
    os << "INCOMPLETE ORDERS" << std::endl;
    for (auto& i : incomplete) { i.display(os, true); }
  }
  
  //runs the lineManager, fills up the orders in the queue,
  //moves the filled/unfilled orders to the next stations,
  //and moves each order to either completed or incomplete deque.
  //Finally, check whether all the orders have been processed or not
  //return boolean value accordingly.
  bool LineManager::run(std::ostream& os) {
    bool allProcessed{ false };
    size_t numberOfOrders{ waitingQueue.size() };
    std::string past{};
    std::string next{};
    std::string nameProduct{};
    //run this loop until the waitingQueue is empty
    while (!waitingQueue.empty() || numberOfOrders) {
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
      //checking each order in each of the stations,
      //and moving the orders to appropriate places.
      //If the order is not at the last station, move it to the next one,
      //if the order is at the last station, move it to either completed
      //or incomplete deque according to its filled status
      size_t index = firstStation;
      CustomerOrder temp{};
      for (size_t i = 0; i < stations.size(); i++) {
        if (stations.at(i)->hasAnOrderToRelease()) {
          stations.at(i)->pop(temp);
          if (i != lastStation) {
            past = stations.at(i)->getName();
            index = nextStations.at(i);
            if (index != stations.size()) {
              next = stations.at(index)->getName();
              nameProduct = temp.getNameProduct();
              *(stations.at(index)) += std::move(temp);
              os << " --> " << nameProduct << " moved from " << past << " to " << next << std::endl;
            }
          }     //end of if(index != lastStation)
          else {
            nameProduct = temp.getNameProduct();
            past = stations.at(i)->getName();
            os << " --> " << nameProduct << " moved from " << past << " to ";
            if (temp.isFilled()) {
              os << "Completed Set" << std::endl;
              completed.push_back(std::move(temp));
            }     //end of if(temp.isFilled())
            else {
              os << "Incomplete Set" << std::endl;
              incomplete.push_back(std::move(temp));
            }     //end of else(temp.isFilled())
            --numberOfOrders;
          }     //end of else (index != lastStation)
        }       //end of if(stations.at(index)->hasAnOrderToRelease())
      }
    }
    //checks whether there is any order left to be processed
    //if not assign true to allProcessed flag
    if (!numberOfOrders) {
      allProcessed = true;
    }
    return allProcessed;
  }
}